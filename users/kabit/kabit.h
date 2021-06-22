enum layers {
    _COLEMAK,
    _QWERTY,
    _SPEED,
    _UP,
    _LEFT,
    _RGHT,
    _DOWN,
};

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
    MAC_UM = NEW_SAFE_RANGE,
    VIM_WR,
    KT_CCCV,  // Initiate ctrl-c ctrl-v sequence (OS Specific)
    KT_ESZ,   // Eszett
    KT_UM_A,  // A Umlaut
    KT_UM_U,  // U Umlaut
    KT_UM_O,  // O Umlaut
}

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
#define KQ_J    MT(MOD_LGUI, KC_J)
#define KQ_K    MT(MOD_LSFT, KC_K)
#define KQ_L    MT(MOD_LALT, KC_L)
#define KQ_SCLN MT(MOD_LCTL, KC_SCLN

// !! COLEMAK WITH HOMEROW MODS
// ??         - LEFT SIDE
// .                           +_________+_________+_________+_________+_________+
#define _____COLEMAK_ROW_1L_____ KC_Q    , KC_W    , KC_F    , KC_P    , KC_G
// .                           +_________+_________+_________+_________+_________+
#define _____COLEMAK_HRM_2L_____ KT_A    , KT_R    , KT_S    , KT_T    , KC_D
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
#define _____QWERTY_ROW_1L_____ KC_Q    , KC_W    , KC_E    , KC_R    , KC_T
// .                           +_________+_________+_________+_________+_________+
#define _____QWERTY_HRM_2L_____ KT_A    , KT_S    , KT_D    , KT_F    , KC_G
// .                           +_________+_________+_________+_________+_________+
#define _____QWERTY_HRM_3L_____ KT_Z    , KT_X    , KT_C    , KT_V    , KT_B
// .                           +_________+_________+_________+_________+_________+

// ??        - RIGHT SIDE
// .                           +_________+_________+_________+_________+_________+
#define _____QWERTY_ROW_1R_____ KC_Y    , KC_U    , KC_I    , KC_O    , KC_P
// .                           +_________+_________+_________+_________+_________+
#define _____QWERTY_HRM_2R_____ KC_H    , KT_J    , KT_K    , KT_L    , KT_SCLN
// .                           +_________+_________+_________+_________+_________+
#define _____QWERTY_HRM_3R_____ KT_N    , KT_M    , KT_COMM , KT_DOT  , KT_QUOT
// .                           +_________+_________+_________+_________+_________+
