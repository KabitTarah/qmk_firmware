# KabitTarah's BDN9 MacroPad Design

This is a 3x3 macropad with one encoder in the following configuration:

```
+-----+-----+-----+
|     |     |     |
|  D  | ENC |  S  |
|     |     |     |
+-----+-----+-----+
|     |     |     |
|  1  |  2  |  3  |
|     |     |     |
+-----+-----+-----+
|     |     |     |
|  4  |  5  |  6  |
|     |     |     |
+-----+-----+-----+
```

![image of BDN9](https://lh3.googleusercontent.com/pw/ACtC-3cseFZhtNSv-s9F5wGiZVoOI_AtmlO4BKqLsdDNJj-TDFfFlyFTbAhCvG8V5aRzYT0e_tTxdcZX9mcWubh4-9zGMWerEi9VILLd291Kp64yAwGth186Ot4sBmlSaTWLsHRxEGkenyVSEwDDsfEFqp1mrA=w1164-h1550-no?authuser=0)

### Encoder
The base encoder function changes layers:

  * BASE LAYER --- Red
  * VSCode     --- Green
  * Media      --- Blue
  * Strings    --- Cyan

These layers are described more in sections below

### D / S Modifiers
D and S keys act as modifiers. When held down they set a flag allowing up to 24 macros per Encoder layer. When held down, the underglow changes accordingly (to a contrasting color)

### Strings and sendstr.py

#### Purpose
This keymap contains a virtual serial bus to communicate between the host computer and the macro pad. `sendstr.py` is a utility that connects to the virtual serial port and sends strings to one of six registers on the board. These strings can be accessed on the Strings layer.

#### Setup
`sendstr.py` requires only Python3 and pyserial. This was tested with Python 3.9.4 and pyserial==3.5 on MacOS. Install pyserial with `pip install pyserial`. I recommend using a VENV with `python3 -m venv path/to/venv/dir` and `source path/to/venv/dir/bin/activate`

#### Operation
With the board connected run

```
python sendstr.py 1 test1234
```

The board will receive the string test1234 and put it into string register 1. Change to Strings (Cyan layer) with the encoder and press and hold S1. The string `test1234` will be printed. Press and hold D1 and the string will print followed by a carriage return.

### Layers
