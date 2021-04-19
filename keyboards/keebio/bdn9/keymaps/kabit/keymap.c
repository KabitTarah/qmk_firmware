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
    _NONE1,      //       None1: 0x008 = 0b 0000 0000 1000    ---> 3
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
};

layer_state_t _layer = _BASE;
layer_state_t _max_layer = _MEDIA;
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
        | Dom Modifier      | Press: Return to Base     | [Sub Modifier]     |
        | Home              | Up                        | End                |
        | Left              | Down                      | Right              |
     */
    [_PROG] = LAYOUT(
        RESET  , BL_STEP, KC_STOP,
        _______, KC_HOME, RGB_MOD,
        KC_MPRV, KC_END , KC_MNXT
    ),
    /*
        |                   | Knob 1: Change base layer |                    |
        | Dom Modifier      | Press: Return to Base     | [Sub Modifier]     |
        | Home              | Up                        | End                |
        | Left              | Down                      | Right              |
     */
    [_MEDIA] = LAYOUT(
        RESET  , BL_STEP, KC_STOP,
        _______, KC_HOME, RGB_MOD,
        KC_MPRV, KC_END , KC_MNXT
    ),
};

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
                if (smod) {
                    reset_keyboard();
                } elif (dmod) {
                    tap_code(KC_MUTE);
                } else {
                    // Return to base layer
                    default_layer_set(X_BASE);
                    layer_state_set(X_BASE);
                }
            }
        break;
    }
    return true;
};

void encoder_update_user(uint8_t index, bool clockwise) {
    if (index == _MIDDLE) {
        if (clockwise) {
            tap_code(KC_DOWN);
        } else {
            tap_code(KC_UP);
        }
    }
}
