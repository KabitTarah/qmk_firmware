#include "kabit.h"

layer_state_t os = _MAC;

// We want to keep track of our current default layer. This starts at COLEMAK. It's easier to keep track this way!
layer_state_t _layer = _COLEMAK;
// We also set our max layer. This way I only have to update one variable if I want to add or remove a layer
layer_state_t _max_layer = _SPEED;

void keyboard_post_init_user(void) {
    // debug_enable = true;
    return;
}

bool get_shift_state(void) {
    return get_mods() & MOD_MASK_SHIFT;
}

bool get_ctrl_state(void) {
    return get_mods() & MOD_MASK_CTRL;
}

bool get_alt_state(void) {
    return get_mods() & MOD_MASK_ALT;
}

bool get_gui_state(void) {
    return get_mods() & MOD_MASK_GUI;
}

#ifdef ENCODER_ENABLE
    bool encoder_update_user(uint8_t index, bool clockwise) {
        if (index == 1) {
            // Volume control
            if (clockwise) {
                tap_code(KC_VOLU);
            } else {
                tap_code(KC_VOLD);
            }
        }
        else if (index == 0) {
            // Page up/Page down
            if (clockwise) {
                tap_code(KC_PGDN);
            } else {
                tap_code(KC_PGUP);
            }
        }
        return true;
    }
#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        switch (keycode) {
            case KT_ESZ:
                // Send shortcut for Eszett (no shifted version)
                SEND_STRING(SS_RALT("s"));
                break;
            case KT_UM_A:
                // Send shortcut for Umlaut a
                if (get_shift_state()) {
                    unregister_code(KC_LSFT);
                    if (os == _MAC) {
                        SEND_STRING(SS_RALT("u")"A");
                    } else {
                        SEND_STRING(SS_RALT("\"")"A");
                    }
                    register_code(KC_LSFT);
                } else {
                    if (os == _MAC) {
                        SEND_STRING(SS_RALT("u")"a");
                    } else {
                        SEND_STRING(SS_RALT("\"")"a");
                    }
                }
                break;
            case KT_UM_O:
                // Send shortcut for Umlaut o
                if (get_shift_state()) {
                    unregister_code(KC_LSFT);
                    if (os == _MAC) {
                        SEND_STRING(SS_RALT("u")"O");
                    } else {
                        SEND_STRING(SS_RALT("\"")"O");
                    }
                    register_code(KC_LSFT);
                } else {
                    if (os == _MAC) {
                        SEND_STRING(SS_RALT("u")"o");
                    } else {
                        SEND_STRING(SS_RALT("\"")"o");
                    }
                }
                break;
            case KT_UM_U:
                // Send shortcut for Umlaut u
                if (get_shift_state()) {
                    unregister_code(KC_LSFT);
                    if (os == _MAC) {
                        SEND_STRING(SS_RALT("u")"U");
                    } else {
                        SEND_STRING(SS_RALT("\"")"U");
                    }
                    register_code(KC_LSFT);
                } else {
                    if (os == _MAC) {
                        SEND_STRING(SS_RALT("u")"u");
                    } else {
                        SEND_STRING(SS_RALT("\"")"u");
                    }
                }
                break;
            case KM_PPX1:
                SEND_STRING("ppx1");
                break;
            case KM_PAU2:
                SEND_STRING("pau2");
                break;
            case KM_PMI2:
                SEND_STRING("pmi2");
                break;
            case KM_PSE1:
                SEND_STRING("pse1");
                break;
            case KM_PP13:
                SEND_STRING("pip13");
                break;
            case KM_PP14:
                SEND_STRING("pip14");
                break;
            case KM_PIN2:
                SEND_STRING("pin2");
                break;
            case KM_PNA1:
                SEND_STRING("pna1");
                break;
            case KM_M1A:
                SEND_STRING("-m1a");
                break;
            case KM_M1C:
                SEND_STRING("-m1c");
                break;
            case KM_M1D:
                SEND_STRING("-m1d");
                break;
            case KM_IDF:
                SEND_STRING("-idf");
                break;
            case KM_IDF1:
                SEND_STRING("-idf1");
                break;
            case KM_INET:
                SEND_STRING("-inet");
                break;
            case KM_LTE:
                SEND_STRING("-lte");
                break;
            case KM_CORE:
                SEND_STRING("-core");
                break;
            case KM_OOB:
                SEND_STRING("-oob");
                break;
            case KM_VEN:
                SEND_STRING("-ven");
                break;
            case KM_ACC:
                SEND_STRING("-acc");
                break;
            case KM_WAN:
                SEND_STRING("-wan");
                break;
            case KM_FW:
                SEND_STRING("-fw");
                break;
            case KM_DIST:
                SEND_STRING("-dist");
                break;
            case KM_SW0:
                SEND_STRING("-sw0");
                break;
            case KM_SW:
                SEND_STRING("-sw");
                break;
        }
    }
    return true;
}

#ifdef LEADER_ENABLE
    // LEADER KEY FUNCTIONALITY
    LEADER_EXTERNS();

    void matrix_scan_user(void) {
        LEADER_DICTIONARY() {
            leading = false;
            leader_end();

            SEQ_ONE_KEY(KC_D) {
                // ** TEST
                SEND_STRING("test...");
            }

            // ************************* //
            // ** COMMUNICATE TO HOST ** //
            SEQ_TWO_KEYS(KC_W, KC_W) {
                // ** WW -> WEATHER REQ
                dprintf("");
            }
            // ************************* //

            // ************************** //
            // ** MANAGE OPERATING SYS ** //
            SEQ_THREE_KEYS(KC_M, KC_A, KC_C) {
                os = _MAC;
            }
            SEQ_THREE_KEYS(KC_W, KC_I, KC_N) {
                os = _WIN;
            }
            SEQ_THREE_KEYS(KC_L, KC_N, KC_X) {
                os = _LINUX;
            }
            // ************************* //

            // *************************** //
            // ** MANAGE BASE LAYER MAP ** //
            SEQ_FOUR_KEYS(KC_Q, KC_W, KC_F, KC_P) {
                // ** QWFP -> QWERTY
                _layer = _QWERTY;
                default_layer_set(X_QWERTY);
                layer_state_set(X_QWERTY);
            }
            SEQ_FOUR_KEYS(KC_Q, KC_W, KC_E, KC_R) {
                // ** QWER -> COLEMAK
                _layer = _COLEMAK;
                default_layer_set(X_COLEMAK);
                layer_state_set(X_COLEMAK);
            }
            SEQ_FOUR_KEYS(KC_F, KC_A, KC_S, KC_T) {
                // ** FAST -> SPEED (MonkeyType)
                _layer = _SPEED;
                default_layer_set(X_SPEED);
                layer_state_set(X_SPEED);
            }
            SEQ_FOUR_KEYS(KC_S, KC_L, KC_O, KC_W) {
                // ** SLOW -> COLEMAK
                _layer = _COLEMAK;
                default_layer_set(X_COLEMAK);
                layer_state_set(X_COLEMAK);
            }
            // *************************** //
        }
    }
#endif
