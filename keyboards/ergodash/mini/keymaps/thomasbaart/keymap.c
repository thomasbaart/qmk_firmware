#include QMK_KEYBOARD_H

extern keymap_config_t keymap_config;

#define _QWERTY 0
#define _LOWER 1
#define _RAISE 2
#define _ADJUST 16

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  ADJUST,
};

#define LWR_TAB LT(_LOWER, KC_TAB)
#define RSE_ESC LT(_RAISE, KC_ESC)
#define BSP_SFT SFT_T(KC_BSPC)
#define SPC_SFT SFT_T(KC_SPC)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  /* Qwerty
   * ,----------------------------------------------------------------------------------------------------------------------.
   * | PScr |   Q  |   W  |   E  |   R  |   T  | pgup |                    | home |   Y  |   U  |   I  |   O  |   P  |  \   |
   * |------+------+------+------+------+------+------+--------------------+------+------+------+------+------+------+------|
   * | Noop |   A  |   S  |   D  |   F  |   G  | pgdn |                    | end  |   H  |   J  |   K  |   L  |   ;  |  "   |
   * |------+------+------+------+------+------+---------------------------+------+------+------+------+------+------+------|
   * | Noop |   Z  |   X  |   C  |   V  |   B  |      |      |      |      |      |   N  |   M  |   ,  |   .  |   /  | - _  |
   * |-------------+------+------+------+------+ Bksp + Del  +------+ Enter+ Space+------+------+------+------+-------------|
   * | Noop | Noop | Menu |||||||| AltGr| Lower|      |      ||||||||      |      | Raise| Lead |||||||| Menu | Noop | Noop |
   * ,----------------------------------------------------------------------------------------------------------------------.
   */
  [_QWERTY] = LAYOUT( \
    KC_PSCR, KC_Q,        KC_W,        KC_E,        KC_R,         KC_T,    KC_PGDN,                     KC_HOME, KC_Y,    KC_U,         KC_I,        KC_O,        KC_P,           KC_BSLS, \
    XXXXXXX, SFT_T(KC_A), GUI_T(KC_S), ALT_T(KC_D), LCTL_T(KC_F), KC_G,    KC_PGUP,                     KC_END,  KC_H,    LCTL_T(KC_J), ALT_T(KC_K), GUI_T(KC_L), SFT_T(KC_SCLN), KC_QUOT, \
    XXXXXXX, KC_Z,        KC_X,        KC_C,        KC_V,         KC_B,    BSP_SFT,                     SPC_SFT, KC_N,    KC_M,         KC_COMM,     KC_DOT,      KC_SLSH,        KC_MINS, \
    XXXXXXX, XXXXXXX,     KC_MENU,                  KC_ALGR,      LWR_TAB, BSP_SFT, KC_DEL,     KC_ENT, SPC_SFT, RSE_ESC, KC_LEAD,                   KC_MENU,     XXXXXXX,        XXXXXXX  \
  ),

  /* Lower
   * ,----------------------------------------------------------------------------------------------------------------------.
   * |      |   !  |   @  |   {  |   }  |   |  |   &  |                    |   ↑  |   /  |   7  |   8  |   9  |   *  |      |
   * |------+------+------+------+------+------+------+--------------------+------+------+------+------+------+------+------|
   * |      |   #  |   $  |   (  |   )  |   `  |   *  |                    |   ↓  |   .  |   4  |   5  |   6  |   -  |      |
   * |------+------+------+------+------+------+---------------------------+------+------+------+------+------+------+------|
   * |      |   %  |   ^  |   [  |   ]  |   ~  |      |      |      |      |      |   0  |   1  |   2  |   3  |   +  |   =  |
   * |-------------+------+------+------+------+      +      +------+      +      +------+------+------+------+-------------|
   * |      |      |      ||||||||      |      |      |      ||||||||      |      |      ||||||||      |      |      |      |
   * ,----------------------------------------------------------------------------------------------------------------------.
   */
  [_LOWER] = LAYOUT(
    _______, KC_EXLM,        KC_AT,         KC_LCBR,        KC_RCBR,         KC_PIPE, KC_AMPR,                        KC_UP,   KC_SLSH, KC_7,         KC_8,        KC_9,        KC_ASTR,        _______, \
    _______, SFT_T(KC_HASH), GUI_T(KC_DLR), ALT_T(KC_LPRN), LCTL_T(KC_RPRN), KC_GRV,  KC_ASTR,                        KC_DOWN, KC_DOT,  LCTL_T(KC_4), ALT_T(KC_5), GUI_T(KC_6), SFT_T(KC_MINS), _______, \
    _______, KC_PERC,        KC_CIRC,       KC_LBRC,        KC_RBRC,         KC_TILD, _______,                        _______, KC_0,    KC_1,         KC_2,        KC_3,        KC_PLUS,        KC_EQL,  \
    _______, _______,        _______,                       _______,         _______, _______, _______,      _______, _______, _______, _______,                   _______,     _______,        _______  \
  ),

  /* Raise
   * ,----------------------------------------------------------------------------------------------------------------------.
   * |      |  F1  |  F2  |  F3  |  F4  |  F5  |      |                    |      | volup| back |   ↑  |forwrd|      |      |
   * |------+------+------+------+------+------+------+--------------------+------+------+------+------+------+------+------|
   * |      |  F6  |  F7  |  F8  |  F9  |  F10 |      |                    |      | mute |   ←  |   ↓  |   →  |      |      |
   * |------+------+------+------+------+------+---------------------------+------+------+------+------+------+------+------|
   * |      |  F11 |  F12 |  F13 |  F14 |  F15 |      |      |      |      |      | voldn| prev | play | next |      |      |
   * |-------------+------+------+------+------+      +      +------+      +      +------+------+------+------+-------------|
   * |      |      |      ||||||||      |      |      |      ||||||||      |      |      ||||||||      |      |      |      |
   * ,----------------------------------------------------------------------------------------------------------------------.
   */
  [_RAISE] = LAYOUT(
    _______, KC_F1,        KC_F2,        KC_F3,        KC_F4,         KC_F5,   _______,                        _______, KC_VOLU, KC_WBAK,         KC_UP,          KC_WFWD,         _______, _______, \
    _______, SFT_T(KC_F6), GUI_T(KC_F7), ALT_T(KC_F8), LCTL_T(KC_F9), KC_F10,  _______,                        _______, KC_MUTE, LCTL_T(KC_LEFT), ALT_T(KC_DOWN), GUI_T(KC_RIGHT), KC_LSFT, _______, \
    _______, KC_F11,       KC_F12,       KC_F13,       KC_F14,        KC_F15,  _______,                        _______, KC_VOLD, KC_MPRV,         KC_MPLY,        KC_MNXT,         _______, _______, \
    _______, _______,      _______,                    _______,       _______, _______, _______,      _______, _______, _______, _______,                         _______,         _______, _______  \
  ),

  /* Adjust
   * ,----------------------------------------------------------------------------------------------------------------------.
   * | Reset|      |      |      |      |      |      |                    |bkltup|glowtg|hueinc|satinc|valinc|nxtmod|      |
   * |------+------+------+------+------+------+------+--------------------+------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |                    |bkltdn|      |      |      |      |      |      |
   * |------+------+------+------+------+------+---------------------------+------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |      |      |      |      |bklttg|huedec|satdec|valdec|prvmod|      |
   * |-------------+------+------+------+------+      +      +------+      +      +------+------+------+------+-------------|
   * |      |      |      ||||||||      |      |      |      ||||||||      |      |      ||||||||      |      |      |      |
   * ,----------------------------------------------------------------------------------------------------------------------.
   */
  [_ADJUST] = LAYOUT(
    RESET,   _______, _______, _______, _______, _______, _______,                        BL_INC,  RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, RGB_MOD,  _______, \
    _______, KC_LSFT, KC_LGUI, KC_LALT, KC_LCTL, _______, _______,                        BL_DEC,  _______, KC_LCTL, KC_LALT, KC_LGUI, KC_LSFT,  _______, \
    _______, _______, _______, _______, _______, _______, _______,                        _______, BL_BRTG, RGB_HUD, RGB_SAD, RGB_VAD, RGB_RMOD, _______, \
    _______, _______, _______,          _______, _______, _______, _______,      _______, _______, _______, _______,          _______, _______,  _______  \
  ),
};

uint32_t layer_state_set_user(uint32_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

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
    case ADJUST:
      if (record->event.pressed) {
        layer_on(_ADJUST);
      } else {
        layer_off(_ADJUST);
      }
      return false;
      break;
  }
  return true;
}

LEADER_EXTERNS();

void matrix_scan_user(void) {
  LEADER_DICTIONARY() {
    leading = false;
    leader_end();

    SEQ_ONE_KEY(KC_C) {
      // Calculator
      register_code(KC_CALC);
      unregister_code(KC_CALC);
    }
    SEQ_TWO_KEYS(KC_C, KC_L) {
      // Caps lock
      register_code(KC_CAPS);
      unregister_code(KC_CAPS);
    }
  }
}