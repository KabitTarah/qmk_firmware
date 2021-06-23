/* Copyright 2021 Tarah Tamayo
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
#include "kabit.h"

// Defined keycode macros
// See kabit.h

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_COLEMAK] = LAYOUT_wrapper( // **C** COLEMAK BASE LAYER **C**
 // ,------------------------------------------------------------.                                              ,------------------------------------------------------------.
      XXXXXXX,   _____COLEMAK_ROW_1L_____                       ,                                                 _____COLEMAK_ROW_1R_____                       ,  KC_MUTE,
 // |----------+---------+---------+---------+---------+---------|                                              |---------+---------+---------+---------+---------+----------|
      TT_UP  ,   _____COLEMAK_HRM_2L_____                       ,                                                 _____COLEMAK_HRM_2R_____                       ,  TT_RGHT,
 // |----------+---------+---------+---------+---------+---------+---------------------.  ,---------------------+---------+---------+---------+---------+---------+----------|
      TT_LEFT,   _____COLEMAK_HRM_3L_____                       ,  KC_DEL ,   KC_LEAD,      KT_CCCV,   KC_LGUI,   _____COLEMAK_HRM_3R_____                       ,  TT_DOWN,
 // `------------------------------+---------+---------+---------+----------+----------|  |----------+----------+---------+---------+---------+------------------------------'
                                     KC_LALT,  KC_TAB ,  KC_BSPC,  KC_LSFT,   KC_ESC ,      KC_SPC ,   KC_SPC ,   KC_ENT ,  KC_GRV ,  KC_RALT
 //                                `---------+---------+---------+----------+----------|  |----------+----------+---------+---------+---------'
    ),
    [_QWERTY] = LAYOUT_wrapper( // **C** QWERTY BASE LAYER **C**
 // ,------------------------------------------------------------.                                              ,------------------------------------------------------------.
      XXXXXXX,   _____QWERTY_ROW_1L_____                        ,                                                 _____QWERTY_ROW_1R_____                        ,  KC_MUTE,
 // |----------+---------+---------+---------+---------+---------|                                              |---------+---------+---------+---------+---------+----------|
      TT_UP  ,   _____QWERTY_HRM_2L_____                        ,                                                 _____QWERTY_HRM_2R_____                        ,  TT_RGHT,
 // |----------+---------+---------+---------+---------+---------+---------------------.  ,---------------------+---------+---------+---------+---------+---------+----------|
      TT_LEFT,   _____QWERTY_HRM_3L_____                        ,  KC_DEL ,   KC_LEAD,      KT_CCCV,   KC_LGUI,   _____QWERTY_HRM_3R_____                        ,  TT_DOWN,
 // `------------------------------+---------+---------+---------+----------+----------|  |----------+----------+---------+---------+---------+------------------------------'
                                     KC_LALT,  KC_TAB ,  KC_BSPC,  KC_LSFT,   KC_ESC ,      KC_SPC ,   KC_SPC ,   KC_ENT ,  KC_GRV ,  KC_RALT
 //                                `---------+---------+---------+----------+----------|  |----------+----------+---------+---------+---------'
    ),
    [_SPEED] = LAYOUT_wrapper( // **C** COLEMAK SPEED LAYER **C**
 // ,------------------------------------------------------------.                                              ,------------------------------------------------------------.
      KC_ESC ,   _____COLEMAK_ROW_1L_____                       ,                                                 _____COLEMAK_ROW_1R_____                       ,  KC_MUTE,
 // |----------+---------+---------+---------+---------+---------|                                              |---------+---------+---------+---------+---------+----------|
      XXXXXXX,   _____COLEMAK_ROW_2L_____                       ,                                                 _____COLEMAK_ROW_2R_____                       ,  XXXXXXX,
 // |----------+---------+---------+---------+---------+---------+---------------------.  ,---------------------+---------+---------+---------+---------+---------+----------|
      XXXXXXX,   _____COLEMAK_ROW_3L_____                       ,  KC_DEL ,   KC_LEAD,      KT_CCCV,   KC_LGUI,   _____COLEMAK_ROW_3R_____                       ,  XXXXXXX,
 // `------------------------------+---------+---------+---------+----------+----------|  |----------+----------+---------+---------+---------+------------------------------'
                                     XXXXXXX,  XXXXXXX,  KC_BSPC,  KC_LSFT,   XXXXXXX,      KC_SPC ,   KC_SPC ,   XXXXXXX,  XXXXXXX,  XXXXXXX
 //                                `---------+---------+---------+----------+----------|  |----------+----------+---------+---------+---------'
    ),
    [_UP] = LAYOUT_wrapper( // **C** Symbols layer **C**
 // ,------------------------------------------------------------.                                              ,------------------------------------------------------------.
      XXXXXXX,   KC_PERC,  KC_CIRC,  KC_AMPR,  KC_PIPE,  KC_LBRC,                                                 KC_RBRC,  KC_PLUS,  KC_ASTR,  KC_DLR ,  KC_TILD,  KC_MUTE,
 // |----------+---------+---------+---------+---------+---------|                                              |---------+---------+---------+---------+---------+----------|
      TT_UP  ,   KC_QUES,  KC_EXLM,  KC_SLSH,  KC_BSLS,  KC_LPRN,                                                 KC_RPRN,  KC_EQL ,  KC_DQUO,  KC_LT  ,  KC_GT  ,  TT_RGHT,
 // |----------+---------+---------+---------+---------+---------+---------------------.  ,---------------------+---------+---------+---------+---------+---------+----------|
      TT_LEFT,   KC_AT  ,  KC_HASH,  KC_COLN,  KC_UNDS,  KC_LCBR,  _______,   _______,      _______,   _______,   KC_RCBR,  KC_MINS,  KC_SCLN,  KC_DOT ,  KC_QUOT,  TT_DOWN,
 // `------------------------------+---------+---------+---------+----------+----------|  |----------+----------+---------+---------+---------+------------------------------'
                                     _______,  _______,  _______,  _______,   _______,      _______,   _______,   _______,  _______,  _______
 //                                `---------+---------+---------+----------+----------|  |----------+----------+---------+---------+---------'
    ),
    [_LEFT] = LAYOUT_wrapper( // **C** Numpad & Reversed Left Board **C**
 // ,------------------------------------------------------------.                                              ,------------------------------------------------------------.
      XXXXXXX,   KC_SCLN,  KC_Y   ,  KC_U   ,  KC_L   ,  KC_J   ,                                                 KC_PSLS,  KC_7   ,  KC_8   ,  KC_9   ,  KC_PAST,  KC_MUTE,
 // |----------+---------+---------+---------+---------+---------|                                              |---------+---------+---------+---------+---------+----------|
      TT_UP  ,   KT_O   ,  KT_I   ,  KT_E   ,  KT_N   ,  KC_H   ,                                                 KC_DOT ,  KC_4   ,  KC_5   ,  KC_6   ,  KC_PMNS,  TT_RGHT,
 // |----------+---------+---------+---------+---------+---------+---------------------.  ,---------------------+---------+---------+---------+---------+---------+----------|
      TT_LEFT,   KT_QUOT,  KT_DOT ,  KT_COMM,  KT_M   ,  KT_K   ,  _______,   _______,      _______,   _______,   KC_0   ,  KC_1   ,  KC_2   ,  KC_3   ,  KC_PPLS,  TT_DOWN,
 // `------------------------------+---------+---------+---------+----------+----------|  |----------+----------+---------+---------+---------+------------------------------'
                                     _______,  _______,  _______,  _______,   _______,      KC_LGUI,   _______,   _______,  _______,  _______
 //                                `---------+---------+---------+----------+----------|  |----------+----------+---------+---------+---------'
    ),
    [_RGHT] = LAYOUT_wrapper( // **C** Number/symbol row and F-keys **C**
 // ,------------------------------------------------------------.                                              ,------------------------------------------------------------.
      XXXXXXX,   KC_EXLM,  KC_AT  ,  KC_HASH,  KC_DLR ,  KC_PERC,                                                 KC_CIRC,  KC_AMPR,  KC_ASTR,  KC_LPRN,  KC_RPRN,  KC_MUTE,
 // |----------+---------+---------+---------+---------+---------|                                              |---------+---------+---------+---------+---------+----------|
      TT_UP  ,   KC_1   ,  KC_2   ,  KC_3   ,  KC_4   ,  KC_5   ,                                                 KC_6   ,  KC_7   ,  KC_8   ,  KC_9   ,  KC_O   ,  TT_RGHT,
 // |----------+---------+---------+---------+---------+---------+---------------------.  ,---------------------+---------+---------+---------+---------+---------+----------|
      TT_LEFT,   KC_F1  ,  KC_F2  ,  KC_F3  ,  KC_F4  ,  KC_F5  ,  KC_F11 ,   KC_F12 ,      KC_F13 ,   _______,   KC_F6  ,  KC_F7  ,  KC_F8  ,  KC_F9  ,  KC_F10 ,  TT_DOWN,
 // `------------------------------+---------+---------+---------+----------+----------|  |----------+----------+---------+---------+---------+------------------------------'
                                     _______,  _______,  _______,  _______,   _______,      KC_LGUI,   _______,   _______,  _______,  _______
 //                                `---------+---------+---------+----------+----------|  |----------+----------+---------+---------+---------'
    ),
    [_DOWN] = LAYOUT_wrapper( // Movement & Macros
 // ,------------------------------------------------------------.                                              ,------------------------------------------------------------.
      XXXXXXX,   XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,                                                 XXXXXXX,  XXXXXXX,  KC_UP  ,  XXXXXXX,  XXXXXXX,  KC_MUTE,
 // |----------+---------+---------+---------+---------+---------|                                              |---------+---------+---------+---------+---------+----------|
      TT_UP  ,   KT_UM_A,  KT_UM_O,  KT_ESZ ,  KT_UM_U,  XXXXXXX,                                                 XXXXXXX,  KC_LEFT,  KC_DOWN,  KC_RGHT,  XXXXXXX,  TT_RGHT,
 // |----------+---------+---------+---------+---------+---------+---------------------.  ,---------------------+---------+---------+---------+---------+---------+----------|
      TT_LEFT,   XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  KC_DOT ,   _______,      _______,   _______,   XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  TT_DOWN,
 // `------------------------------+---------+---------+---------+----------+----------|  |----------+----------+---------+---------+---------+------------------------------'
                                     _______,  _______,  _______,  _______,   _______,      _______,   _______,   _______,  _______,  _______
 //                                `---------+---------+---------+----------+----------|  |----------+----------+---------+---------+---------'
    ),
    [_MACRO1] = LAYOUT_wrapper( // Macro Layer 1
 // ,------------------------------------------------------------.                                              ,------------------------------------------------------------.
      KC_ESC ,   _____MACRO1_ROW_1L_____                        ,                                                 _____MACRO1_ROW_1R_____                        ,  KC_MUTE,
 // |----------+---------+---------+---------+---------+---------|                                              |---------+---------+---------+---------+---------+----------|
      XXXXXXX,   _____MACRO1_ROW_2L_____                        ,                                                 _____MACRO1_ROW_2R_____                        ,  XXXXXXX,
 // |----------+---------+---------+---------+---------+---------+---------------------.  ,---------------------+---------+---------+---------+---------+---------+----------|
      XXXXXXX,   _____MACRO1_ROW_3L_____                        ,  KC_DEL ,   KC_LEAD,      KT_CCCV,   KC_LGUI,   _____MACRO1_ROW_3R_____                        ,  XXXXXXX,
 // `------------------------------+---------+---------+---------+----------+----------|  |----------+----------+---------+---------+---------+------------------------------'
                                     XXXXXXX,  XXXXXXX,  KC_BSPC,  KC_LSFT,   XXXXXXX,      KC_SPC ,   KC_SPC ,   XXXXXXX,  XXXXXXX,  XXXXXXX
 //                                `---------+---------+---------+----------+----------|  |----------+----------+---------+---------+---------'
    ),
    [_MACRO2] = LAYOUT_wrapper( // Macro Layer 2
 // ,------------------------------------------------------------.                                              ,------------------------------------------------------------.
      KC_ESC ,   _____MACROS_XXXXXX_____                        ,                                                 _____MACROS_XXXXXX_____                        ,  KC_MUTE,
 // |----------+---------+---------+---------+---------+---------|                                              |---------+---------+---------+---------+---------+----------|
      XXXXXXX,   _____MACROS_XXXXXX_____                        ,                                                 _____MACROS_XXXXXX_____                        ,  XXXXXXX,
 // |----------+---------+---------+---------+---------+---------+---------------------.  ,---------------------+---------+---------+---------+---------+---------+----------|
      XXXXXXX,   _____MACROS_XXXXXX_____                        ,  KC_DEL ,   KC_LEAD,      KT_CCCV,   KC_LGUI,   _____MACROS_XXXXXX_____                        ,  XXXXXXX,
 // `------------------------------+---------+---------+---------+----------+----------|  |----------+----------+---------+---------+---------+------------------------------'
                                     XXXXXXX,  XXXXXXX,  KC_BSPC,  KC_LSFT,   XXXXXXX,      KC_SPC ,   KC_SPC ,   XXXXXXX,  XXXXXXX,  XXXXXXX
 //                                `---------+---------+---------+----------+----------|  |----------+----------+---------+---------+---------'
    ),
};

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
/*
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
*/
