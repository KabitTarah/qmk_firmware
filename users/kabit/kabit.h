#pragma once
#ifndef USERSPACE
#define USERSPACE

#include QMK_KEYBOARD_H

bool get_shift_state(void);
bool get_ctrl_state(void);
bool get_alt_state(void);
bool get_gui_state(void);

enum layers {
    _COLEMAK,
    _QWERTY,
    _SPEED,
    _UP,
    _LEFT,
    _RGHT,
    _DOWN,
    _MACRO1,
    _MACRO2,
};

extern layer_state_t os;
extern layer_state_t _layer;
extern layer_state_t _max_layer;

// Base Layer Masks
#define X_COLEMAK	1 << _COLEMAK
#define X_QWERTY	1 << _QWERTY
#define X_SPEED 	1 << _SPEED

enum os_type {
    _MAC,
    _WIN,
    _LINUX,
};

enum custom_keycodes {
    MAC_UM = SAFE_RANGE,
    VIM_WR,
    KT_CCCV,  // Initiate ctrl-c ctrl-v sequence (OS Specific)
    KT_ESZ,   // Eszett
    KT_UM_A,  // A Umlaut
    KT_UM_U,  // U Umlaut
    KT_UM_O,  // O Umlaut
    KM_PPX1,  // MACROS FOLLOW
    KM_PAU2,
    KM_PMI2,
    KM_PSE1,
    KM_PP13,
    KM_PP14,
    KM_PIN2,
    KM_PNA1,
    KM_M1A,
    KM_M1C,
    KM_M1D,
    KM_IDF1,
    KM_IDF,
    KM_INET,
    KM_LTE,
    KM_CORE,
    KM_OOB,
    KM_VEN,
    KM_ACC,
    KM_WAN,
    KM_FW,
    KM_DIST,
    KM_SW0,
    KM_SW,
};

// Defined keycode macros
#define DEAD    KC_NO
#define KM_XXXX KC_NO
#define KT_A    MT(MOD_LCTL, KC_A)
#define KT_R    MT(MOD_LALT, KC_R)
#define KT_S    MT(MOD_LSFT, KC_S)
#define KT_T    MT(MOD_LGUI, KC_T)
#define KT_D    LT(_LEFT, KC_D)
#define KT_N    MT(MOD_LGUI, KC_N)
#define KT_E    MT(MOD_LSFT, KC_E)
#define KT_I    MT(MOD_LALT, KC_I)
#define KT_O    MT(MOD_LCTL, KC_O)
#define KT_Z    LT(_DOWN, KC_Z)
#define KT_X    LT(_RGHT, KC_X)
#define KT_C    LT(_UP, KC_C)
#define KT_V    LT(_LEFT, KC_V)
#define KT_B    LT(_DOWN, KC_B)
#define KT_K    LT(_DOWN, KC_K)
#define KT_M    LT(_LEFT, KC_M)
#define KT_COMM LT(_UP, KC_COMM)
#define KT_DOT  LT(_RGHT, KC_DOT)
#define KT_QUOT LT(_DOWN, KC_QUOT)
#define KT_ESC  LT(_MACRO, KC_ESC)
#define KT_SPC  LT(_MACRO2, KC_SPC)
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
#define KQ_G    LT(_LEFT, KC_G)
#define KQ_J    MT(MOD_LGUI, KC_J)
#define KQ_K    MT(MOD_LSFT, KC_K)
#define KQ_L    MT(MOD_LALT, KC_L)
#define KQ_SCLN MT(MOD_LCTL, KC_SCLN)

#define LAYOUT_wrapper(...) LAYOUT(__VA_ARGS__)

// !! COLEMAK WITH HOMEROW MODS
// ??         - LEFT SIDE
// .                           +_________+_________+_________+_________+_________+
#define _____COLEMAK_ROW_1L_____ KC_Q    , KC_W    , KC_F    , KC_P    , KC_G
// .                           +_________+_________+_________+_________+_________+
#define _____COLEMAK_HRM_2L_____ KT_A    , KT_R    , KT_S    , KT_T    , KT_D
// .                           +_________+_________+_________+_________+_________+
#define _____COLEMAK_HRM_3L_____ KT_Z    , KT_X    , KT_C    , KT_V    , KT_B
// .                           +_________+_________+_________+_________+_________+

// ??         - RIGHT SIDE
// .                           +_________+_________+_________+_________+_________+
#define _____COLEMAK_ROW_1R_____ KC_J    , KC_L    , KC_U    , KC_Y    , KC_SCLN
// .                           +_________+_________+_________+_________+_________+
#define _____COLEMAK_HRM_2R_____ KC_H    , KT_N    , KT_E    , KT_I    , KT_O
// .                           +_________+_________+_________+_________+_________+
#define _____COLEMAK_HRM_3R_____ KT_K    , KT_M    , KT_COMM , KT_DOT  , KT_QUOT
// .                           +_________+_________+_________+_________+_________+

// !! COLEMAK (PLAIN - NO MODS)
// ??         - LEFT SIDE
// .                           +_________+_________+_________+_________+_________+
#define _____COLEMAK_ROW_2L_____ KC_A    , KC_R    , KC_S    , KC_T    , KC_D
// .                           +_________+_________+_________+_________+_________+
#define _____COLEMAK_ROW_3L_____ KC_Z    , KC_X    , KC_C    , KC_V    , KC_B
// .                           +_________+_________+_________+_________+_________+

// ??         - RIGHT SIDE
// .                           +_________+_________+_________+_________+_________+
#define _____COLEMAK_ROW_2R_____ KC_H    , KC_N    , KC_E    , KC_I    , KC_O
// .                           +_________+_________+_________+_________+_________+
#define _____COLEMAK_ROW_3R_____ KC_K    , KC_M    , KC_COMM , KC_DOT  , KC_QUOT
// .                           +_________+_________+_________+_________+_________+

// !! QWERTY WITH HOMEROW MODS
// ??        - LEFT SIDE
// .                           +_________+_________+_________+_________+_________+
#define _____QWERTY_ROW_1L_____  KC_Q    , KC_W    , KC_E    , KC_R    , KC_T
// .                           +_________+_________+_________+_________+_________+
#define _____QWERTY_HRM_2L_____  KT_A    , KQ_S    , KQ_D    , KQ_F    , KQ_G
// .                           +_________+_________+_________+_________+_________+
#define _____QWERTY_HRM_3L_____  KT_Z    , KT_X    , KT_C    , KT_V    , KT_B
// .                           +_________+_________+_________+_________+_________+

// ??        - RIGHT SIDE
// .                           +_________+_________+_________+_________+_________+
#define _____QWERTY_ROW_1R_____  KC_Y    , KC_U    , KC_I    , KC_O    , KC_P
// .                           +_________+_________+_________+_________+_________+
#define _____QWERTY_HRM_2R_____  KC_H    , KQ_J    , KQ_K    , KQ_L    , KQ_SCLN
// .                           +_________+_________+_________+_________+_________+
#define _____QWERTY_HRM_3R_____  KT_N    , KT_M    , KT_COMM , KT_DOT  , KT_QUOT
// .                           +_________+_________+_________+_________+_________+

// !! MACROS
// ?? EMPTY MACRO
#define _____MACROS_XXXXXX_____  KM_XXXX,  KM_XXXX,  KM_XXXX,  KM_XXXX,  KM_XXXX

// !! MACRO Layer 1
// ??        - LEFT SIDE
// .                           +_________+_________+_________+_________+_________+
#define _____MACRO1_ROW_1L_____  KM_XXXX,  KM_XXXX,  KM_PP13,  KM_PP14,  KM_XXXX
// .                           +_________+_________+_________+_________+_________+
#define _____MACRO1_ROW_2L_____  KM_PPX1,  KM_PAU2,  KM_PMI2,  KM_PSE1,  KM_PIN2
// .                           +_________+_________+_________+_________+_________+
#define _____MACRO1_ROW_3L_____  KM_XXXX,  KM_XXXX,  KM_XXXX,  KM_PNA1,  KM_XXXX
// .                           +_________+_________+_________+_________+_________+

// ??        - RIGHT SIDE
// .                           +_________+_________+_________+_________+_________+
#define _____MACRO1_ROW_1R_____  KM_IDF1,  KM_M1A ,  KM_IDF ,  KM_M1C ,  KM_M1D
// .                           +_________+_________+_________+_________+_________+
#define _____MACRO1_ROW_2R_____  KM_VEN ,  KM_CORE,  KM_OOB ,  KM_ACC ,  KM_INET
// .                           +_________+_________+_________+_________+_________+
#define _____MACRO1_ROW_3R_____  KM_FW  ,  KM_DIST,  KM_WAN ,  KM_SW0 ,  KM_LTE
// .                           +_________+_________+_________+_________+_________+

// !! MACRO Layer 2
// ?? Not used yet

#endif
