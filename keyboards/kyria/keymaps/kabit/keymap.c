/* Copyright 2019 Thomas Baart <thomas@splitkb.com>
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

enum layers {
    _COLEMAK,
    _QWERTY,
    _UP,
    _LEFT,
    _RGHT,
    _DOWN,
};

// Base Layer Masks
#define X_COLEMAK	1 << _COLEMAK
#define X_QWERTY	1 << _QWERTY

enum custom_keycodes {
    MAC_UM = SAFE_RANGE,
    VIM_WR,
    KT_CCCV,  // Initiate ctrl-c ctrl-v sequence (OS Specific)
};

// We want to keep track of our current default layer. This starts at COLEMAK. It's easier to keep track this way!
layer_state_t _layer = _COLEMAK;
// We also set our max layer. This way I only have to update one variable if I want to add or remove a layer
layer_state_t _max_layer = _QWERTY;

// Defined keycode macros
#define DEAD    KC_NO
#define KT_A    MT(MOD_LCTL, KC_A)
#define KT_R    MT(MOD_LALT, KC_R)
#define KT_S    MT(MOD_LSFT, KC_S)
#define KT_T    MT(MOD_LGUI, KC_T)
#define KT_N    MT(MOD_LGUI, KC_N)
#define KT_E    MT(MOD_LSFT, KC_E)
#define KT_I    MT(MOD_LALT, KC_I)
#define KT_O    MT(MOD_LCTL, KC_O)
#define KT_X    LT(_DOWN, KC_X)
#define KT_C    LT(_RGHT, KC_C)
#define KT_V    LT(_UP, KC_V)
#define KT_B    LT(_LEFT, KC_B)
#define KT_K    LT(_LEFT, KC_K)
#define KT_M    LT(_UP, KC_M)
#define KT_COMM LT(_RGHT, KC_COMM)
#define KT_DOT  LT(_DOWN, KC_DOT)
#define TO_UP   TO(_UP)
#define TO_LEFT TO(_LEFT)
#define TO_RGHT TO(_RGHT)
#define TO_DOWN TO(_DOWN)
#define TT_UP   TT(_UP)
#define TT_LEFT TT(_LEFT)
#define TT_RGHT TT(_RGHT)
#define TT_DOWN TT(_DOWN)
// QWERTY specific changes
#define KQ_S    MT(MOD_LALT, KC_S)
#define KQ_D    MT(MOD_LSFT, KC_D)
#define KQ_F    MT(MOD_LGUI, KC_F)
#define KQ_J    MT(MOD_LGUI, KC_N)
#define KQ_K    MT(MOD_LSFT, KC_E)
#define KQ_L    MT(MOD_LALT, KC_I)
#define KQ_SCLN MT(MOD_LCTL, KC_SCLN)
#define KQ_N    LT(_LEFT, KC_N)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_COLEMAK] = LAYOUT( // **C** COLEMAK BASE LAYER **C**
 // ,------------------------------------------------------------.                                              ,------------------------------------------------------------.
      XXXXXXX,   KC_Q   ,  KC_W   ,  KC_F   ,  KC_P   ,  KC_G   ,                                                 KC_J   ,  KC_L   ,  KC_U   ,  KC_Y   ,  KC_SCLN,  KC_MUTE,
 // |----------+---------+---------+---------+---------+---------|                                              |---------+---------+---------+---------+---------+----------|
      TO_UP  ,   KT_A   ,  KT_R   ,  KT_S   ,  KT_T   ,  KC_D   ,                                                 KC_H   ,  KT_N   ,  KT_E   ,  KT_I   ,  KT_O   ,  TO_RGHT,
 // |----------+---------+---------+---------+---------+---------+---------------------.  ,---------------------+---------+---------+---------+---------+---------+----------|
      TO_LEFT,   KC_Z   ,  KT_X   ,  KT_C   ,  KT_V   ,  KT_B   ,  KC_DEL ,   KC_LEAD,      KT_CCCV,   KC_ESC ,   KT_K   ,  KT_M   ,  KT_COMM,  KT_DOT ,  KC_QUOT,  TO_DOWN,
 // `------------------------------+---------+---------+---------+----------+----------|  |----------+----------+---------+---------+---------+------------------------------'
                                     KC_LCTL,  KC_LALT,  KC_LSFT,  KC_ENT ,   KC_TAB ,      KC_BSPC,   KC_SPC ,   KC_LGUI,  KC_RALT,  KC_RCTL
 //                                `---------+---------+---------+----------+----------|  |----------+----------+---------+---------+---------'
    ),
    [_QWERTY] = LAYOUT( // **C** QWERTY BASE LAYER **C**
 // ,------------------------------------------------------------.                                              ,------------------------------------------------------------.
      XXXXXXX,   KC_Q   ,  KC_W   ,  KC_E   ,  KC_R   ,  KC_T   ,                                                 KC_Y   ,  KC_U   ,  KC_I   ,  KC_O   ,  KC_P   ,  KC_MUTE,
 // |----------+---------+---------+---------+---------+---------|                                              |---------+---------+---------+---------+---------+----------|
      TO_UP  ,   KT_A   ,  KQ_S   ,  KQ_D   ,  KQ_F   ,  KC_G   ,                                                 KC_H   ,  KQ_J   ,  KQ_K   ,  KQ_L   ,  KQ_SCLN,  TO_RGHT,
 // |----------+---------+---------+---------+---------+---------+---------------------.  ,---------------------+---------+---------+---------+---------+---------+----------|
      TO_LEFT,   KC_Z   ,  KT_X   ,  KT_C   ,  KT_V   ,  KT_B   ,  KC_DEL ,   KC_LEAD,      KT_CCCV,   KC_ESC ,   KQ_N   ,  KT_M   ,  KT_COMM,  KT_DOT ,  KC_QUOT,  TO_DOWN,
 // `------------------------------+---------+---------+---------+----------+----------|  |----------+----------+---------+---------+---------+------------------------------'
                                     KC_LCTL,  KC_LALT,  KC_LSFT,  KC_ENT ,   KC_TAB ,      KC_BSPC,   KC_SPC ,   KC_LGUI,  KC_RALT,  KC_RCTL
 //                                `---------+---------+---------+----------+----------|  |----------+----------+---------+---------+---------'
    ),
    [_UP] = LAYOUT( // **C** Symbols layer **C**
 // ,------------------------------------------------------------.                                              ,------------------------------------------------------------.
      XXXXXXX,   KC_PERC,  KC_CIRC,  KC_AMPR,  KC_PIPE,  KC_LBRC,                                                 KC_RBRC,  KC_PLUS,  KC_ASTR,  KC_DLR ,  KC_TILD,  KC_MUTE,
 // |----------+---------+---------+---------+---------+---------|                                              |---------+---------+---------+---------+---------+----------|
      TO_UP  ,   KC_QUES,  KC_EXLM,  KC_SLSH,  KC_BSLS,  KC_LPRN,                                                 KC_RPRN,  KC_EQL ,  KC_QUOT,  KC_DQUO,  KC_GRAV,  TO_RGHT,
 // |----------+---------+---------+---------+---------+---------+---------------------.  ,---------------------+---------+---------+---------+---------+---------+----------|
      TO_LEFT,   KC_AT  ,  KC_HASH,  KC_COLN,  KC_UNDS,  KC_LCBR,  _______,   _______,      _______,   _______,   KC_RCBR,  KC_MINS,  KC_SCLN,  KC_LT  ,  KC_GT  ,  TO_DOWN,
 // `------------------------------+---------+---------+---------+----------+----------|  |----------+----------+---------+---------+---------+------------------------------'
                                     _______,  _______,  _______,  _______,   _______,      _______,   _______,   _______,  _______,  _______
 //                                `---------+---------+---------+----------+----------|  |----------+----------+---------+---------+---------'
    ),
    [_LEFT] = LAYOUT( // **C** Numpad & Reversed Left Board **C**
 // ,------------------------------------------------------------.                                              ,------------------------------------------------------------.
      XXXXXXX,   KC_SCLN,  KC_Y   ,  KC_U   ,  KC_L   ,  KC_J   ,                                                 KC_7   ,  KC_8   ,  KC_9   ,  KC_PMNS,  KC_PSLS,  KC_MUTE,
 // |----------+---------+---------+---------+---------+---------|                                              |---------+---------+---------+---------+---------+----------|
      TO_UP  ,   KT_O   ,  KT_I   ,  KT_E   ,  KT_N   ,  KC_H   ,                                                 KC_4   ,  KT_5   ,  KT_6   ,  KC_PPLS,  KC_PAST,  TO_RGHT,
 // |----------+---------+---------+---------+---------+---------+---------------------.  ,---------------------+---------+---------+---------+---------+---------+----------|
      TO_LEFT,   KC_QUOT,  KT_DOT ,  KT_COMM,  KT_M   ,  KT_K   ,  _______,   _______,      KC_PDOT,   KC_0   ,   KC_1   ,  KC_2   ,  KC_3   ,  KC_PEQL,  KC_ENT ,  TO_DOWN,
 // `------------------------------+---------+---------+---------+----------+----------|  |----------+----------+---------+---------+---------+------------------------------'
                                     _______,  _______,  _______,  _______,   _______,      _______,   _______,   _______,  _______,  _______
 //                                `---------+---------+---------+----------+----------|  |----------+----------+---------+---------+---------'
    ),
    [_RGHT] = LAYOUT( // **C** Number/symbol row and F-keys **C**
 // ,------------------------------------------------------------.                                              ,------------------------------------------------------------.
      XXXXXXX,   KC_EXLM,  KC_AT  ,  KC_HASH,  KC_DLR ,  KC_PERC,                                                 KC_CIRC,  KC_AMPR,  KC_ASTR,  KC_LPRN,  KC_RPRN,  KC_MUTE,
 // |----------+---------+---------+---------+---------+---------|                                              |---------+---------+---------+---------+---------+----------|
      TO_UP  ,   KC_1   ,  KC_2   ,  KC_3   ,  KC_4   ,  KC_5   ,                                                 KC_6   ,  KC_7   ,  KC_8   ,  KC_9   ,  KC_O   ,  TO_RGHT,
 // |----------+---------+---------+---------+---------+---------+---------------------.  ,---------------------+---------+---------+---------+---------+---------+----------|
      TO_LEFT,   KC_F1  ,  KC_F2  ,  KC_F3  ,  KC_F4  ,  KC_F5  ,  KC_F11 ,   KC_F12 ,      KC_F13 ,   KC_F14 ,   KC_F6  ,  KC_F7  ,  KC_F8  ,  KC_F9  ,  KC_F10 ,  TO_DOWN,
 // `------------------------------+---------+---------+---------+----------+----------|  |----------+----------+---------+---------+---------+------------------------------'
                                     _______,  _______,  _______,  _______,   _______,      _______,   _______,   _______,  _______,  _______
 //                                `---------+---------+---------+----------+----------|  |----------+----------+---------+---------+---------'
    ),
    [_DOWN] = LAYOUT( // TBD
 // ,------------------------------------------------------------.                                              ,------------------------------------------------------------.
      XXXXXXX,   _______,  _______,  _______,  _______,  _______,                                                 _______,  _______,  _______,  _______,  _______,  KC_MUTE,
 // |----------+---------+---------+---------+---------+---------|                                              |---------+---------+---------+---------+---------+----------|
      TO_UP  ,   _______,  _______,  _______,  _______,  _______,                                                 _______,  _______,  _______,  _______,  _______,  TO_RGHT,
 // |----------+---------+---------+---------+---------+---------+---------------------.  ,---------------------+---------+---------+---------+---------+---------+----------|
      TO_LEFT,   _______,  _______,  _______,  _______,  _______,  _______,   _______,      _______,   _______,   _______,  _______,  _______,  _______,  _______,  TO_DOWN,
 // `------------------------------+---------+---------+---------+----------+----------|  |----------+----------+---------+---------+---------+------------------------------'
                                     _______,  _______,  _______,  _______,   _______,      _______,   _______,   _______,  _______,  _______
 //                                `---------+---------+---------+----------+----------|  |----------+----------+---------+---------+---------'
    ),
};

layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

#ifdef OLED_DRIVER_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
	return OLED_ROTATION_180;
}

static const char PROGMEM kyria_logo[] = {
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,128,192,224,240,112,120, 56, 60, 28, 30, 14, 14, 14,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7, 14, 14, 14, 30, 28, 60, 56,120,112,240,224,192,128,128,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,192,224,240,124, 62, 31, 15,  7,  3,  1,128,192,224,240,120, 56, 60, 28, 30, 14, 14,  7,  7,135,231,127, 31,255,255, 31,127,231,135,  7,  7, 14, 14, 30, 28, 60, 56,120,240,224,192,128,  1,  3,  7, 15, 31, 62,124,240,224,192,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,240,252,255, 31,  7,  1,  0,  0,192,240,252,254,255,247,243,177,176, 48, 48, 48, 48, 48, 48, 48,120,254,135,  1,  0,  0,255,255,  0,  0,  1,135,254,120, 48, 48, 48, 48, 48, 48, 48,176,177,243,247,255,254,252,240,192,  0,  0,  1,  7, 31,255,252,240,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,255,255,255,  0,  0,  0,  0,  0,254,255,255,  1,  1,  7, 30,120,225,129,131,131,134,134,140,140,152,152,177,183,254,248,224,255,255,224,248,254,183,177,152,152,140,140,134,134,131,131,129,225,120, 30,  7,  1,  1,255,255,254,  0,  0,  0,  0,  0,255,255,255,  0,  0,  0,  0,255,255,  0,  0,192,192, 48, 48,  0,  0,240,240,  0,  0,  0,  0,  0,  0,240,240,  0,  0,240,240,192,192, 48, 48, 48, 48,192,192,  0,  0, 48, 48,243,243,  0,  0,  0,  0,  0,  0, 48, 48, 48, 48, 48, 48,192,192,  0,  0,  0,  0,  0,
    0,  0,  0,255,255,255,  0,  0,  0,  0,  0,127,255,255,128,128,224,120, 30,135,129,193,193, 97, 97, 49, 49, 25, 25,141,237,127, 31,  7,255,255,  7, 31,127,237,141, 25, 25, 49, 49, 97, 97,193,193,129,135, 30,120,224,128,128,255,255,127,  0,  0,  0,  0,  0,255,255,255,  0,  0,  0,  0, 63, 63,  3,  3, 12, 12, 48, 48,  0,  0,  0,  0, 51, 51, 51, 51, 51, 51, 15, 15,  0,  0, 63, 63,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 48, 48, 63, 63, 48, 48,  0,  0, 12, 12, 51, 51, 51, 51, 51, 51, 63, 63,  0,  0,  0,  0,  0,
    0,  0,  0,  0, 15, 63,255,248,224,128,  0,  0,  3, 15, 63,127,255,239,207,141, 13, 12, 12, 12, 12, 12, 12, 12, 30,127,225,128,  0,  0,255,255,  0,  0,128,225,127, 30, 12, 12, 12, 12, 12, 12, 12, 13,141,207,239,255,127, 63, 15,  3,  0,  0,128,224,248,255, 63, 15,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  3,  7, 15, 62,124,248,240,224,192,128,  1,  3,  7, 15, 30, 28, 60, 56,120,112,112,224,224,225,231,254,248,255,255,248,254,231,225,224,224,112,112,120, 56, 60, 28, 30, 15,  7,  3,  1,128,192,224,240,248,124, 62, 15,  7,  3,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  3,  7, 15, 14, 30, 28, 60, 56,120,112,112,112,224,224,224,224,224,224,224,224,224,224,224,224,224,224,224,224,112,112,112,120, 56, 60, 28, 30, 14, 15,  7,  3,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0
};

char oled_register[4][1024];

static void render_loop(void) {

    oled_write_raw_P(kyria_logo, sizeof(kyria_logo));
}

static void render_qmk_logo(void) {
  static const char PROGMEM qmk_logo[] = {
    0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,0x90,0x91,0x92,0x93,0x94,
    0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,0xb0,0xb1,0xb2,0xb3,0xb4,
    0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,0xd0,0xd1,0xd2,0xd3,0xd4,0};

  oled_write_P(qmk_logo, false);
}

static void render_status(void) {
    // QMK Logo and version information
    render_qmk_logo();
    oled_write_P(PSTR("Kyria rev1.4\n\n"), false);

    // Host Keyboard Default Layer
    oled_write_P(PSTR("Base:  "), false);
    switch (_layer) {
        case _COLEMAK:
            oled_write_P(PSTR("COLEMAK\n"), false);
            break;
        case _QWERTY:
            oled_write_P(PSTR("QWERTY\n"), false);
            break;
    }

    // Host Keyboard Layer Status
    oled_write_P(PSTR("Layer: "), false);
    switch (get_highest_layer(layer_state)) {
        case _COLEMAK:
            oled_write_P(PSTR("COLEMAK\n"), false);
            break;
        case _QWERTY:
            oled_write_P(PSTR("QWERTY\n"), false);
            break;
        case _UP:
            oled_write_P(PSTR("Up\n"), false);
            break;
        case _LEFT:
            oled_write_P(PSTR("Left\n"), false);
            break;
        case _RGHT:
            oled_write_P(PSTR("Right\n"), false);
            break;
        case _DOWN:
            oled_write_P(PSTR("Down\n"), false);
            break;
        default:
            oled_write_P(PSTR("HOW U HERE?\n"), false);
    }
}

void oled_task_user(void) {
    if (is_keyboard_left()) {
        render_loop();
    } else {
        render_status(); // Renders the current keyboard state
    }
}
#endif

#ifdef ENCODER_ENABLE
void encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        // Volume control
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    }
    else if (index == 1) {
        // Page up/Page down
        if (clockwise) {
            tap_code(KC_PGDN);
        } else {
            tap_code(KC_PGUP);
        }
    }
}
#endif

// LEADER KEY FUNCTIONALITY
LEADER_EXTERNS();

void matrix_scan_user(void) {
    LEADER_DICTIONARY() {
        leading = false;
        leader_end();

        // ************************* //
        // ** COMMUNICATE TO HOST ** //
        SEQ_TWO_KEYS(KC_W, KC_W) {
            // ** WW -> WEATHER REQ

        }
        // ************************* //

        // *************************** //
        // ** MANAGE BASE LAYER MAP ** //
        SEQ_FOUR_KEYS(KC_Q, KC_W, KC_F, KC_P) {
            // ** QWFP -> QWERTY
            _layer = _QWERTY
            default_layer_set(_QWERTY);
            layer_state_set(_QWERTY);
        }
        SEQ_FOUR_KEYS(KC_Q, KC_W, KC_E, KC_R) {
            // ** QWER -> COLEMAK
            _layer = _COLEMAK
            default_layer_set(_COLEMAK);
            layer_state_set(_COLEMAK);
        }
        // *************************** //

        // ** Boilerplate from docs.qmk.fm
        // SEQ_ONE_KEY(KC_F) {
        //     // Anything you can do in a macro.
        //     SEND_STRING("QMK is awesome.");
        // }
        // SEQ_TWO_KEYS(KC_D, KC_D) {
        //     SEND_STRING(SS_LCTL("a") SS_LCTL("c"));
        // }
        // SEQ_THREE_KEYS(KC_D, KC_D, KC_S) {
        //     SEND_STRING("https://start.duckduckgo.com\n");
        // }
        // SEQ_TWO_KEYS(KC_A, KC_S) {
        //     register_code(KC_LGUI);
        //     register_code(KC_S);
        //     unregister_code(KC_S);
        //     unregister_code(KC_LGUI);
        // }
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
 * Type (Sent)
 * 0x10         = Ack 0x11-0x14 OLED register set
 * 0xF0         = Send Info String. Response to 0xF1
 *
 * Type (Received)
 * 0x11-0x14    = OLED Register set. This sets the OLED data register to the
 *                value received. 0x10 sent as ack.
 * 0xF1         = Req Info String. The Info String is sent as payload to
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
