/* Copyright 2021 Tarah Tamayo
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H
#include "virtser.h"
#include "string.h"

// System Info String - Accessed via Serial connection
char sysinfo[10] = "BD9 kabit";
// Six string registers to hold arbitrary strings (max len 30)
// These strings are printed via a macro and configured by the host device
// using sendstr.py (in this folder)
char str1[31];
char str2[31];
char str3[31];
char str4[31];
char str5[31];
char str6[31];

// Only using _MIDDLE but I figured I should leave this as a board HW config
enum encoder_names {
  _LEFT,
  _RIGHT,
  _MIDDLE,
};


// set up 12 layers but only the first four are currently used.
//
//                       Layer Mask _       |||| ||||  _ STR        _ Layer #
//                                   \      |||| |||| / _ MEDIA    /
//                                   |      |||| |||| |/ _ PROG    |
//                                   |      |||| |||| ||/ _ BASE   |
enum layer_names {   //              |      |||| |||| |||/         |
    _BASE,       //        Base: 0x001 = 0b 0000 0000 0001    ---> 0
    _PROG,       //        Prog: 0x002 = 0b 0000 0000 0010    ---> 1
    _MEDIA,      //       Media: 0x004 = 0b 0000 0000 0100    ---> 2
    _STR,        //       None1: 0x008 = 0b 0000 0000 1000    ---> 3
    _NONE2,      //       None2: 0x010 = 0b 0000 0001 0000    ---> 4
    _NONE3,      //       None3: 0x020 = 0b 0000 0010 0000    ---> 5
    _NONE4,      //       None4: 0x040 = 0b 0000 0100 0000    ---> 6
    _NONE5,      //       None5: 0x080 = 0b 0000 1000 0000    ---> 7
    _NONE6,      //       None6: 0x100 = 0b 0001 0000 0000    ---> 8
    _NONE7,      //       None7: 0x200 = 0b 0010 0000 0000    ---> 9
    _NONE8,      //       None8: 0x400 = 0b 0100 0000 0000    ---> 10
    _NONE9,      //       None9: 0x800 = 0b 1000 0000 0000    ---> 11
};

// These defs are used to activate specific layers
#define X_BASE  1 << _BASE
#define X_PROG	1 << _PROG
#define X_MEDIA 1 << _MEDIA
#define X_STR   1 << _STR

// Most keycodes on this macropad are custom. MOD_D and MOD_S set flags when pressed (and unset when released).
// Each macro key can have up to 4 functions:
//    1. Macro pressed
//    2. Macro + D
//    3. Macro + S
//    4. Macro + D/S
// This IS a macro pad after all!
enum custom_keycodes {
    MOD_D = SAFE_RANGE,
    MOD_S,
    RET_B,   // Return to Base (also reset to load firmware)
    KT_HOME,
    KT_END,
    KT_UP,
    KT_DOWN,
    KT_LEFT,
    KT_RGHT,
    VS_MINI, // Minimize VSCode folding
    VS_MAXI, // Maximize VSCode folding
    VS_PANL, // Panel (Terminal, Problems)
    KT_STR1, // Saved String Technology (tm)
    KT_STR2,
    KT_STR3,
    KT_STR4,
    KT_STR5,
    KT_STR6,
};

// We want to keep track of our current default layer. This starts at Base. It's easier to keep track this way!
layer_state_t _layer = _BASE;
// We also set our max layer. This way I only have to update one variable if I want to add or remove a layer
layer_state_t _max_layer = _STR;

// Modifier flags
bool dmod = false;
bool smod = false;

// A constant work in progress! Thes are mapped to keycodes I've created, plus the odd standard map
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
        |                   | Knob 1: Change base layer |                    |
        | D Modifier        | Press: Return to Base     | S Modifier         |
        | Home              | Up                        | End                |
        | Left              | Down                      | Right              |
     */
    [_BASE] = LAYOUT(
        MOD_D  , RET_B  , MOD_S  ,
        KT_HOME, KT_UP  , KT_END ,
        KT_LEFT, KT_DOWN, KT_RGHT
    ),
    /*
        |                   | Knob 1: Change base layer |                    |
        | D Modifier        | Press: Return to Base     | S Modifier         |
        | Home              | Up                        | VS Code Open Folds |
        | Left              | VS Code Panel Shortcuts   | VS Code Fold       |
     */
    [_PROG] = LAYOUT(
        MOD_D  , RET_B  , MOD_S  ,
        KT_HOME, KT_UP  , VS_MAXI,
        KT_LEFT, VS_PANL, VS_MINI
    ),
    /*
        |                   | Knob 1: Change base layer |                    |
        | D Modifier        | Press: Return to Base     | S Modifier         |
        | Home              | Up                        | End                |
        | Left              | Down                      | Right              |
     */
    [_MEDIA] = LAYOUT(
        MOD_D  , RET_B  , MOD_S  ,
        KT_HOME, KT_UP  , KT_END ,
        KT_LEFT, KT_DOWN, KT_RGHT
    ),
    /*
        |                   | Knob 1: Change base layer |                    |
        | D Modifier        | Press: Return to Base     | S Modifier         |
        | String 1          | String 2                  | String 3           |
        | String 4          | String 5                  | String 6           |
     */
    [_STR] = LAYOUT(
        MOD_D  , RET_B  , MOD_S  ,
        KT_STR1, KT_STR2, KT_STR3,
        KT_STR4, KT_STR5, KT_STR6
    ),
};

// This runs automatically on a cycle. It ensures the LEDs are set correctly for the different layers
// and modifiers. This is the only indication of what layer we're on, so it's rather important.
void rgb_matrix_indicators_kb(void) {
    switch (_layer) {
        case _BASE:
            // This is a built in. It only seems to work inside this function
            rgb_matrix_set_color_all(RGB_RED);
            if (dmod) {
                // My D Key is on the left. This LED is the right underlay. I prefer this
                // off-sides / inverted indication
                rgb_matrix_set_color(9, RGB_BLUE);
            }
            if (smod) {
                rgb_matrix_set_color(10, RGB_BLUE);
            }
            break;
        case _PROG:
            rgb_matrix_set_color_all(RGB_GREEN);
            if (dmod) {
                // Modifier colors are chosen for contrast. Plus I like purple and green!
                rgb_matrix_set_color(9, RGB_PURPLE);
            }
            if (smod) {
                rgb_matrix_set_color(10, RGB_PURPLE);
            }
            break;
        case _MEDIA:
            rgb_matrix_set_color_all(RGB_BLUE);
            if (dmod) {
                rgb_matrix_set_color(9, RGB_RED);
            }
            if (smod) {
                rgb_matrix_set_color(10, RGB_RED);
            }
            break;
        case _STR:
            rgb_matrix_set_color_all(RGB_CYAN);
            if (dmod) {
                rgb_matrix_set_color(9, RGB_MAGENTA);
            }
            if (smod) {
                rgb_matrix_set_color(10, RGB_MAGENTA);
            }
            break;
    }
}

// Runs on startup. Just initialization goes in here!
void keyboard_post_init_user(void) {
    debug_enable = false;
}

// Runs every time a button is pressed. This is where all the macros live!
// Might make functions to make this more readable. Might delete later.
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case MOD_D:
            // this button and the next sets or unsets the modifier flags.
            if (record->event.pressed) {
                // pushed the button down
                dmod = true;
            } else {
                // pulled the button up
                dmod = false;
            }
            break;
        case MOD_S:
            if (record->event.pressed) {
                smod = true;
            } else {
                smod = false;
            }
            break;
        case RET_B:
            if (record->event.pressed) {
                if (smod && dmod) {
                    // all 3 top row buttons triggers a reset for firmware upload
                    reset_keyboard();
                } else if (smod) {
                    // S mod ... mute!
                    tap_code(KC_MUTE);
                } else if (dmod) {
                    // D mod ... pause/play
                    tap_code(KC_MPLY);
                } else {
                    // Return to base layer
                    default_layer_set(X_BASE);
                    layer_state_set(X_BASE);
                }
            }
            break;
        case VS_MINI:
            if (record->event.pressed) {
                if (smod && dmod) {
                    return true;   // placeholder
                } else if (smod) {
                    return true;
                } else if (dmod) {
                    return true;
                } else {
                    // Minimize All Folds
                    SEND_STRING(SS_LGUI("k0"));
                }
            }
            break;
        case VS_MAXI:
            if (record->event.pressed) {
                if (smod && dmod) {
                    return true;   // placeholder
                } else if (smod) {
                    return true;
                } else if (dmod) {
                    return true;
                } else {
                    // Maximize All Folds
                    SEND_STRING(SS_LGUI("kj"));
                }
            }
            break;
        case VS_PANL:
            if (record->event.pressed) {
                if (smod && dmod) {
                    return true;   // placeholder
                } else if (smod) {
                    // VSCode PROBLEMS PANEL
                    SEND_STRING(SS_LGUI("M"));
                } else if (dmod) {
                    return true;
                } else {
                    // VSCode TERMINAL
                    SEND_STRING(SS_LGUI(SS_TAP(X_F12)));
                }
            }
            break;
        case KT_STR1:
            if (record->event.pressed) {
                if (smod && dmod) {
                    return true;   // placeholder
                } else if (smod) {
                    // Send string
                    SEND_STRING(str1);
                } else if (dmod) {
                    // Send string followed by Enter
                    SEND_STRING(str1);
                    tap_code(KC_ENT);
                } else {
                    // I don't want to accidentally send strings. Mod keys ONLY
                    return true;
                }
            }
            break;
        case KT_STR2:
            if (record->event.pressed) {
                if (smod && dmod) {
                    return true;   // placeholder
                } else if (smod) {
                    // Send string
                    SEND_STRING(str2);
                } else if (dmod) {
                    SEND_STRING(str2);
                    tap_code(KC_ENT);
                } else {
                    // could use these for something else entirely, though!
                    return true;
                }
            }
            break;
        case KT_STR3:
            if (record->event.pressed) {
                if (smod && dmod) {
                    return true;   // placeholder
                } else if (smod) {
                    // Send string
                    SEND_STRING(str3);
                } else if (dmod) {
                    SEND_STRING(str3);
                    tap_code(KC_ENT);
                } else {
                    return true;
                }
            }
            break;
        case KT_STR4:
            if (record->event.pressed) {
                if (smod && dmod) {
                    return true;   // placeholder
                } else if (smod) {
                    // Send string
                    SEND_STRING(str4);
                } else if (dmod) {
                    SEND_STRING(str4);
                    tap_code(KC_ENT);
                } else {
                    return true;
                }
            }
            break;
        case KT_STR5:
            if (record->event.pressed) {
                if (smod && dmod) {
                    return true;   // placeholder
                } else if (smod) {
                    // Send string
                    SEND_STRING(str5);
                } else if (dmod) {
                    SEND_STRING(str5);
                    tap_code(KC_ENT);
                } else {
                    return true;
                }
            }
            break;
        case KT_STR6:
            if (record->event.pressed) {
                if (smod && dmod) {
                    return true;   // placeholder
                } else if (smod) {
                    // Send string
                    SEND_STRING(str6);
                } else if (dmod) {
                    SEND_STRING(str6);
                    tap_code(KC_ENT);
                } else {
                    return true;
                }
            }
            break;
    }
    // Debugs only run if debug is enabled
    dprintf("KL: kc: 0x%04X, col: %u, row: %u, pressed: %b, time: %u, interrupt: %b, count: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed, record->event.time, record->tap.interrupted, record->tap.count);
    dprintf("    Default: %u\n", get_highest_layer(default_layer_state));
    dprintf("    Highest: %u\n", get_highest_layer(layer_state));
    dprintf("    Layer Index: %u\n\n", _layer);
    dprintf("          D Mod: %u   S Mod: %u\n\n", dmod, smod);
    dprintf("\n\n");
    return true;
};

// Runs when an encoder tick event occurs (turn of encoder)
void encoder_update_user(uint8_t index, bool clockwise) {
    if (dmod) {
        if (clockwise) {
            tap_code(KC_PGDN);
        } else {
            tap_code(KC_PGUP);
        }
    } else if (smod) {
        if (clockwise) {
            tap_code(KC_DOWN);
        } else {
            tap_code(KC_UP);
        }
    } else {
        // without mods, the encoder controls what layer the board is on
        // I already have a volume knob elsewhere :P
        if (clockwise) {
            // INCREASE the thing!!
            _layer++;
            // can't go to an unknown layer!! loop back around
            if (_layer > _max_layer) {
                _layer = _BASE;
            }
        } else {
            // these are unsigned ints. We have to loop around BEFORE we do a subtraction!!!
            if (_layer == _BASE) {
                _layer = _max_layer;
            } else {
                _layer--;
            }
        }
        // change to the specified layer as both default and current layer.
        // This is a layer mask, so we have to push a 1 to the right spot
        layer_state_t change_to = (1 << _layer);
        default_layer_set(change_to);
        layer_state_set(change_to);
    }
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * The next bit of code sets up a virtual serial port with the host machine.
 * The protocol is illustrated below. We are the CLIENT side.
 *
 * TLV based protocol. This was used because this triggered event reads only
 * one byte at a time. Prepend with 0x1FF8. This is used as a reset. Only
 * used FROM the Host. This allows the host to resync by sending 32 0x1F
 * bytes in a row. (0x1F = decimal 31)
 *
 * Type (Received)
 * 0xA1 - 0xA6  = Set Register. Expected payload is a null terminated string
 *                Response is T=0xA0 with a 1 byte payload with the register
 * 0xF1         = Send Info String. The Info String is sent as payload to
 *                a T=0xF0
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
// determines the current message state:
uint8_t start = 0; // 0,1=waiting for TLV, 2=read type next, 3=read length, 4=read value
uint8_t type;
uint8_t length;
uint8_t value[31]; // max string len 30 + null terminator
uint8_t clen;      // current length in bytes
void virtser_recv(uint8_t byte_in) {
    switch (start) {
        case 0:
            // in start = 0 we have no valid message in progress. If we get the first
            // pramble byte, start goes to 1
            if (byte_in == 0x1f) {
                start = 1;
            }
            break;
        case 1:
            // in start = 1 we have the 1st preamble byte. If we get the second preamble
            // byte, we continue to 2. If not we go back to 0 unless we got another 1st
            // preamble, in which case we stay in 1.
            if (byte_in == 0xf8) {
                start = 2;
            } else if (byte_in != 0x1f) {
                start = 0;
            }
            break;
        case 2:
            // in start = 2 we get the Type. This value cannot be 0x1f or 0xf8!!
            // (length and payload are not restricted in this way)
            type = byte_in;
            // type cannot be 0x1f or 0xf8
            if (type == 0x1f) {
                // 0x1f is the start of a preamble. We go back to the beginning with 1
                start = 1;
            } else if (type == 0xf8) {
                // 0xf8 is an error. We go back to 0.
                start = 0;
            } else {
                start = 3;
            }
            break;
        case 3:
            // in start = 3 we get the Length. This is set and the count begins.
            length = byte_in;
            clen = 0;
            start = 4;
            break;
        case 4:
            // in start = 4 we add to the value register. This continues until the desired
            // length has been reached
            value[clen] = byte_in;
            clen++;
            break;
    }

    // If we're fully started and have received the whole Value payload, now we process the TLV
    if ((start == 4) && (clen == length)) {
        switch (type) {
            case 0xa1:       // save string #1
                value[clen] = '\0';
                // copy the received Value into the requsted register
                strcpy(str1, (char *)value);
                virtser_send(0xa0); // save string ack
                virtser_send(0x01);
                virtser_send(0x01); // value = string register
                break;
            case 0xa2:       // save string #2
                value[clen] = '\0';
                strcpy(str2, (char *)value);
                virtser_send(0xa0);
                virtser_send(0x01);
                virtser_send(0x02);
                break;
            case 0xa3:       // save string #2
                value[clen] = '\0';
                strcpy(str3, (char *)value);
                virtser_send(0xa0);
                virtser_send(0x01);
                virtser_send(0x03);
                break;
            case 0xa4:       // save string #2
                value[clen] = '\0';
                strcpy(str4, (char *)value);
                virtser_send(0xa0);
                virtser_send(0x01);
                virtser_send(0x04);
                break;
            case 0xa5:       // save string #2
                value[clen] = '\0';
                strcpy(str5, (char *)value);
                virtser_send(0xa0);
                virtser_send(0x01);
                virtser_send(0x05);
                break;
            case 0xa6:       // save string #2
                value[clen] = '\0';
                strcpy(str6, (char *)value);
                virtser_send(0xa0);
                virtser_send(0x01);
                virtser_send(0x06);
                break;
            case 0xf1:      // system info
                // Send back T=0xF0
                virtser_send(0xf0);
                // Send back Length of the sysinfo string
                virtser_send(strlen(sysinfo));
                // then send each byte of the string
                for (int i = 0; i < strlen(sysinfo); i++) {
                    virtser_send(sysinfo[i]);
                }
                break;
        }

        // Reset and wait for the next one!
        length = 0;
        clen = 0;
        start = 0;
        type = 0xff;
        dprintf("\n\n");
    }
}
