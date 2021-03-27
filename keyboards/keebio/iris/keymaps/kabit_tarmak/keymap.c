/********************************************************************************
 *
 * Kabit keymap for Iris rev4
 * Built by Tarah Tamayo, github @KabitTarah
 *
 * Board has three layer maps:
 *   English     - US standard mapping with a bit of fun on upper layers
 *               - Backlighting: Trans flag
 *
 *   Programming - Layout optimized for programming / scripting
 *               - Backlighting: Purple & Green (Kabit colors)
 *
 *   German      - I'm learning German and wanted something easier to use
 *               - Backlighting: Rainbow
 *
 * Encoder (In each layer set):
 *   L0 - Volume / Press to mute
 *   L1 - Line up / down
 *   L2 - Base layer change
 *   L3 - Page up / down
 *
 ********************************************************************************/

#include QMK_KEYBOARD_H

enum custom_keycodes {
    MAC_UM = SAFE_RANGE
};

// RGB Underglow
// LEDs are in matrix:
// 2  1  0 .   11 10 9
// 3  4  5 .   6  7  8
//
const rgblight_segment_t PROGMEM layer_tm1_hsv[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 12, HSV_RED}
);

const rgblight_segment_t PROGMEM layer_tm2_hsv[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 12, HSV_ORANGE}
);

const rgblight_segment_t PROGMEM layer_tm3_hsv[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 12, HSV_GREEN}
);

const rgblight_segment_t PROGMEM layer_tm4_hsv[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 12, HSV_BLUE}
);

const rgblight_segment_t PROGMEM layer_colemak_hsv[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 12, HSV_MAGENTA}
);

const rgblight_segment_t* const PROGMEM backlight_layers[] = RGBLIGHT_LAYERS_LIST(
    layer_tm1_hsv,
    layer_tm2_hsv,
    layer_tm3_hsv,
    layer_tm4_hsv,
    layer_colemak_hsv
);

//                                                   _ COLEMAK
//                                                  /
//                       Layer Mask _       |||| ||||  _ TM4        _ Layer #
//                                   \      |||| |||| / _ TM3      /
//                                   |      |||| |||| |/ _ TM2     |
//                                   |      |||| |||| ||/ _ TM1    |
enum layer_names {   //              |      |||| |||| |||/         |
    _TM1,        //            : 0x001 = 0b 0000 0000 0001    ---> 0
    _TM2,        //            : 0x002 = 0b 0000 0000 0010    ---> 1
    _TM3,        //            : 0x004 = 0b 0000 0000 0100    ---> 2
    _TM4,        //            : 0x008 = 0b 0000 0000 1000    ---> 3
    _COLEMAK,    //            : 0x010 = 0b 0000 0001 0000    ---> 4
    _MOD1,       //            : 0x020 = 0b 0000 0010 0000    ---> 5
    _MOD2,       //            : 0x040 = 0b 0000 0100 0000    ---> 6
    _MOD3        //            : 0x080 = 0b 0000 1000 0000    ---> 7
};
int current_layer = _TM1;
// Layer Masks
#define X_LOWER 0x1F
#define X_UPPER 0xE0
#define X_TM1 1 << _TM1
#define X_TM2 1 << _TM2
#define X_TM3 1 << _TM3
#define X_TM4 1 << _TM4
#define X_CMK 1 << _COLEMAK
#define X_M1  1 << _MOD1
#define X_M2  1 << _MOD2
#define X_M3  1 << _MOD3

#define L_M1    TT(_MOD1)
#define L_M2    TT(_MOD2)
#define L_M3    TT(_MOD3)

#define DEAD    KC_NO

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_TM1] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
      KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                               KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
      KC_TAB,  KC_Q,    KC_W,    KC_J,    KC_R,    KC_T,                               KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_GRV,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
      KC_LALT, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                               KC_H,    KC_N,    KC_E,    KC_L,    KC_SCLN, KC_QUOT,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
      KC_LCTL, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_MUTE,          DEAD,    KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_BSLS,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                     L_M2,    KC_LSFT, KC_ENT,                    KC_SPC,  KC_LGUI, L_M1
  //                               └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  ), [_TM2] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
      KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                               KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
      KC_TAB,  KC_Q,    KC_W,    KC_F,    KC_R,    KC_G,                               KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_GRV,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
      KC_LALT, KC_A,    KC_S,    KC_D,    KC_T,    KC_J,                               KC_H,    KC_N,    KC_E,    KC_L,    KC_SCLN, KC_QUOT,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
      KC_LCTL, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_MUTE,          DEAD,    KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_BSLS,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                     L_M2,    KC_LSFT, KC_ENT,                    KC_SPC,  KC_LGUI, L_M1
  //                               └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  ), [_TM3] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
      KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                               KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
      KC_TAB,  KC_Q,    KC_W,    KC_F,    KC_J,    KC_G,                               KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_GRV,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
      KC_LALT, KC_A,    KC_R,    KC_S,    KC_T,    KC_D,                               KC_H,    KC_N,    KC_E,    KC_L,    KC_SCLN, KC_QUOT,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
      KC_LCTL, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_MUTE,          DEAD,    KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_BSLS,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                     L_M2,    KC_LSFT, KC_ENT,                    KC_SPC,  KC_LGUI, L_M1
  //                               └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  ), [_TM4] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
      KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                               KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
      KC_TAB,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,                               KC_J,    KC_U,    KC_I,    KC_Y,    KC_SCLN, KC_GRV,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
      KC_LALT, KC_A,    KC_R,    KC_S,    KC_T,    KC_D,                               KC_H,    KC_N,    KC_E,    KC_L,    KC_O,    KC_QUOT,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
      KC_LCTL, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_MUTE,          DEAD,    KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_BSLS,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                     L_M2,    KC_LSFT, KC_ENT,                    KC_SPC,  KC_LGUI, L_M1
  //                               └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  ),
  [_COLEMAK] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
      KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                               KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
      KC_TAB,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,                               KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_GRV,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
      KC_LALT, KC_A,    KC_R,    KC_S,    KC_T,    KC_D,                               KC_H,    KC_N,    KC_E,    KC_I,    KC_O,    KC_QUOT,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
      KC_LCTL, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_MUTE,          DEAD,    KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_BSLS,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                     L_M2,    KC_LSFT, KC_ENT,                    KC_SPC,  KC_LGUI, L_M1
  //                               └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  ), [_MOD1] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
      KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                               KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
      KC_TAB,  XXXXXXX, XXXXXXX, XXXXXXX, KC_GRV,  KC_LBRC,                            KC_RBRC, KC_DLR,  KC_PERC, XXXXXXX, XXXXXXX, XXXXXXX,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
      KC_RALT, KC_AMPR, KC_PIPE, KC_CIRC, KC_EXLM, KC_LPRN,                            KC_RPRN, KC_EQL,  KC_LT,   KC_GT, XXXXXXX, XXXXXXX,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
      KC_RCTL, XXXXXXX, KC_COLN, KC_DQUO, KC_UNDS, KC_LCBR, KC_F13,           DEAD,    KC_RCBR, KC_MINS, KC_QUOT, KC_QUES, XXXXXXX, XXXXXXX,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                     L_M3,    _______, _______,                   _______, _______, _______
  //                               └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  ), [_MOD2] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
      KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                              KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
      KC_TAB,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,          DEAD,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                     _______, _______, _______,                   _______, _______, L_M3
  //                               └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  ), [_MOD3] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
      KC_ESC,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
      KC_TAB,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,          DEAD,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                     _______, _______, _______,                   _______, _______, _______
  //                               └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  )
};

void lights_on(layer_state_t state) {
    // Loop through main layers to set color
    for (int layer=_TM1; layer <= _COLEMAK; layer++) {
        rgblight_set_layer_state(layer, layer_state_cmp(state, 1 << layer));
    }
}

void keyboard_post_init_user(void) {
    // Enable the LED layers
    rgblight_layers = backlight_layers;
    default_layer_set(_TM1);
    //layer_state_set(_TM1);
    debug_enable = false;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
/*
    switch (keycode) {
        case MAC_UM:
	    if (record->event.pressed) {
	        SEND_STRING(SS_RALT("u")); // send RALT + U = umlaut on Mac
	    }
	    break;
    }
    dprintf("KL: kc: 0x%04X, col: %u, row: %u, pressed: %b, time: %u, interrupt: %b, count: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed, record->event.time, record->tap.interrupted, record->tap.count);
    dprintf("Default: %X  Current: %X  Highest: %X\n\n", default_layer_state, layer_state, get_highest_layer(layer_state));
    */
	return true;
}

/*
layer_state_t default_layer_state_set_user(layer_state_t state) {
    layer_clear();
    lights_on(get_highest_layer(state));
    return state;
}*/

layer_state_t layer_state_set_user(layer_state_t state) {
    // group_mask must have one bit per number of layers per group
    layer_state_t current_mask = 1 << current_layer;
    layer_state_t group_mask = X_UPPER | current_mask;
    layer_state_t state_mask = state & group_mask;

    // If artifacts are left over the applied mask and state will be different. So clear the bad ones out
    // there is a built in for this (layer_and(mask)) but since we're in layer_state_set_user() we have to
    // do all the work ourselves anyway :P -- and this is the best place to check for it. The higher level
    // function shouldn't change anything if nothing changes, but it does.
    if (state_mask != state) {
        layer_state_set(state_mask);
    } else {
        lights_on(state);
    }

    return state_mask;
}

void encoder_update_user(uint8_t index, bool clockwise) {
    // Testing shows that layer state returns 0 if only the default is enabled, even if the default layer is not 0
    layer_state_t kabit_layer = layer_state;
    if (kabit_layer < default_layer_state) {
        kabit_layer = default_layer_state;
    }
    kabit_layer = get_highest_layer(kabit_layer);
    bool change = false;

    if ((kabit_layer & X_UPPER) == 0) {
	    if (clockwise) {
	        tap_code(KC_VOLU);
	    } else {
	        tap_code(KC_VOLD);
	    }
    } else if ((kabit_layer & (1 << _MOD1)) > 0) {
	    if (clockwise) {
            tap_code(KC_PGDN);
	    } else {
            tap_code(KC_PGUP);
	    }
    } else if ((kabit_layer & (1 << _MOD2)) > 0) {
        // Switch layers
        change = true;
        if (clockwise) {
            current_layer++;
            if (current_layer > _COLEMAK) {
                current_layer = _TM1;
            }
        } else {
            current_layer--;
            if (current_layer < _TM1) {
                current_layer = _COLEMAK;
            }
        }
    }
    layer_state_t change_to = 1 << current_layer;

    if (change) {
        default_layer_set(change_to);
        layer_state_set(change_to);
    }
}
