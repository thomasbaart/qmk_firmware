/* Copyright 2018 REPLACE_WITH_YOUR_NAME
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

enum my_keycodes {
  MY_KEYCODE = SAFE_RANGE
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT(
    KC_LEAD,  KC_D,  MY_KEYCODE \
  ),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  return true;
}

void matrix_init_user(void) {
  
}

LEADER_EXTERNS();

void matrix_scan_user(void) {
  LEADER_DICTIONARY() {
    leading = false;
    leader_end();

    SEQ_ONE_KEY(MY_KEYCODE) {
      // Anything you can do in a macro.
      SEND_STRING(SS_LCTRL(SS_LSFT("t")));
    } 
    SEQ_TWO_KEYS(KC_E, KC_D) {
      SEND_STRING(SS_LGUI("r")"cmd"SS_TAP(KC_ENTER)SS_LCTRL("c"));
    }
  }
}

void led_set_user(uint8_t usb_led) {

}
