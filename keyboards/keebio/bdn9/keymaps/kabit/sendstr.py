# /* Copyright 2021 Tarah Tamayo
#  *
#  * This program is free software: you can redistribute it and/or modify
#  * it under the terms of the GNU General Public License as published by
#  * the Free Software Foundation, either version 2 of the License, or
#  * (at your option) any later version.
#  *
#  * This program is distributed in the hope that it will be useful,
#  * but WITHOUT ANY WARRANTY; without even the implied warranty of
#  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  * GNU General Public License for more details.
#  *
#  * You should have received a copy of the GNU General Public License
#  * along with this program.  If not, see <http://www.gnu.org/licenses/>.
#  */

import serial
from serial.tools import list_ports
import sys

vid = 0xcb10
pid = 0x2133

def open_port() -> serial.Serial:
    """
    open_port() - looks for a port that matches VID and PID expected for the device and opens
    a serial connection to that port.
    """
    # built in module of the pySerial library to list all COM Ports on the system
    ports = list_ports.comports()
    port = None
    # look through all ports that have a VID. The filter prevents us from comparing to None
    for p in filter(lambda p: p.vid is not None, ports):
        if (p.vid == vid) and (p.pid == pid):
            port = p
    # Error out and exit if no matching device is found
    if port is None:
        print(f"Could not open port for vid/pid { vid }/{ pid }")
        exit()
    # Open and return the Serial connection object
    return serial.Serial(port.device)

def send_msg(ser: serial.Serial, t, l, v: list):
    """
    send_msg() - Builds a byte array from TLV arguments to send via serial, then sends the message.

    Arguments:
        ser   - Serial object (see open_port())
        t     - Type. 1 Byte. This is the instruction code
        l     - Length. 1 Byte. This is the length of the Value payload ONLY
        v     - Value. This is the data (byte list) correspondint with the T instruction. This may be empty.
    """
    # Message preamble ensures that we have a way to recover sync if needed.
    msg_preamble = [0x1f, 0xf8]
    # Start crafting the message using the preamble
    msg = msg_preamble
    # 1st append T (one byte) and L (one byte)
    msg.append(t)
    msg.append(l)
    # then extend by the full byte array in V
    msg.extend(v)
    # Write the message to the serial bus
    ser.write(msg)

def get_msg(ser: serial.Serial):
    """
    get_msg() - Listens on the Serial bus for a message from the client side.

    Arguments:
        ser   - Serial object (see open_port())
    Returns:
        TLV list with V being a byte array
    """
    # First read T and L. These are always 1 Byte each
    t = ser.read()
    l = ser.read()
    # Then read L bytes into V
    v = ser.read(size=ord(l)) if ord(l) > 0 else []
    return [t, l, v]

def sysinfo(ser: serial.Serial):
    """
    sysinfo() - Sends a System Info request (T=0xF1) to the client. The client should respond with
    an informational string. This string is printed to stdout

    Arguments:
        ser   - Serial object (see open_port())
    """
    # this message code is defined and agreed upon in the client code
    t = 0xf1
    # this is a single request with no value so length is zero but must still be sent
    l = 0x0
    # but value is empty. This will turn into a 2 byte TOTAL length message
    v = []
    # send the message to the serial bus
    send_msg(ser, t, l, v)
    # listen to the serial bus for a reply. The response will be T=0xF0 but this isn't important to parse out
    t, l, v = get_msg(ser)
    # changing the byte array into a string is important. We print this to stdout
    print(f"system info: { str(v) }")

def send_str(ser: serial.Serial, pos: int, data: str):
    """
    send_str() - Sends a string into one of six register positions on the client.

    Arguments:
        ser   - Serial object (see open_port())
        pos   - Register position. Integer 1 through 6.
        data  - A string to send into the register on the client. This is limited to 30 characters.
    """
    # Check to see if the position requested is in range
    if (pos < 1) or (pos > 6):
        print(f"Position { pos } not supported!")
        exit()
    # Check to see that string length is in range
    if len(data) > 30:
        print(f"Saved strings must be 30 characters or fewer.")
        exit()
    # The response T will be 0xa0. Register Ts are 0xa1 through 0xa6. Register 0xAX is not available.
    base_t = 0xa0
    # Calculate the Type code to send
    t = base_t + pos
    # need to add 1 to length for null terminator. Strings on the client are C standard and require a 0x0 null terminator
    l = len(data) + 1
    # convert the string to a byte array
    v = [ord(c) for c in data]
    # append the null terminator
    v.append(0x0)
    # Send the message with the calculated TLV
    send_msg(ser, t, l, v)
    # A response is expected with T=0xA0. This is an acknowledgement only
    t, l, v = get_msg(ser)
    # verify the Ack Value contains the stored register number
    if ord(v) == pos:
        print(f"Message stored in position { v }")
    else:
        print(f"Received unknown response { t } / { l } / { v }")

# Open the virtual serial port
ser = open_port()
# Get and print the TLV System Info string
sysinfo(ser)

# Check arguments
if len(sys.argv) < 3:
    print("Please run with two arguments:")
    print("    pos  - Number 1 through 6 of string storage position")
    print("    str  - String to store, max 30 characters.")
    print()
else:
    # send the string received to the requested register
    send_str(ser, int(sys.argv[1]), sys.argv[2])
