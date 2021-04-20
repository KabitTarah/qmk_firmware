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

char sysinfo[10] = "BD9 kabit";
char str1[31];
char str2[31];
char str3[31];
char str4[31];
char str5[31];
char str6[31];

enum encoder_names {
  _LEFT,
  _RIGHT,
  _MIDDLE,
};

//                                           _ L_G3
//                                          / _ L_G2
//                                          |/ _ L_G1
//                                          ||/ _ M_GER
//                                          |||/
//                                          ||||  _ L_P3
//                                          |||| / _ L_P2
//                                          |||| |/ _ L_P1
//                                          |||| ||/ _ M_PROG
//                                          |||| |||/
//                       Layer Mask _       |||| ||||  _ L_E3       _ Layer #
//                                   \      |||| |||| / _ L_E2     /
//                                   |      |||| |||| |/ _ L_E1    |
//                                   |      |||| |||| ||/ _ M_ENG  |
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

#define X_BASE  1 << _BASE
#define X_PROG	1 << _PROG
#define X_MEDIA 1 << _MEDIA
#define X_STR   1 << _STR

enum custom_keycodes {
    MOD_D = SAFE_RANGE,
    MOD_S,
    RET_B,
    KT_HOME,
    KT_END,
    KT_UP,
    KT_DOWN,
    KT_LEFT,
    KT_RGHT,
    VS_MINI, // Minimize all VSCode
    VS_MAXI,
    VS_PANL, // Panel (Terminal, Problems)
    KT_STR1, // Saved String Technology
    KT_STR2,
    KT_STR3,
    KT_STR4,
    KT_STR5,
    KT_STR6,
};

layer_state_t _layer = _BASE;
layer_state_t _max_layer = _STR;
bool dmod = false;
bool smod = false;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
        |                   | Knob 1: Change base layer |                    |
        | Dom Modifier      | Press: Return to Base     | Sub Modifier       |
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
        | Dom Modifier      | Press: Return to Base     | Sub Modifier       |
        | Home              | Up                        | End                |
        | Left              | Down                      | Right              |
     */
    [_PROG] = LAYOUT(
        MOD_D  , RET_B  , MOD_S  ,
        KT_HOME, KT_UP  , VS_MAXI,
        KT_LEFT, VS_PANL, VS_MINI
    ),
    /*
        |                   | Knob 1: Change base layer |                    |
        | Dom Modifier      | Press: Return to Base     | Sub Modifier       |
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
        | Dom Modifier      | Press: Return to Base     | Sub Modifier       |
        | Home              | Up                        | End                |
        | Left              | Down                      | Right              |
     */
    [_STR] = LAYOUT(
        MOD_D  , RET_B  , MOD_S  ,
        KT_STR1, KT_STR2, KT_STR3,
        KT_STR4, KT_STR5, KT_STR6
    ),
};

void rgb_matrix_indicators_kb(void) {
    switch (_layer) {
        case _BASE:
            rgb_matrix_set_color_all(RGB_RED);
            if (dmod) {
                rgb_matrix_set_color(9, RGB_BLUE);
            }
            if (smod) {
                rgb_matrix_set_color(10, RGB_BLUE);
            }
            break;
        case _PROG:
            rgb_matrix_set_color_all(RGB_GREEN);
            if (dmod) {
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

void keyboard_post_init_user(void) {
    debug_enable = false;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case MOD_D:
            if (record->event.pressed) {
                dmod = true;
            } else {
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
                    reset_keyboard();
                } else if (smod) {
                    tap_code(KC_MUTE);
                } else if (dmod) {
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
                    // PROBLEMS PANEL
                    SEND_STRING(SS_LGUI("M"));
                } else if (dmod) {
                    return true;
                } else {
                    // TERMINAL
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
                    // Send string
                    SEND_STRING(str1);
                    tap_code(KC_ENT);
                } else {
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
    dprintf("KL: kc: 0x%04X, col: %u, row: %u, pressed: %b, time: %u, interrupt: %b, count: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed, record->event.time, record->tap.interrupted, record->tap.count);
    dprintf("    Default: %u\n", get_highest_layer(default_layer_state));
    dprintf("    Highest: %u\n", get_highest_layer(layer_state));
    dprintf("    Layer Index: %u\n\n", _layer);
    dprintf("          D Mod: %u   S Mod: %u\n\n", dmod, smod);
    dprintf("\n\n");
    return true;
};

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
        if (clockwise) {
            _layer++;
            if (_layer > _max_layer) {
                _layer = _BASE;
            }
        } else {
            if (_layer == _BASE) {
                _layer = _max_layer;
            } else {
                _layer--;
            }
        }
        layer_state_t change_to = (1 << _layer);
        default_layer_set(change_to);
        layer_state_set(change_to);
    }
}

// Wait for 0x1FF8 to start sequence
// Host side can clear by sending 0x1F 32 times
uint8_t start = 0; // 0,1=waiting for TLV, 2=read type next, 3=read length, 4=read value
uint8_t type = 0xff;
uint8_t length;
uint8_t value[31]; // max string len 30 + null terminator
uint8_t clen;      // current length in bytes
void virtser_recv(uint8_t byte_in) {
    switch (start) {
        case 0:
            if (byte_in == 0x1f) {
                start = 1;
            }
            break;
        case 1:
            if (byte_in == 0xf8) {
                start = 2;
            } else if (byte_in != 0x1f) {
                start = 0;
            }
            break;
        case 2:
            type = byte_in;
            // type cannot be 0x1f or 0xf8
            if ((type == 0x1f) || (type == 0xf8)) {
                start = 0;
            } else {
                start = 3;
            }
            break;
        case 3:
            length = byte_in;
            start = 4;
            break;
        case 4:
            value[clen] = byte_in;
            clen++;
            break;
    }

    if ((start == 4) && (clen == length)) {
        switch (type) {
            case 0xa1:       // save string #1
                value[clen] = '\0';
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
                virtser_send(0xf0);
                virtser_send(strlen(sysinfo));
                for (int i = 0; i < strlen(sysinfo); i++) {
                    virtser_send(sysinfo[i]);
                }
                break;
        }

        length = 0;
        clen = 0;
        start = 0;
        type = 0xff;
        dprintf("\n\n");
    }
}
