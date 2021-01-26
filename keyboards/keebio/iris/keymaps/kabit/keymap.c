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

enum unicode_keys {
    ESZ,
    UM_A,
    UM_E,
    UM_I,
    UM_O,
    UM_U,
    THRN,
    UM_Y,
    UMCA,
    UMCE,
    UMCI,
    UMCO,
    UMCU,
    THCN
};

const uint32_t PROGMEM unicode_map[] = {
    [ESZ] = 0x00DF,
    [UM_A] = 0x00E4,
    [UM_E] = 0x00EB,
    [UM_I] = 0x00EF,
    [UM_O] = 0x00F6,
    [UM_U] = 0x00FC,
    [THRN] = 0x00FE,
    [UM_Y] = 0x00FF,
    [UMCA] = 0x00C4,
    [UMCE] = 0x00CB,
    [UMCI] = 0x00CF,
    [UMCO] = 0x00D6,
    [UMCU] = 0x00DC,
    [THCN] = 0x00DE
};

#define XU_A XP(UM_A, UMCA)
#define XU_E XP(UM_E, UMCE)
#define XU_I XP(UM_I, UMCI)
#define XU_O XP(UM_O, UMCO)
#define XU_U XP(UM_U, UMCU)
#define XU_T XP(THRN, THCN)
#define XU_Y X(UM_Y)
#define XU_B X(ESZ)

// RGB Underglow
// LEDs are in matrix:
// 2  1  0 .   11 10 9
// 3  4  5 .   6  7  8
//
const rgblight_segment_t PROGMEM layer_eng_hsv[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 2, HSV_MAGENTA},
    {2, 2, HSV_CYAN},
    {4, 2, HSV_MAGENTA},
    {6, 1, HSV_WHITE},
    {7, 1, HSV_MAGENTA},
    {8, 2, HSV_CYAN},
    {10, 1, HSV_MAGENTA},
    {11, 1, HSV_WHITE}
);

const rgblight_segment_t PROGMEM layer_prog_hsv[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 1, HSV_GREEN},
    {1, 2, HSV_PURPLE},
    {3, 1, HSV_GREEN},
    {4, 1, HSV_PURPLE},
    {5, 2, HSV_GREEN},
    {6, 1, HSV_GREEN},
    {7, 1, HSV_PURPLE},
    {8, 1, HSV_GREEN},
    {9, 2, HSV_PURPLE},
    {11, 1, HSV_GREEN}
);

const rgblight_segment_t PROGMEM layer_ger_hsv[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 1, HSV_YELLOW},
    {1, 1, HSV_GREEN},
    {2, 1, HSV_BLUE},
    {3, 2, HSV_PURPLE},
    {5, 1, HSV_BLUE},
    {6, 1, HSV_GREEN},
    {7, 1, HSV_YELLOW},
    {8, 1, HSV_ORANGE},
    {9, 2, HSV_RED},
    {11, 1, HSV_ORANGE}
);

const rgblight_segment_t PROGMEM layer_1_hsv[] = RGBLIGHT_LAYER_SEGMENTS(
    {5, 1, HSV_RED}
);
const rgblight_segment_t PROGMEM layer_2_hsv[] = RGBLIGHT_LAYER_SEGMENTS(
    {6, 1, HSV_RED}
);

const rgblight_segment_t* const PROGMEM backlight_layers[] = RGBLIGHT_LAYERS_LIST(
    layer_eng_hsv,
    layer_prog_hsv,
    layer_ger_hsv,
    layer_1_hsv,
    layer_2_hsv
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
#define L_E0    TT(_ENG)
#define L_E1    TT(_ENG1)
#define L_E2    TT(_ENG2)
#define L_E3    TT(_ENG3)
//
#define M_PROG  DF(_PROG)
#define L_P0    TT(_PROG)
#define L_P1    TT(_PROG1)
#define L_P2    TT(_PROG2)
#define L_P3    TT(_PROG3)
//
#define M_GER   DF(_GER)
#define L_G0    TT(_GER)
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
      XXXXXXX, XXXXXXX, KC_UP,   XXXXXXX, XXXXXXX, KC_PGDN,                            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_EQL,  KC_HOME,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
      KC_LALT, KC_LEFT, KC_DOWN, KC_RGHT, KC_LBRC, KC_DEL,  _______,          DEAD,    KC_RCTL, KC_RBRC, XXXXXXX, XXXXXXX, KC_MINS, KC_END,
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
      M_GER,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,          DEAD,    KC_P0,   KC_PDOT, KC_NLCK, KC_PSLS, XXXXXXX, XXXXXXX,
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
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_MPRV, _______,          DEAD,    KC_MNXT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_BRID,
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
      KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                               KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
      L_P3,    XXXXXXX, XXXXXXX, XXXXXXX, KC_GRV,  KC_LBRC,                            KC_RBRC, KC_DLR,  KC_PERC, XXXXXXX, XXXXXXX, DEAD,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
      XXXXXXX, KC_AMPR, KC_PIPE, KC_CIRC, KC_EXLM, KC_LPRN,                            KC_RPRN, KC_EQL,  KC_LT,   KC_GT, XXXXXXX, XXXXXXX,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
      XXXXXXX, XXXXXXX, KC_COLN, KC_DQUO, KC_UNDS, KC_LCBR, _______,          DEAD,    KC_RCBR, KC_MINS, KC_QUOT, KC_QUES, XXXXXXX, XXXXXXX,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                     _______, _______, _______,                   _______, _______, _______
  //                               └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  ), [_PROG2] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
      KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                              KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
      _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, DEAD,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
      M_ENG,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
      M_GER,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,          DEAD,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                     _______, _______, _______,                   _______, _______, L_P3
  //                               └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  ), [_PROG3] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
      KC_ESC,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
      _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, DEAD,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,          DEAD,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
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
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, UC_MOD,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
      L_G3,    XXXXXXX, XXXXXXX, XU_E,    XXXXXXX, XU_T,                               XU_Y,    XU_U,    XU_I,    XU_O,    XXXXXXX, DEAD,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
      XXXXXXX, XU_A,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XU_B,    DEAD,             DEAD,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                     _______, _______, _______,                   _______, _______, _______
  //                               └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  ), [_GER2] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_ENT,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
      _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, DEAD,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
      M_ENG,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
      M_PROG,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, DEAD,             DEAD,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                     _______, _______, _______,                   _______, _______, L_G3
  //                               └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  ), [_GER3] = LAYOUT( // ANKI
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_ENT,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
      _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, DEAD,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, DEAD,             DEAD,    KC_1,    KC_2,    KC_3,    KC_4,    XXXXXXX, XXXXXXX,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                     XXXXXXX, XXXXXXX, KC_ENT,                    XXXXXXX, XXXXXXX, _______
  //                               └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  )
};

void lights_on(layer_state_t state) {
    // This is all probably easier with a bunch of bit masks, but heck
    rgblight_set_layer_state(0, layer_state_cmp(state, _ENG) || !(layer_state_cmp(state, _PROG) || layer_state_cmp(state, _GER)));
    rgblight_set_layer_state(1, layer_state_cmp(state, _PROG));
    rgblight_set_layer_state(2, layer_state_cmp(state, _GER));

    rgblight_set_layer_state(3, layer_state_cmp(state, _ENG1) || layer_state_cmp(state, _PROG1) || layer_state_cmp(state, _GER1) ||
        layer_state_cmp(state, _ENG3) || layer_state_cmp(state, _PROG3) || layer_state_cmp(state, _GER3));
    rgblight_set_layer_state(4, layer_state_cmp(state, _ENG2) || layer_state_cmp(state, _PROG2) || layer_state_cmp(state, _GER2) ||
        layer_state_cmp(state, _ENG3) || layer_state_cmp(state, _PROG3) || layer_state_cmp(state, _GER3));
}

void keyboard_post_init_user(void) {
    // Enable the LED layers
    rgblight_layers = backlight_layers;
    default_layer_set(_ENG);
    layer_state_set(_ENG);
    debug_enable = true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    dprintf("KL: kc: 0x%04X, col: %u, row: %u, pressed: %b, time: %u, interrupt: %b, count: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed, record->event.time, record->tap.interrupted, record->tap.count);
    dprintf("Default: %X  Current: %X  Highest: %X\n\n", default_layer_state, layer_state, get_highest_layer(layer_state));
	return true;
}

/*
layer_state_t default_layer_state_set_user(layer_state_t state) {
    layer_clear();
    lights_on(get_highest_layer(state));
    return state;
}*/

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
        layer_state_set(change_to);
    }
}
