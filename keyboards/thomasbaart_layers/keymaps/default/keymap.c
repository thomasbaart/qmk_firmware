#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT( /* Base */
    KC_A,  KC_1,  KC_H, \
      KC_TAB,  KC_SPC   \
  ),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  return true;
}