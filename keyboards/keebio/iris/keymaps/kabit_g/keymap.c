/********************************************************************************
 *
 * Kabit keymap for Iris rev4
 * Built by Tarah Tamayo, github @KabitTarah
 *
 * This is an Iris Left-side macro pad / game board layout. It's based on my
 * kabit layout.
 *
 * Board has three layer maps:
 *   Macro Pad   - Volume and music controls
 *               - Backlighting: Trans flag
 *
 *   Anki        - Specifically for Anki fun!
 *               - I have red, orange, green, and blue keycaps for this layout
 *               - Backlighting: Purple & Green (Kabit colors)
 *
 *   Gaming      - I don't play a lot of games.
 *               - But Celeste.
 *               - Backlighting: Rainbow
 *
 * Encoder
 *   - Macro L0  - Volume / Mute
 *   - Anki L0   - Volume / Mute
 *   - Gaming L0 - Volume ONLY
 *   - ALL L1 - Layer shifting
 *
 ********************************************************************************/

#include QMK_KEYBOARD_H

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
//                                          ||/ _ M_GAME
//                                          |||/
//                                          ||||  _ L_A3
//                                          |||| / _ L_A2
//                                          |||| |/ _ L_A1
//                                          |||| ||/ _ M_ANKI
//                                          |||| |||/
//                       Layer Mask _       |||| ||||  _ L_M3       _ Layer #
//                                   \      |||| |||| / _ L_M2     /
//                                   |      |||| |||| |/ _ L_M1    |
//                                   |      |||| |||| ||/ _ M_MACRO  |
enum layer_names {   //              |      |||| |||| |||/         |
    _MACRO,    //  M_MACRO Base: 0x001 = 0b 0000 0000 0001    ---> 0
    _MACRO1,   //          L_M1: 0x002 = 0b 0000 0000 0010    ---> 1
    _MACRO2,   //          L_M2: 0x004 = 0b 0000 0000 0100    ---> 2
    _MACRO3,   //          L_M3: 0x008 = 0b 0000 0000 1000    ---> 3
    _ANKI,     //   M_ANKI Base: 0x010 = 0b 0000 0001 0000    ---> 4
    _ANKI1,    //          L_A1: 0x020 = 0b 0000 0010 0000    ---> 5
    _ANKI2,    //          L_A2: 0x040 = 0b 0000 0100 0000    ---> 6
    _ANKI3,    //          L_A3: 0x080 = 0b 0000 1000 0000    ---> 7
    _GAME,     //   M_GAME BASE: 0x100 = 0b 0001 0000 0000    ---> 8
    _GAME1,    //          L_G1: 0x200 = 0b 0010 0000 0000    ---> 9
    _GAME2,    //          L_G2: 0x400 = 0b 0100 0000 0000    ---> 10
    _GAME3     //          L_G3: 0x800 = 0b 1000 0000 0000    ---> 11
};

// Base Layer Masks
#define X_MACRO	1 << _MACRO
#define X_ANKI	1 << _ANKI
#define X_GAME	1 << _GAME

#define DEAD    KC_NO

// Layer Key Macros
#define M_MACRO   DF(_MACRO)
#define L_M0    TT(_MACRO)
#define L_M1    TT(_MACRO1)
#define L_M2    TT(_MACRO2)
#define L_M3    TT(_MACRO3)
//
#define M_ANKI  DF(_ANKI)
#define L_A0    TT(_ANKI)
#define L_A1    TT(_ANKI1)
#define L_A2    TT(_ANKI2)
#define L_A3    TT(_ANKI3)
//
#define M_GAME   DF(_GAME)
#define L_G0    TT(_GAME)
#define L_G1    TT(_GAME1)
#define L_G2    TT(_GAME2)
#define L_G3    TT(_GAME3)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_MACRO] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
      XXXXXXX, XXXXXXX, XXXXXXX, L_M1,    L_M2,    XXXXXXX,                            DEAD,    DEAD,    DEAD,    DEAD,    DEAD,    DEAD,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                            DEAD,    DEAD,    DEAD,    DEAD,    DEAD,    DEAD,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                            DEAD,    DEAD,    DEAD,    DEAD,    DEAD,    DEAD,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_MUTE,          DEAD,    DEAD,    DEAD,    DEAD,    DEAD,    DEAD,    DEAD,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                     XXXXXXX, XXXXXXX, XXXXXXX,                   DEAD,    DEAD,    DEAD
  //                               └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  ), [_MACRO1] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
      XXXXXXX, XXXXXXX, XXXXXXX, _______, L_M3,    XXXXXXX,                            DEAD,    DEAD,    DEAD,    DEAD,    DEAD,    DEAD,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                            DEAD,    DEAD,    DEAD,    DEAD,    DEAD,    DEAD,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                            DEAD,    DEAD,    DEAD,    DEAD,    DEAD,    DEAD,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          DEAD,    DEAD,    DEAD,    DEAD,    DEAD,    DEAD,    DEAD,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                     XXXXXXX, XXXXXXX, XXXXXXX,                   DEAD,    DEAD,    DEAD
  //                               └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  ), [_MACRO2] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
      XXXXXXX, XXXXXXX, XXXXXXX, L_M3,    _______, XXXXXXX,                            DEAD,    DEAD,    DEAD,    DEAD,    DEAD,    DEAD,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                            DEAD,    DEAD,    DEAD,    DEAD,    DEAD,    DEAD,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
      M_ANKI,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                            DEAD,    DEAD,    DEAD,    DEAD,    DEAD,    DEAD,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
      M_GAME,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          DEAD,    DEAD,    DEAD,    DEAD,    DEAD,    DEAD,    DEAD,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                     XXXXXXX, XXXXXXX, XXXXXXX,                   DEAD,    DEAD,    DEAD
  //                               └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  ), [_MACRO3] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
      XXXXXXX, XXXXXXX, XXXXXXX, _______, _______, XXXXXXX,                            DEAD,    DEAD,    DEAD,    DEAD,    DEAD,    DEAD,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                            DEAD,    DEAD,    DEAD,    DEAD,    DEAD,    DEAD,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                            DEAD,    DEAD,    DEAD,    DEAD,    DEAD,    DEAD,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          DEAD,    DEAD,    DEAD,    DEAD,    DEAD,    DEAD,    DEAD,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                     XXXXXXX, XXXXXXX, XXXXXXX,                   DEAD,    DEAD,    DEAD
  //                               └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  ),

  [_ANKI] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
      XXXXXXX, XXXXXXX, XXXXXXX, L_A1,    L_A2,    XXXXXXX,                            DEAD,    DEAD,    DEAD,    DEAD,    DEAD,    DEAD,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                            DEAD,    DEAD,    DEAD,    DEAD,    DEAD,    DEAD,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                            DEAD,    DEAD,    DEAD,    DEAD,    DEAD,    DEAD,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          DEAD,    DEAD,    DEAD,    DEAD,    DEAD,    DEAD,    DEAD,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                     XXXXXXX, XXXXXXX, XXXXXXX,                   DEAD,    DEAD,    DEAD
  //                               └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  ), [_ANKI1] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
      XXXXXXX, XXXXXXX, XXXXXXX, _______, L_A3,    XXXXXXX,                            DEAD,    DEAD,    DEAD,    DEAD,    DEAD,    DEAD,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                            DEAD,    DEAD,    DEAD,    DEAD,    DEAD,    DEAD,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                            DEAD,    DEAD,    DEAD,    DEAD,    DEAD,    DEAD,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          DEAD,    DEAD,    DEAD,    DEAD,    DEAD,    DEAD,    DEAD,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                     XXXXXXX, XXXXXXX, XXXXXXX,                   DEAD,    DEAD,    DEAD
  //                               └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  ), [_ANKI2] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
      XXXXXXX, XXXXXXX, XXXXXXX, L_A3,    _______, XXXXXXX,                            DEAD,    DEAD,    DEAD,    DEAD,    DEAD,    DEAD,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                            DEAD,    DEAD,    DEAD,    DEAD,    DEAD,    DEAD,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
      M_GAME,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                            DEAD,    DEAD,    DEAD,    DEAD,    DEAD,    DEAD,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
      M_MACRO, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          DEAD,    DEAD,    DEAD,    DEAD,    DEAD,    DEAD,    DEAD,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                     XXXXXXX, XXXXXXX, XXXXXXX,                   DEAD,    DEAD,    DEAD
  //                               └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  ), [_ANKI3] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
      XXXXXXX, XXXXXXX, XXXXXXX, _______, _______, XXXXXXX,                            DEAD,    DEAD,    DEAD,    DEAD,    DEAD,    DEAD,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                            DEAD,    DEAD,    DEAD,    DEAD,    DEAD,    DEAD,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                            DEAD,    DEAD,    DEAD,    DEAD,    DEAD,    DEAD,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          DEAD,    DEAD,    DEAD,    DEAD,    DEAD,    DEAD,    DEAD,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                     XXXXXXX, XXXXXXX, XXXXXXX,                   DEAD,    DEAD,    DEAD
  //                               └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  ),


  [_GAME] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
      XXXXXXX, XXXXXXX, XXXXXXX, L_G1,    L_G2,    XXXXXXX,                            DEAD,    DEAD,    DEAD,    DEAD,    DEAD,    DEAD,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                            DEAD,    DEAD,    DEAD,    DEAD,    DEAD,    DEAD,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                            DEAD,    DEAD,    DEAD,    DEAD,    DEAD,    DEAD,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          DEAD,    DEAD,    DEAD,    DEAD,    DEAD,    DEAD,    DEAD,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                     XXXXXXX, XXXXXXX, XXXXXXX,                   DEAD,    DEAD,    DEAD
  //                               └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  ), [_GAME1] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
      XXXXXXX, XXXXXXX, XXXXXXX, _______, L_G3,    XXXXXXX,                            DEAD,    DEAD,    DEAD,    DEAD,    DEAD,    DEAD,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                            DEAD,    DEAD,    DEAD,    DEAD,    DEAD,    DEAD,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                            DEAD,    DEAD,    DEAD,    DEAD,    DEAD,    DEAD,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          DEAD,    DEAD,    DEAD,    DEAD,    DEAD,    DEAD,    DEAD,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                     XXXXXXX, XXXXXXX, XXXXXXX,                   DEAD,    DEAD,    DEAD
  //                               └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  ), [_GAME2] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
      XXXXXXX, XXXXXXX, XXXXXXX, L_G3,    _______, XXXXXXX,                            DEAD,    DEAD,    DEAD,    DEAD,    DEAD,    DEAD,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                            DEAD,    DEAD,    DEAD,    DEAD,    DEAD,    DEAD,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
      M_MACRO, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                            DEAD,    DEAD,    DEAD,    DEAD,    DEAD,    DEAD,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
      M_ANKI,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          DEAD,    DEAD,    DEAD,    DEAD,    DEAD,    DEAD,    DEAD,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                     XXXXXXX, XXXXXXX, XXXXXXX,                   DEAD,    DEAD,    DEAD
  //                               └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  ), [_GAME3] = LAYOUT( // ANKI
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
      XXXXXXX, XXXXXXX, XXXXXXX, _______, _______, XXXXXXX,                            DEAD,    DEAD,    DEAD,    DEAD,    DEAD,    DEAD,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                            DEAD,    DEAD,    DEAD,    DEAD,    DEAD,    DEAD,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                            DEAD,    DEAD,    DEAD,    DEAD,    DEAD,    DEAD,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          DEAD,    DEAD,    DEAD,    DEAD,    DEAD,    DEAD,    DEAD,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                     XXXXXXX, XXXXXXX, XXXXXXX,                   DEAD,    DEAD,    DEAD
  //                               └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  )
};

void lights_on(layer_state_t state) {
    // This is all probably easier with a bunch of bit masks, but heck
    rgblight_set_layer_state(0, layer_state_cmp(state, _MACRO) || !(layer_state_cmp(state, _ANKI) || layer_state_cmp(state, _GAME)));
    rgblight_set_layer_state(1, layer_state_cmp(state, _ANKI));
    rgblight_set_layer_state(2, layer_state_cmp(state, _GAME));

    rgblight_set_layer_state(3, layer_state_cmp(state, _MACRO1) || layer_state_cmp(state, _ANKI1) || layer_state_cmp(state, _GAME1) ||
        layer_state_cmp(state, _MACRO3) || layer_state_cmp(state, _ANKI3) || layer_state_cmp(state, _GAME3));
    rgblight_set_layer_state(4, layer_state_cmp(state, _MACRO2) || layer_state_cmp(state, _ANKI2) || layer_state_cmp(state, _GAME2) ||
        layer_state_cmp(state, _MACRO3) || layer_state_cmp(state, _ANKI3) || layer_state_cmp(state, _GAME3));
}

void keyboard_post_init_user(void) {
    // Enable the LED layers
    rgblight_layers = backlight_layers;
    default_layer_set(_MACRO);
    layer_state_set(_MACRO);
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
        case _MACRO:
	case _ANKI:
	case _GAME:
	    if (clockwise) {
	        tap_code(KC_VOLU);
	    } else {
	        tap_code(KC_VOLD);
	    }
	    break;
	case _MACRO1:
	case _ANKI1:
	case _GAME1:
	    if (clockwise) {
            tap_code(KC_PGDN);
	    } else {
            tap_code(KC_PGUP);
	    }
	    break;
	case _MACRO2:
	    change = true;
	    if (clockwise) {
            change_to = X_ANKI;
	    } else {
            change_to = X_GAME;
	    }
	    break;
	case _ANKI2:
	    change = true;
	    if (clockwise) {
            change_to = X_GAME;
	    } else {
            change_to = X_MACRO;
	    }
	    break;
	case _GAME2:
	    change = true;
	    if (clockwise) {
            change_to = X_MACRO;
	    } else {
            change_to = X_ANKI;
	    }
	    break;
    }
    if (change) {
        default_layer_set(change_to);
        layer_state_set(change_to);
    }
}
