 /* Copyright 2023 Nhut Duong <hello@nhutduong.com>
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
#include "enums.h"
#include "encoder.c"
#include "oled.c"

#define KC_LCTES    LCTL_T(KC_ESC)
#define KC_LGEQ     LGUI_T(KC_EQL)
#define KC_LABS     LALT_T(KC_BSLS)
#define KC_LCLE     LCTL_T(KC_LEFT)
#define KC_LORG         LT(KC_LOWER, KC_RGHT)
#define KC_RSUP         LT(KC_RAISE, KC_UP)
#define KC_RCDO     RCTL_T(KC_DOWN)
#define KC_RALB     RALT_T(KC_LBRC)
#define KC_RGRB     RGUI_T(KC_RBRC)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT(
        KC_GRV,     KC_1,       KC_2,       KC_3,       KC_4,       KC_5,                               KC_6,       KC_7,       KC_8,       KC_9,       KC_0,       KC_MINS,
        KC_TBCP,    KC_Q,       KC_W,       KC_E,       KC_R,       KC_T,                               KC_Y,       KC_U,       KC_I,       KC_O,       KC_P,       KC_BSDL,
        KC_LCTES,   KC_A,       KC_S,       KC_D,       KC_F,       KC_G,                               KC_H,       KC_J,       KC_K,       KC_L,       KC_SCLN,    KC_QUOT,
        KC_LSFT,    KC_Z,       KC_X,       KC_C,       KC_V,       KC_B,       KC_MUTE,    KC_HOME,    KC_N,       KC_M,       KC_COMM,    KC_DOT,     KC_SLSH,    KC_RSFT,
                    KC_LGEQ,    KC_LABS,    KC_LCLE,    KC_LORG,    KC_ENT,                             KC_SPC,     KC_RSUP,    KC_RCDO,    KC_RALB,    KC_RGRB
    ),

    [_LOWER] = LAYOUT(
        _______,    KC_F1,      KC_F2,      KC_F3,      KC_F4,      KC_F5,                              KC_F6,      KC_F7,      KC_F8,      KC_F9,      KC_F10,     KC_F11,
        _______,    KC_EXLM,    KC_AT,      KC_LCBR,    KC_RCBR,    KC_PIPE,                            KC_PGUP,    KC_7,       KC_8,       KC_9,       KC_ASTR,    KC_F12,
        _______,    KC_HASH,    KC_DLR,     KC_LPRN,    KC_RPRN,    KC_GRV,                             KC_PGDN,    KC_4,       KC_5,       KC_6,       KC_PLUS,    KC_MINS,
        _______,    KC_PERC,    KC_CIRC,    KC_LBRC,    KC_RBRC,    KC_TILD,    _______,    _______,    KC_AMPR,    KC_1,       KC_2,       KC_3,       KC_BSLS,    _______,
                    _______,    _______,    _______,    _______,    _______,                            _______,    KC_ADJUST,  KC_DOT,     KC_0,       KC_EQUAL
    ),

    [_RAISE] = LAYOUT(
        _______,    _______,    _______,    _______,    _______,    _______,                            _______,    _______,    _______,    _______,    _______,    _______,
        _______,    KC_INS,     KC_PSCR,    KC_APP,     XXXXXXX,    XXXXXXX,                            KC_PGUP,    KC_PRVWD,   XXXXXXX,    KC_NXTWD,   KC_DLINE,   _______,
        _______,    KC_LALT,    KC_LCTL,    KC_LSFT,    XXXXXXX,    KC_CAPS,                            KC_PGDN,    KC_LEFT,    KC_DOWN,    KC_UP,      KC_RGHT,    KC_DEL,
        _______,    KC_UNDO,    KC_CUT,     KC_COPY,    KC_PASTE,   XXXXXXX,    _______,    _______,    XXXXXXX,    KC_LSTRT,   XXXXXXX,    KC_LEND,    XXXXXXX,    _______,
                    _______,    _______,    _______,    KC_ADJUST,  _______,                            _______,    _______,    _______,    _______,    _______
    ),

    [_ADJUST] = LAYOUT(
        XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,                            XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,
        QK_BOOT,    RGB_TOG,    RGB_HUI,    RGB_SAI,    RGB_VAI,    RGB_MOD,                            XXXXXXX,    KC_VOLD,    KC_MUTE,    KC_VOLU,    XXXXXXX,    XXXXXXX,
        EE_CLR,     RGB_M_P,    RGB_HUD,    RGB_SAD,    RGB_VAD,    RGB_RMOD,                           XXXXXXX,    KC_MPRV,    KC_MPLY,    KC_MNXT,    XXXXXXX,    XXXXXXX,
        CG_TOGG,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,
                    _______,    _______,    _______,    _______,    _______,                            _______,    _______,    _______,    _______,    _______
    )
};

bool            shift_held = false;
static uint16_t held_shift = 0;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_BASE:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_BASE);
            }
            return false;
        case KC_LOWER:
            if (record->event.pressed) {
                layer_on(_LOWER);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
            } else {
                layer_off(_LOWER);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
            }
            return false;
        case KC_RAISE:
            if (record->event.pressed) {
                layer_on(_RAISE);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
            } else {
                layer_off(_RAISE);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
            }
            return false;
        case KC_ADJUST:
            if (record->event.pressed) {
                layer_on(_ADJUST);
            } else {
                layer_off(_ADJUST);
            }
            return false;
        case KC_PRVWD:
            if (record->event.pressed) {
                if (keymap_config.swap_lctl_lgui) {
                    register_mods(mod_config(MOD_LALT));
                    register_code(KC_LEFT);
                } else {
                    register_mods(mod_config(MOD_LCTL));
                    register_code(KC_LEFT);
                }
            } else {
                if (keymap_config.swap_lctl_lgui) {
                    unregister_mods(mod_config(MOD_LALT));
                    unregister_code(KC_LEFT);
                } else {
                    unregister_mods(mod_config(MOD_LCTL));
                    unregister_code(KC_LEFT);
                }
            }
            return false;
        case KC_NXTWD:
             if (record->event.pressed) {
                if (keymap_config.swap_lctl_lgui) {
                    register_mods(mod_config(MOD_LALT));
                    register_code(KC_RIGHT);
                } else {
                    register_mods(mod_config(MOD_LCTL));
                    register_code(KC_RIGHT);
                }
            } else {
                if (keymap_config.swap_lctl_lgui) {
                    unregister_mods(mod_config(MOD_LALT));
                    unregister_code(KC_RIGHT);
                } else {
                    unregister_mods(mod_config(MOD_LCTL));
                    unregister_code(KC_RIGHT);
                }
            }
            return false;
        case KC_LSTRT:
            if (record->event.pressed) {
                if (keymap_config.swap_lctl_lgui) {
                    register_mods(mod_config(MOD_LCTL));
                    register_code(KC_LEFT);
                } else {
                    register_code(KC_HOME);
                }
            } else {
                if (keymap_config.swap_lctl_lgui) {
                    unregister_mods(mod_config(MOD_LCTL));
                    unregister_code(KC_LEFT);
                } else {
                    unregister_code(KC_HOME);
                }
            }
            return false;
        case KC_LEND:
            if (record->event.pressed) {
                if (keymap_config.swap_lctl_lgui) {
                    register_mods(mod_config(MOD_LCTL));
                    register_code(KC_RIGHT);
                } else {
                    register_code(KC_END);
                }
            } else {
                if (keymap_config.swap_lctl_lgui) {
                    unregister_mods(mod_config(MOD_LCTL));
                    unregister_code(KC_RIGHT);
                } else {
                    unregister_code(KC_END);
                }
            }
            return false;
        case KC_DLINE:
            if (record->event.pressed) {
                register_mods(mod_config(MOD_LCTL));
                register_code(KC_BSPC);
            } else {
                unregister_mods(mod_config(MOD_LCTL));
                unregister_code(KC_BSPC);
            }
            return false;
        case KC_COPY:
            if (record->event.pressed) {
                register_mods(mod_config(MOD_LCTL));
                register_code(KC_C);
            } else {
                unregister_mods(mod_config(MOD_LCTL));
                unregister_code(KC_C);
            }
            return false;
        case KC_PASTE:
            if (record->event.pressed) {
                register_mods(mod_config(MOD_LCTL));
                register_code(KC_V);
            } else {
                unregister_mods(mod_config(MOD_LCTL));
                unregister_code(KC_V);
            }
            return false;
        case KC_CUT:
            if (record->event.pressed) {
                register_mods(mod_config(MOD_LCTL));
                register_code(KC_X);
            } else {
                unregister_mods(mod_config(MOD_LCTL));
                unregister_code(KC_X);
            }
            return false;
        case KC_UNDO:
            if (record->event.pressed) {
                register_mods(mod_config(MOD_LCTL));
                register_code(KC_Z);
            } else {
                unregister_mods(mod_config(MOD_LCTL));
                unregister_code(KC_Z);
            }
            return false;
        case KC_RSFT:
        case KC_LSFT:
            shift_held = record->event.pressed;
            held_shift = keycode;
            break;
        case KC_TBCP:
            if (record->event.pressed) {
                if (shift_held) {
                    unregister_code(held_shift);
                    register_code(KC_CAPS);
                } else {
                    register_code(KC_TAB);
                }
            } else {
                unregister_code(KC_CAPS);
                unregister_code(KC_TAB);
                if (shift_held) {
                    register_code(held_shift);
                }
            }
            return false;
        case KC_BSDL:
            if (record->event.pressed) {
                if (shift_held) {
                    unregister_code(held_shift);
                    register_code(KC_DEL);
                } else {
                    register_code(KC_BSPC);
                }
            } else {
                unregister_code(KC_DEL);
                unregister_code(KC_BSPC);
                if (shift_held) {
                    register_code(held_shift);
                }
            }
            return false;
    }
    return true;
}
