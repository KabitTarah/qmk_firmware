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

/* 
 * CURRENT ISSUES:
 *   - I activate Layer 2 (from current base) to shift to a new base layer
 *     - When setting the new state, the base layer is set, not the base + 2
 *     - This means getting stuck in a mode - further debugs needed
 */
#include QMK_KEYBOARD_H

#define U_ESZ   UC(0xDF)
#define U_UMA   UC(0xE4)
#define U_UME   UC(0xEB)
#define U_UMI   UC(0xEF)
#define U_UMO   UC(0xF6)
#define U_UMU   UC(0xFC)
#define U_THRN  UC(0xFE)
#define U_UMY   UC(0xFF)

// RGB Underglow
const rgblight_segment_t PROGMEM my_rgb_eng_layers[] = RGBLIGHT_LAYER_SEGMENTS(
    {1, 12, HSV_RED}
);
const rgblight_segment_t PROGMEM my_rgb_prog_layers[] = RGBLIGHT_LAYER_SEGMENTS(
    {1, 12, HSV_GREEN}
);
const rgblight_segment_t PROGMEM my_rgb_ger_layers[] = RGBLIGHT_LAYER_SEGMENTS(
    {1, 12, HSV_BLUE}
);

const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    my_rgb_eng_layers,
    my_rgb_prog_layers,
    my_rgb_ger_layers
);


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
    _ENG,        //  M_ENG Base: 0x001 = 0b 0000 0000 0001    ---> 0
    _ENG1,       //        L_E1: 0x002 = 0b 0000 0000 0010    ---> 1
    _ENG2,       //        L_E2: 0x004 = 0b 0000 0000 0100    ---> 2
    _ENG3,       //        L_E3: 0x008 = 0b 0000 0000 1000    ---> 3
    _PROG,       // M_PROG Base: 0x010 = 0b 0000 0001 0000    ---> 4
    _PROG1,      //        L_P1: 0x020 = 0b 0000 0010 0000    ---> 5
    _PROG2,      //        L_P2: 0x040 = 0b 0000 0100 0000    ---> 6
    _PROG3,      //        L_P3: 0x080 = 0b 0000 1000 0000    ---> 7
    _GER,        //  M_GER BASE: 0x100 = 0b 0001 0000 0000    ---> 8
    _GER1,       //        L_G1: 0x200 = 0b 0010 0000 0000    ---> 9
    _GER2,       //        L_G2: 0x400 = 0b 0100 0000 0000    ---> 10
    _GER3        //        L_G3: 0x800 = 0b 1000 0000 0000    ---> 11
};

// Base Layer Masks
#define X_ENG	1 << _ENG
#define X_PROG	1 << _PROG
#define X_GER	1 << _GER

#define DEAD    KC_NO

// Layer Key Macros
#define M_ENG   DF(_ENG)
#define L_E1    TT(_ENG1)
#define L_E2    TT(_ENG2)
#define L_E3    TT(_ENG3)
//
#define M_PROG  DF(_PROG)
#define L_P1    TT(_PROG1)
#define L_P2    TT(_PROG2)
#define L_P3    TT(_PROG3)
//
#define M_GER   DF(_GER)
#define L_G1    TT(_GER1)
#define L_G2    TT(_GER2)
#define L_G3    TT(_GER3)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_ENG] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
      KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                               KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
      L_E2,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                               KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    DEAD,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
      KC_TAB,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                               KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
      KC_LCTL, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_MUTE,          DEAD,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_BSLS,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                     KC_LGUI, KC_LSFT, KC_ENT,                    KC_SPC,  KC_RALT, L_E1
  //                               └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  ), [_ENG1] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
      KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                              KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
      L_E3,    XXXXXXX, XXXXXXX, XXXXXXX, KC_PGUP, XXXXXXX,                            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, DEAD,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
      XXXXXXX, KC_UP,   XXXXXXX, XXXXXXX, XXXXXXX, KC_PGDN,                            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_EQL,  KC_HOME,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
      KC_LEFT, KC_DOWN, KC_RGHT, KC_LALT, KC_LBRC, KC_DEL,  _______,          DEAD,    KC_RCTL, KC_RBRC, XXXXXXX, XXXXXXX, KC_MINS, KC_END,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                     _______, _______, _______,                   _______, _______, _______
  //                               └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  ), [_ENG2] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                            KC_P7,   KC_P8,   KC_P9,   KC_PPLS, XXXXXXX, XXXXXXX,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
      _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                            KC_P4,   KC_P5,   KC_P6,   KC_PMNS, XXXXXXX, DEAD,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
      M_PROG,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                            KC_P1,   KC_P2,   KC_P3,   KC_PAST, XXXXXXX, XXXXXXX,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
      M_GER,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, DEAD,             DEAD,    KC_P0,   KC_PDOT, KC_NLCK, KC_PSLS, XXXXXXX, XXXXXXX,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                     _______, _______, _______,                   _______, _______, L_E3
  //                               └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  ), [_ENG3] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
      KC_F13,  KC_F14,  KC_F15,  KC_F16,  KC_F17,  KC_F18,                             KC_F19,  KC_F20,  KC_F21,  KC_F22,  KC_F23,  KC_F24,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
      _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, DEAD,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_MSTP,                            KC_MPLY, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_BRIU,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_MPRV, DEAD,             DEAD,    KC_MNXT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_BRID,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                     _______, _______, _______,                   _______, _______, _______
  //                               └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  ),
  
  [_PROG] = LAYOUT(
//┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
      KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                               KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
      L_P2,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                               KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    DEAD,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
      KC_TAB,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                               KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
      KC_LCTL, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_MUTE,          DEAD,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_BSLS,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                     KC_LGUI, KC_LSFT, KC_ENT,                    KC_SPC,  KC_RALT, L_P1
  //                               └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  ), [_PROG1] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
      L_P3,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, DEAD,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, DEAD,             DEAD,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                     _______, _______, _______,                   _______, _______, _______
  //                               └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  ), [_PROG2] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
      _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, DEAD,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
      M_ENG,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
      M_GER,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, DEAD,             DEAD,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                     _______, _______, _______,                   _______, _______, L_P3
  //                               └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  ), [_PROG3] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
      _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, DEAD,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, DEAD,             DEAD,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                     _______, _______, _______,                   _______, _______, _______
  //                               └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  ),


  [_GER] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
      KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                               KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
      L_G2,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                               KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    DEAD,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
      KC_TAB,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                               KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
      KC_LCTL, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_MUTE,          DEAD,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_BSLS,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                     KC_LGUI, KC_LSFT, KC_ENT,                    KC_SPC,  KC_RALT, L_G1
  //                               └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  ), [_GER1] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
      L_G3,    XXXXXXX, XXXXXXX, U_UME,   XXXXXXX, U_THRN,                             U_UMY,   U_UMU,   U_UMI,   U_UMO,   XXXXXXX, DEAD,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
      XXXXXXX, U_UMA,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, U_ESZ,   DEAD,             DEAD,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                     _______, _______, _______,                   _______, _______, _______
  //                               └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  ), [_GER2] = LAYOUT( // ANKI
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_ENT,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
      _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, DEAD,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
      M_ENG,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
      M_PROG,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, DEAD,             DEAD,    KC_1,    KC_2,    KC_3,    KC_4,    XXXXXXX, XXXXXXX,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                     XXXXXXX, XXXXXXX, KC_ENT,                    XXXXXXX, XXXXXXX, L_G3
  //                               └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  ), [_GER3] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
      _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, DEAD,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, DEAD,             DEAD,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                     _______, _______, _______,                   _______, _______, _______
  //                               └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  )
};

void keyboard_post_init_user(void) {
    // Enable the LED layers
    rgblight_layers = my_rgb_layers;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
	dprintf("\nDLS: %X CLS: %X HL: %X\n", default_layer_state, layer_state, get_highest_layer(layer_state));
	return true;
}

layer_state_t default_layer_state_set_user(layer_state_t state) {
    layer_clear();
    switch (get_highest_layer(state)) {
        case _ENG:
            rgblight_set_layer_state(0, true);
	    rgblight_set_layer_state(1, false);
	    rgblight_set_layer_state(2, false);
            break;
        case _PROG:
            rgblight_set_layer_state(0, false);
	    rgblight_set_layer_state(1, true);
	    rgblight_set_layer_state(2, false);
            break;
        case _GER:
            rgblight_set_layer_state(0, false);
	    rgblight_set_layer_state(1, false);
	    rgblight_set_layer_state(2, true);
            break;
    }
    return state;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    // Any time we have a layer state transition, ensure all layers are within the current base layer set. Turn off all layers that are not
    // group_mask must have one bit per number of layers per group
    layer_state_t group_mask = 0xF;

    // need to create a bitwise & mask for all allowed layers
    layer_state_t def_layer = default_layer_state;
    layer_state_t shift = 0;
    // Count how far over the default layer is
    while (def_layer > 0) {
        def_layer = def_layer >> 1;
	shift = shift + 1;
    }
    // Shift the group mask the same distance
    layer_state_t mask = group_mask << (shift - 1);
    // Apply the bitmask. This cleans out layers left "on" after the TT(2+base) resets
    layer_state_t state_mask = state & mask;

    // If artifacts are left over the applied mask and state will be different. So clear the bad ones out
    // there is a built in for this (layer_and(mask)) but since we're in layer_state_set_user() we have to
    // do all the work ourselves anyway :P -- and this is the best place to check for it. The higher level
    // function shouldn't change anything if nothing changes, but it does.
    if (state_mask != state) {
        layer_state_set(state_mask);
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
    //layer_state_t diff = kabit_layer - get_highest_layer(default_layer_state) + 1;

    bool change = false;
    layer_state_t change_to;
    switch (kabit_layer) {
        case _ENG:
	case _PROG:
	case _GER:
	    if (clockwise) {
	        tap_code(KC_VOLU);
	    } else {
	        tap_code(KC_VOLD);
	    }
	    break;
	case _ENG1:
	case _PROG1:
	case _GER1:
	    if (clockwise) {
		tap_code(KC_PGDN);
	    } else {
		tap_code(KC_PGUP);
	    }
	    break;
	case _ENG2:
	    change = true;
	    if (clockwise) {
                change_to = X_PROG;
	    } else {
                change_to = X_GER;
	    }
	    break;
	case _PROG2:
	    change = true;
	    if (clockwise) {
                change_to = X_GER;
	    } else {
                change_to = X_ENG;
	    }
	    break;
	case _GER2:
	    change = true;
	    if (clockwise) {
                change_to = X_ENG;
	    } else {
                change_to = X_PROG;
	    }
	    break;
    }
    if (change) {
        default_layer_set(change_to);
	default_layer_state_set_user(change_to);
	layer_state_set(change_to);
    }
}
