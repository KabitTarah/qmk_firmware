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
        if (layer_state_is(_DOWN)) {
            if (index == 0) {
                if (clockwise) {
                    tap_code(KC_PGUP);
                } else {
                    tap_code(KC_PGDN);
                }
            } else {
                // Volume Up/Down
                if (clockwise) {
                    tap_code(KC__VOLDOWN);
                } else {
                    tap_code(KC__VOLUP);
                }
            }
        } else {
            if (index == 0) {
                // Page up/Page down
                if (clockwise) {
                    for (int i=0; i<10; i++) {
                        tap_code(KC_UP);
                    }
                } else {
                    for (int i=0; i<10; i++) {
                        tap_code(KC_DOWN);
                    }
                }
            } else {
                // Up / Down
                if (clockwise) {
                    tap_code(KC_UP);
                } else {
                    tap_code(KC_DOWN);
                }
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

    static const char PROGMEM qmk_logo[] = {
        0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,0x90,0x91,0x92,0x93,0x94,
        0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,0xb0,0xb1,0xb2,0xb3,0xb4,
        0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,0xd0,0xd1,0xd2,0xd3,0xd4,0
    };

    char oled_register[4][1024];
    bool enable_animation = false;

    static void render_loop(void) {
        oled_write_raw_P(kyria_logo, sizeof(kyria_logo));
    }

    static void render_qmk_logo(void) {
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
                oled_write_P(PSTR("COLEMAK   "), false);
                break;
            case _QWERTY:
                oled_write_P(PSTR("QWERTY    "), false);
                break;
            case _SPEED:
                oled_write_P(PSTR("SPEED     "), false);
                break;
        }

        // Host Keyboard Layer Status
        dprintf("layer_state: %x", layer_state);
        if (layer_state_is(_UP)) {
            oled_write_P(PSTR("U\n"), false);
        } else {
            oled_write_P(PSTR(" \n"), false);
        }
        oled_write_P(PSTR("                "), false);
        if (layer_state_is(_LEFT)) {
            oled_write_P(PSTR("L"), false);
        } else {
            oled_write_P(PSTR(" "), false);
        }
        oled_write_P(PSTR(" "), false);
        if (layer_state_is(_RGHT)) {
            oled_write_P(PSTR("R\n"), false);
        } else {
            oled_write_P(PSTR(" \n"), false);
        }
        oled_write_P(PSTR("  OS:  "), false);
        switch (os) {
            case _MAC:
                oled_write_P(PSTR("MAC       "), false);
                break;
            case _WIN:
                oled_write_P(PSTR("WINDOWS   "), false);
                break;
            case _LINUX:
                oled_write_P(PSTR("LINUX     "), false);
                break;
        }
        if (layer_state_is(_DOWN)) {
            oled_write_P(PSTR("D\n"), false);
        } else {
            oled_write_P(PSTR(" \n"), false);
        }
    }

    void oled_task_user(void) {
        if (is_keyboard_master()) {
            render_status(); // Renders the current keyboard state
        } else {
            render_loop();
        }
    }
#endif
