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

enum custom_keycodes {
  MY_HASH = SAFE_RANGE // Define a new keycode for our tap and hold action
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT( /* Base */
    MY_HASH \                         // Use the custom keycode in the keymap
  ),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  static uint16_t my_hash_timer;

  switch (keycode) {
    case MY_HASH:                     // MY_HASH is our custom keycode             
      if(record->event.pressed){      // When the key is pressed,
        my_hash_timer = timer_read(); // Log the time current time,
        register_code(KC_LCTL);       // Start holding a key.
      } else {
        unregister_code(KC_LCTL);     // When the key is let go,
                                      // Compare the elapsed time with a threshold
        if (timer_elapsed(my_hash_timer) < TAPPING_TERM) {
          SEND_STRING("#");           // If it was within the threshold, it was
                                      // a tap action.
        }
      }
      return false;                   // We handled this keypress
  }
  return true;                        // We didn't handle this keypress
}

void matrix_init_user(void) {

}

void matrix_scan_user(void) {

}

void led_set_user(uint8_t usb_led) {

}
