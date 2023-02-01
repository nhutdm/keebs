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

#ifdef OLED_ENABLE
    static void render_logo(void) {
        static const char PROGMEM raw_logo[] = {
            0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
            0,  0,  0,  0,  0,  0,  0,  0,248,252,142,135,  3,  3,123,127, 14,  0,  0,  0,128,128,128,128,  0,  0,128,224,248,124,118, 31, 15,195,240,252,238, 63, 15,128,128,128,128,128,  0,  0,  0,  0,  0,  0, 24, 60,142,243,255,239, 96, 48, 56, 28, 15,  7,  0,128,128,128,128,128,  0,  0,  0,  0,  0,  0,  0,  0,  0,192,240,252,254, 63, 15,  0,  0,  0,  0,128,128,128,128,  0,  0,  0,  0,128,128,128,128,  0,  0,  0,128,192,  0,  0,  0,  0,  0,  0,  0,128,128,128,128,224,252, 62, 15,  3,  0,  0,  0,  0,  0,  0,  0,  0,
            0,  0,  0,  0,  0, 48,248,252,132,129,131,131,135,207,254,124, 96,252,254,198,255,121, 63, 55,248,252, 31,255, 24, 24, 24,120,255,223,195, 97,120,252,255,223,205,207,103, 51, 24,  0,  0,  0,  0,128,224,252, 63,  7, 15, 28,120,240,224,192,240,252,255,223,205,207,103, 51,124,127,103,240,248,254,222,120,255,255,131,223,246,126, 60,112,252,254,198,255,121, 63, 55,248,252,222,199, 99,249,253,223, 99,112, 28, 15,251,255,222,192,240,252,254,199, 99, 49,253,255,199,192,112, 24,  0,  0,  0,  0,  0,  0,  0,  0,  0,
            0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  1,  1,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0, 31, 31, 27, 15,  7,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  0,  0,  0,  0,  0,  0, 28, 30, 26, 31, 15,  3,  0,  0,  0,  1,  1,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        };

        oled_write_raw_P(raw_logo, sizeof(raw_logo));
    }

    static void print_status_narrow(void) {
        oled_write_P(PSTR("\n\n"), false);
        oled_write_ln_P(PSTR("OS"), false);
        if (keymap_config.swap_lctl_lgui) {
            oled_write_ln_P(PSTR("macOS"), false);
        } else {
            oled_write_ln_P(PSTR("Linux"), false);
        }

        oled_write_P(PSTR("\n"), false);
        oled_write_ln_P(PSTR("MODE"), false);
        switch (get_highest_layer(layer_state)) {
            case _BASE:
                oled_write_ln_P(PSTR("Qwrt"), false);
                break;
            default:
                oled_write_ln_P(PSTR("Mod"), false);
        }

        oled_write_P(PSTR("\n"), false);
        oled_write_P(PSTR("LAYER"), false);
        switch (get_highest_layer(layer_state)) {
            case _BASE:
                oled_write_ln_P(PSTR("Base"), false);
                break;
            case _LOWER:
                oled_write_P(PSTR("Lower"), false);
                break;
            case _RAISE:
                oled_write_P(PSTR("Raise"), false);
                break;
            case _ADJUST:
                oled_write_ln_P(PSTR("Adj"), false);
                break;
            default:
                oled_write_ln_P(PSTR("Undef"), false);
        }

        oled_write_P(PSTR("\n\n"), false);
        led_t led_state = host_keyboard_led_state();
        oled_write_P(PSTR("CPSLK"), led_state.caps_lock);
    }

    oled_rotation_t oled_init_user(oled_rotation_t rotation) {
        if (is_keyboard_master()) {
            return OLED_ROTATION_270;
        }
        return rotation;
    }

    bool oled_task_user(void) {
        if (is_keyboard_master()) {
            print_status_narrow();
        } else {
            render_logo();
        }
        return false;
    }
#endif
