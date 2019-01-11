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
#include "trackball.c"

#define _BASE 0
#define _LOWER 1
#define _RAISE 2
#define _ADJUST 3

#define CTLBTN3 LCTL(KC_BTN3)
#define SWTCHTB LCTL(KC_TAB)
#define CLOSEWD LALT(KC_F4)
#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT(
    CLOSEWD, SWTCHTB, \
    KC_WBAK, KC_BTN1, CTLBTN3, KC_BTN2, KC_WFWD, \
    LOWER,            KC_BTN3,          RAISE
  ),
  [_LOWER] = LAYOUT(
    KC_MUTE, KC_MNXT, \
    KC_MPRV, KC_MPLY, _______, _______, _______, \
    _______,          _______,          _______
  ),
  [_RAISE] = LAYOUT(
    _______, _______, \
    _______, _______, _______, _______, _______, \
    _______,          _______,          _______
  ),
  [_ADJUST] = LAYOUT(
    RESET,   _______, \
    _______, _______, _______, _______, _______, \
    _______,          _______,          _______
  )
};

void encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
      switch(biton32(layer_state)) {
        case _LOWER:
          // Volume up/down
          if (clockwise) {
              register_code(KC_VOLU);
              unregister_code(KC_VOLU);
          } else {
              register_code(KC_VOLD);
              unregister_code(KC_VOLD);
          }
          break;
        case _RAISE:
          // Mouse wheel up/down
          if (clockwise) {
              register_code(KC_WH_U);
              unregister_code(KC_WH_U);
          } else {
              register_code(KC_WH_D);
              unregister_code(KC_WH_D);
          }
          break;
        case _BASE:
        default:
          // Page up/down
          if (clockwise) {
              register_code(KC_PGDN);
              unregister_code(KC_PGDN);
          } else {
              register_code(KC_PGUP);
              unregister_code(KC_PGUP);
          }
          break;
      }
    }
}

uint32_t layer_state_set_user(uint32_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  return true;
}

void matrix_init_user(void) {
  // Turn Trackball LED on
  setPinOutput(D7);
  writePinHigh(D7);
}

void matrix_scan_user(void) {
  matrix_scan_trackball();
}

void suspend_power_down_user(void) {
  // Turn Trackball LED off
  setPinOutput(D7);
  writePinLow(D7);
}

void suspend_wakeup_init_user(void) {
  // Turn Trackball LED on
  setPinOutput(D7);
  writePinHigh(D7);
}