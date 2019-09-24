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
      KC_LSFT, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                      /**/                   KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, \
      KC_LCTL, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_LCTL, KC_LSFT, /**/ KC_BSPC, KC_DEL,  KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ALGR, \
                                 KC_LGUI, KC_LALT, LOWER,   KC_LSFT, KC_ENT,  /**/ KC_BSPC, KC_SPC,  RAISE,   KC_TAB,  KC_LEAD
    ),
    [_LOWER] = LAYOUT(
      _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                                            KC_SLSH, KC_7,    KC_8,    KC_9,    KC_MINS, _______, \
      _______, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,                                           KC_ASTR, KC_4,    KC_5,    KC_6,    KC_PLUS, _______, \
      _______, KC_F11,  KC_F12,  KC_F13,  KC_F14,  KC_F15,  _______, _______,      _______, _______, KC_COMM, KC_1,    KC_2,    KC_3,    KC_EQL,  _______, \
                                 _______, _______, _______, _______, _______,      _______, KC_RALT, _______, KC_0,    _______
    ),
    [_RAISE] = LAYOUT(
      KC_TILD, KC_PLUS, KC_MINS, KC_LBRC, KC_RBRC, _______,                                          KC_PGUP, KC_HOME, KC_UP,   KC_END,  _______, _______, \
      KC_GRV,  KC_EQL,  KC_UNDS, KC_LPRN, KC_RPRN, KC_BSLS,                                          KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______, \
      _______, _______, _______, KC_LCBR, KC_RCBR, _______, _______, _______,      _______, _______, _______, _______, _______, _______, _______, _______, \
                                 _______, _______, _______, _______, _______,      _______, _______, _______, _______, _______
    ),
    [_ADJUST] = LAYOUT(
      _______, _______, _______, _______, _______, _______,                                          _______, _______, KC_VOLU, RGB_TOG, RGB_VAD, RGB_VAI, \
      _______, _______, _______, _______, _______, _______,                                          _______, KC_MPRV, KC_MPLY, KC_MNXT, RGB_HUD, RGB_HUI, \
      _______, _______, _______, _______, _______, _______, _______, _______,      _______, _______, _______, _______, KC_VOLD, KC_MUTE, RGB_SAD, RGB_SAI, \
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
      // Discord bongocat
      SEND_STRING(":bongocat:"SS_TAP(X_ENTER));
    }
    SEQ_TWO_KEYS(KC_S, KC_S) {
      // Windows screenshot
      SEND_STRING(SS_LGUI(SS_LSFT("S")));
    }
  }
}

void led_set_user(uint8_t usb_led) {

}

#ifdef OLED_DRIVER_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
	return OLED_ROTATION_180;
}

static void render_qmk_logo(void) {
  static const char PROGMEM qmk_logo[] = {
    0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,0x90,0x91,0x92,0x93,0x94,
    0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,0xb0,0xb1,0xb2,0xb3,0xb4,
    0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,0xd0,0xd1,0xd2,0xd3,0xd4,0};

  oled_write_P(qmk_logo, false);
}

static void render_status(void) {
  render_qmk_logo();
  // Host Keyboard Layer Status
  oled_write_P(PSTR("Layer: "), false);
  switch (get_highest_layer(layer_state)) {
    case _QWERTY:
      oled_write_P(PSTR("Default\n"), false);
      break;
    case _LOWER:
      oled_write_P(PSTR("LOWER\n"), false);
      break;
    case _RAISE:
      oled_write_P(PSTR("RAISE\n"), false);
      break;
    case _ADJUST:
      oled_write_P(PSTR("ADJUST\n"), false);
      break;

    default:
      // Or use the write_ln shortcut over adding '\n' to the end of your string
      oled_write_ln_P(PSTR("Undefined"), false);
  }

  // Host Keyboard LED Status
  uint8_t led_usb_state = host_keyboard_leds();
  oled_write_P("\n", false);
  oled_write_P(led_usb_state & (1<<USB_LED_NUM_LOCK) ? PSTR("NUMLCK ") : PSTR("       "), false);
  oled_write_P(led_usb_state & (1<<USB_LED_CAPS_LOCK) ? PSTR("CAPLCK ") : PSTR("       "), false);
  oled_write_P(led_usb_state & (1<<USB_LED_SCROLL_LOCK) ? PSTR("SCRLCK ") : PSTR("       "), false);
}

void oled_task_user(void) {
  if (is_keyboard_master()) {
    render_status();     // Renders the current keyboard state (layer, lock, caps, scroll, etc)
  } else {
    render_qmk_logo();
    oled_write_P(PSTR("Kyria rev0.6 alpha\n"), false);
    oled_write_P(PSTR("splitkb.com\n"), false);
    oled_write_P(PSTR("Thomas Baart\n"), false);
    oled_write_P(PSTR("thomasbaart.nl\n"), false);
  }
}
#endif

void encoder_update_user(uint8_t index, bool clockwise) {
  if (index == 0) {
     switch (biton32(layer_state)) {
      case _QWERTY:
        if (clockwise) {
          SEND_STRING(SS_LCTRL("z"));
        } else {
          SEND_STRING(SS_LCTRL("y"));
        }
        break;

      default:
        // other layers - =/+ (quals/plus) (CW) and -/_ (minus/underscore) (CCW)
        if (clockwise) {
          tap_code(KC_EQL);
        } else {
          tap_code(KC_MINS);
        }
        break;
    }
  } else if (index == 1) {
    switch (biton32(layer_state)) {
      case _QWERTY:
        if (clockwise) {
          tap_code(KC_PGDN);
        } else {
          tap_code(KC_PGUP);
        }
        break;

      default:
        if (clockwise) {
          tap_code(KC_VOLU);
        } else {
          tap_code(KC_VOLD);
        }
        break;
    }
  }
}