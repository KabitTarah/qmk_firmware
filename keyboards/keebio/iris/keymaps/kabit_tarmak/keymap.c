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
#include "print.h"

enum custom_keycodes {
    MAC_UM = SAFE_RANGE,
    VIM_WR,
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
    {0, 12, HSV_YELLOW}
);

const rgblight_segment_t PROGMEM layer_tm4_hsv[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 12, HSV_BLUE}
);

const rgblight_segment_t PROGMEM layer_colemak_hsv[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 12, HSV_MAGENTA}
);

const rgblight_segment_t PROGMEM layer_qwerty_hsv[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 12, HSV_WHITE}
);

const rgblight_segment_t PROGMEM layer_mod1_hsv[] = RGBLIGHT_LAYER_SEGMENTS(
    {5, 1, HSV_CYAN}
);
const rgblight_segment_t PROGMEM layer_mod2_hsv[] = RGBLIGHT_LAYER_SEGMENTS(
    {6, 1, HSV_CYAN}
);

const rgblight_segment_t PROGMEM layer_mod3_hsv[] = RGBLIGHT_LAYER_SEGMENTS(
    {5, 2, HSV_CYAN}
);

const rgblight_segment_t* const PROGMEM backlight_layers[] = RGBLIGHT_LAYERS_LIST(
    layer_tm1_hsv,
    layer_tm2_hsv,
    layer_tm3_hsv,
    layer_tm4_hsv,
    layer_colemak_hsv,
    layer_qwerty_hsv,
    layer_mod1_hsv,
    layer_mod2_hsv,
    layer_mod3_hsv
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
    _QWERTY,     //            : 0x020 = 0b 0000 0010 0000    ---> 5
    _MOD1,       //            : 0x040 = 0b 0000 0100 0000    ---> 6
    _MOD2,       //            : 0x080 = 0b 0000 1000 0000    ---> 7
    _MOD3        //            : 0x100 = 0b 0001 0000 0000    ---> 8
};
layer_state_t current_layer = _TM1;
// Layer Masks
#define X_LOWER 0x1F
#define X_UPPER 0xE0
#define X_TM1 1 << _TM1
#define X_TM2 1 << _TM2
#define X_TM3 1 << _TM3
#define X_TM4 1 << _TM4
#define X_CMK 1 << _COLEMAK
#define X_QWE 1 << _QWERTY
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
  ), [_QWERTY] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
      KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                               KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
      KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                               KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_GRV,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
      KC_LALT, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                               KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
      KC_LCTL, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_MUTE,          DEAD,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_BSLS,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                     L_M2,    KC_LSFT, KC_ENT,                    KC_SPC,  KC_LGUI, L_M1
  //                               └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  ), [_MOD1] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
      KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                               KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
      KC_TAB,  XXXXXXX, KC_COLN, XXXXXXX, KC_GRV,  KC_LBRC,                            KC_RBRC, KC_DLR,  KC_PERC, XXXXXXX, XXXXXXX, XXXXXXX,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
      KC_RALT, KC_AMPR, KC_PIPE, KC_CIRC, KC_EXLM, KC_LPRN,                            KC_RPRN, KC_EQL,  KC_LT,   KC_GT, XXXXXXX, XXXXXXX,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
      KC_RCTL, XXXXXXX, XXXXXXX, KC_DQUO, KC_UNDS, KC_LCBR, KC_F13,           DEAD,    KC_RCBR, KC_MINS, KC_QUOT, KC_QUES, XXXXXXX, XXXXXXX,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                     L_M3,    _______, _______,                   _______, _______, _______
  //                               └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  ), [_MOD2] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
      KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                              KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
      KC_TAB,  XXXXXXX, VIM_WR,  XXXXXXX, XXXXXXX, XXXXXXX,                            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_UP,   XXXXXXX,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,          DEAD,    XXXXXXX, XXXXXXX, XXXXXXX, KC_LEFT, KC_DOWN, KC_RGHT,
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
    layer_state_t default_layer = get_highest_layer(default_layer_state);
    dprintf("Layers:\n");
    dprintf("    Layer State: %X\n", layer_state);
    dprintf("    Default Layer: %u\n", default_layer);
    dprintf("    Current Layer: %u\n", current_layer);

    for (layer_state_t my_layer=_TM1; my_layer <= _QWERTY; my_layer++) {
        dprintf("Lights: layer on? %d\n", default_layer == my_layer);
        dprintf("        my_layer: %u\n", my_layer);
        rgblight_set_layer_state(my_layer, default_layer == my_layer);
    }

    layer_state_t highest_layer = get_highest_layer(state);
    dprintf("    Highest Layer: %u\n", highest_layer);
    for (layer_state_t my_layer=_MOD1; my_layer <= _MOD3; my_layer++) {
        dprintf("Lights: layer on? %d\n", highest_layer == my_layer);
        dprintf("        my_layer: %u\n", my_layer);
        rgblight_set_layer_state(my_layer, highest_layer == my_layer);
    }
}

void keyboard_post_init_user(void) {
    // Enable the LED layers
    rgblight_layers = backlight_layers;
    // default_layer_set(X_TM1);
    // layer_state_set(X_TM1);
    lights_on(0);
    debug_enable = false;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case MAC_UM:
            if (record->event.pressed) {
                SEND_STRING(SS_RALT("u")); // send RALT + U = umlaut on Mac
            }
            break;
        case VIM_WR:
            if (record->event.pressed) {
                SEND_STRING(":w"SS_TAP(X_ENT));
            }
            break;
        }
    dprintf("KL: kc: 0x%04X, col: %u, row: %u, pressed: %b, time: %u, interrupt: %b, count: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed, record->event.time, record->tap.interrupted, record->tap.count);
    dprintf("    Default: %u\n", get_highest_layer(default_layer_state));
    dprintf("    Highest: %u\n", get_highest_layer(layer_state));
    dprintf("    Layer Index: %u\n\n", current_layer);
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
    layer_state_t my_state = state;
    dprintf("\n\nLAYER CHANGE DETECTED! State: %X\n", my_state);
    layer_state_t current_mask = 1 << current_layer;
    dprintf("group_mask = X_UPPER | current_mask = %X | %X\n", X_UPPER, current_mask);
    layer_state_t group_mask = X_UPPER | current_mask;
    dprintf("state_mask = group_mask & state = %X & %X\n", group_mask, my_state);
    layer_state_t state_mask = my_state & group_mask;
    dprintf("current_mask: %X  group_mask: %X  state_mask: %X\n\n", current_mask, group_mask, state_mask);

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
    layer_state_t highest_layer = get_highest_layer(layer_state);
    //layer_state_t default_layer = get_highest_layer(default_layer_state);
    dprintf("Layer State: %X ", layer_state);
    //dprintf("- Default Layer: %u ", default_layer);
    dprintf("- Highest Layer: %u\n", highest_layer);
    bool change = false;

    if (highest_layer < _MOD1) {
	    if (clockwise) {
	        tap_code(KC_VOLU);
	    } else {
	        tap_code(KC_VOLD);
	    }
    } else if (highest_layer == _MOD1) {
	    if (clockwise) {
            tap_code(KC_PGDN);
	    } else {
            tap_code(KC_PGUP);
	    }
    } else if (highest_layer == _MOD2) {
        // Switch layers */
        change = true;
        if (clockwise) {
            current_layer++;
            if (current_layer > _QWERTY) {
                current_layer = _TM1;
            }
        } else {
            if (current_layer == _TM1) {
                current_layer = _QWERTY;
            } else {
                current_layer--;
            }
        }
    }

    if (change) {
        layer_state_t change_to = (1 << current_layer);
        dprintf("Changing Layer to %X", change_to);
        default_layer_set(change_to);
        layer_state_set(change_to + (1 << highest_layer));
    }
}
