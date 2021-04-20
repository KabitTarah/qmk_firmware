import serial
from serial.tools import list_ports
import sys

vid = 0xcb10
pid = 0x2133

def open_port() -> serial.Serial:
    ports = list_ports.comports()
    port = None
    for p in filter(lambda p: p.vid is not None, ports):
        if (p.vid == vid) and (p.pid == pid):
            port = p
    if port is None:
        print(f"Could not open port for vid/pid { vid }/{ pid }")
        exit()
    return serial.Serial(port.device)

def send_msg(ser: serial.Serial, t, l, v: list) -> list:
    msg_preamble = [0x1f, 0xf8]
    msg = msg_preamble
    msg.append(t)
    msg.append(l)
    msg.extend(v)
    ser.write(msg)

def get_msg(ser: serial.Serial):
    t = ser.read()
    l = ser.read()
    v = ser.read(size=ord(l))
    return [t, l, v]

def sysinfo(ser: serial.Serial):
    t = 0xf1
    l = 0x0
    v = []
    send_msg(ser, t, l, v)
    t, l, v = get_msg(ser)
    print(f"system info: { str(v) }")

def send_str(ser: serial.Serial, pos: int, data: str):
    if (pos < 1) or (pos > 6):
        print(f"Position { pos } not supported!")
        exit()
    if len(data) > 30:
        print(f"Saved strings must be 30 characters or fewer.")
        exit()
    base_t = 0xa0
    t = base_t + pos
    # need to add 1 for null terminator
    l = len(data) + 1
    v = [ord(c) for c in data]
    # null terminator
    v.append(0x0)
    send_msg(ser, t, l, v)
    t, l, v = get_msg(ser)
    if ord(v) == pos:
        print(f"Message stored in position { v }")

ser = open_port()
sysinfo(ser)

if len(sys.argv) < 3:
    print("Please run with two arguments:")
    print("    pos  - Number 1 through 6 of string storage position")
    print("    str  - String to store, max 30 characters.")
    print()
else:
    send_str(ser, int(sys.argv[1]), sys.argv[2])
