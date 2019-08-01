/* Copyright 2019 Thomas Baart
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

#define _QWERTY 0
#define _LOWER 2
#define _RAISE 3
#define _ADJUST 16

enum kyria_keycodes {
  LOWER = SAFE_RANGE,
  RAISE
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT( /* Base */
      KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                      /**/                   KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC, \
      KC_TAB,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                      /**/                   KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, \
      KC_LALT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_LCTL, KC_PSCR, /**/ KC_DEL,  KC_MENU, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ALGR, \
                                 KC_LGUI, KC_ESC,  LOWER,   KC_LSFT, KC_ENT,  /**/ KC_BSPC, KC_SPC,  RAISE,   KC_TAB,  KC_LEAD
    ),
    [_LOWER] = LAYOUT(
      _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                                            KC_SLSH, KC_7,    KC_8,    KC_9,    KC_MINS, _______, \
      _______, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,                                           KC_ASTR, KC_4,    KC_5,    KC_6,    KC_PLUS, _______, \
      _______, KC_F11,  KC_F12,  KC_F13,  KC_F14,  KC_F15,  _______, _______,      _______, _______, _______, KC_1,    KC_2,    KC_3,    KC_EQL,  _______, \
                                 _______, _______, _______, _______, _______,      _______, _______, _______, KC_0,    _______
    ),
    [_RAISE] = LAYOUT(
      KC_TILD, KC_PLUS, KC_MINS, KC_LBRC, KC_RBRC, _______,                                          KC_PGUP, KC_HOME, KC_UP,   KC_END,  _______, _______, \
      KC_GRV,  KC_EQL,  KC_UNDS, KC_LPRN, KC_RPRN, KC_BSLS,                                          KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______, \
      _______, _______, _______, KC_LCBR, KC_RCBR, _______, _______, _______,      _______, _______, _______, _______, _______, _______, _______, _______, \
                                 _______, _______, _______, _______, _______,      _______, _______, _______, _______, _______
    ),
    [_ADJUST] = LAYOUT(
      _______, _______, _______, _______, _______, _______,                                          _______, _______, KC_VOLU, _______, _______, _______, \
      _______, _______, _______, _______, _______, _______,                                          _______, KC_MPRV, KC_MPLY, KC_MNXT, _______, _______, \
      _______, _______, _______, _______, _______, _______, _______, _______,      _______, _______, _______, _______, KC_VOLD, KC_MUTE, _______, _______, \
                                 _______, _______, _______, _______, _______,      _______, _______, _______, _______, _______
    ),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
  }
  return true;
}

void matrix_init_user(void) {

}

LEADER_EXTERNS();

void matrix_scan_user(void) {
  LEADER_DICTIONARY() {
    leading = false;
    leader_end();

    SEQ_TWO_KEYS(KC_B, KC_C) {
      SEND_STRING(":bongocat:"SS_TAP(X_ENTER));
    }
  }
}

void led_set_user(uint8_t usb_led) {

}
