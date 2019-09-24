#include QMK_KEYBOARD_H
#include "bootloader.h"
#ifdef PROTOCOL_LUFA
  #include "lufa.h"
  #include "split_util.h"
#endif
#ifdef SSD1306OLED
  #include "ssd1306.h"
#endif

#define MODS_SHIFT_MASK (MOD_BIT(KC_LSHIFT)|MOD_BIT(KC_RSHIFT))
#define MODS_CTRL_MASK  (MOD_BIT(KC_LCTL)|MOD_BIT(KC_RCTRL))
#define MODS_ALT_MASK   (MOD_BIT(KC_LALT)|MOD_BIT(KC_RALT))
#define MODS_GUI_MASK   (MOD_BIT(KC_LGUI)|MOD_BIT(KC_RGUI)) 

extern keymap_config_t keymap_config;
extern uint8_t is_master;

#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QWERTY 0
#define _COLEMAK 1
#define _DVORAK 2
#define _LOWER 3
#define _RAISE 4
#define _ADJUST 16

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  COLEMAK,
  DVORAK,
  LOWER,
  RAISE,
  ADJUST,
  BACKLIT,
  RGBRST
};

#define BKS_SHFT mod tap shift backspace
#define RET_LOWR mod tap lower return
#define SPC_RAIS mod tap raise space
#define Z_CTRL mod tap ctrl z
#define X_GUI mod tap gui X
#define C_ALT mod tap gui alt

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT( \
  // TODO: Rework all this into a sensible layout
  // https://github.com/qmk/qmk_firmware/blob/master/users/drashna/wrappers.h
  //,-----------------------------------------------------.    ,-----------------------------------------------------.
       KC_ESC,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,         KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, XXXXXXX,\
  // --------+--------+--------+--------+--------+--------|    |--------+--------+--------+--------+--------+--------|
       KC_TAB,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,         KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, XXXXXXX, \
  // --------+--------+--------+--------+--------+--------|    |--------+--------+--------+--------+--------+--------|
      XXXXXXX,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,         KC_N,    KC_M, KC_COMM,  KC_DOT,KC_SLASH, XXXXXXX,\
  // --------+--------+--------+--------+--------+--------+|  |+--------+--------+--------+--------+--------+--------|
                                KC_LCTRL,BKS_SHFT,RET_LOWR,     SPC_RAIS, KC_RSFT, KC_LEAD \
                              //`--------------------------'  `---------------------------'
  ),

  [_COLEMAK] = LAYOUT( \
  // TODO: Rework all this into a sensible layout
  // https://github.com/qmk/qmk_firmware/blob/master/users/drashna/wrappers.h
  //,-----------------------------------------------------.    ,-----------------------------------------------------.
       KC_ESC,    KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,         KC_J,    KC_L,    KC_U,    KC_Y, KC_SCLN, KC_BSPC,\
  // --------+--------+--------+--------+--------+--------|    |--------+--------+--------+--------+--------+--------|
       KC_TAB,    KC_A,    KC_R,    KC_S,    KC_T,    KC_G,         KC_M,    KC_N,    KC_E,    KC_I,    KC_O,   KC_NO, \
  // --------+--------+--------+--------+--------+--------|    |--------+--------+--------+--------+--------+--------|
      KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_D,    KC_V,         KC_K,    KC_H, KC_COMM,  KC_DOT,KC_SLASH,    RSFT,\
  // --------+--------+--------+--------+--------+--------+|  |+--------+--------+--------+--------+--------+--------|
                       LT(_LOWER,KC_GRV),  KC_SPC, KC_BSPC,       KC_DEL,  KC_ENT,   RAISE \
                              //`--------------------------'  `---------------------------'
  ),

  [_DVORAK] = LAYOUT( \
  // TODO: Rework all this into a sensible layout
  //,-----------------------------------------------------.    ,-----------------------------------------------------.
       KC_ESC, KC_QUOT, KC_COMM,  KC_DOT,    KC_P,    KC_Y,         KC_F,    KC_G,    KC_C,    KC_R,    KC_L, KC_BSPC,\
  // --------+--------+--------+--------+--------+--------|    |--------+--------+--------+--------+--------+--------|
       KC_TAB,    KC_A,    KC_O,    KC_E,    KC_U,    KC_I,         KC_D,    KC_H,    KC_T,    KC_N,    KC_S,   KC_NO, \
  // --------+--------+--------+--------+--------+--------|    |--------+--------+--------+--------+--------+--------|
      KC_LSFT, KC_SCLN,    KC_Q,    KC_J,    KC_K,    KC_X,         KC_B,    KC_M,    KC_W,    KC_V,    KC_Z,    RSFT,\
  // --------+--------+--------+--------+--------+--------+|  |+--------+--------+--------+--------+--------+--------|
                       LT(_LOWER,KC_GRV),  KC_SPC, KC_BSPC,       KC_DEL,  KC_ENT,   RAISE \
                              //`--------------------------'  `---------------------------'
  ),

  [_LOWER] = LAYOUT( \
  //,-----------------------------------------------------.    ,-----------------------------------------------------.
      _______, KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_PERC,      KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC,\
  // --------+--------+--------+--------+--------+--------|    |--------+--------+--------+--------+--------+--------|
      _______,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,      _______, KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR,   KC_NO, \
  // --------+--------+--------+--------+--------+--------|    |--------+--------+--------+--------+--------+--------|
      _______,   KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,      _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT,    RSFT,\
  // --------+--------+--------+--------+--------+--------+|  |+--------+--------+--------+--------+--------+--------|
                                 _______, _______, _______,      _______, _______, _______ \
                              //`--------------------------'  `---------------------------'
  ),

  [_RAISE] = LAYOUT( \
  //,-----------------------------------------------------.    ,-----------------------------------------------------.
      _______,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,         KC_6,    KC_7,    KC_8,    KC_9,    KC_0, _______,\
  // --------+--------+--------+--------+--------+--------|    |--------+--------+--------+--------+--------+--------|
      _______, _______, _______, _______, _______, _______,      _______, KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, _______, \
  // --------+--------+--------+--------+--------+--------|    |--------+--------+--------+--------+--------+--------|
      _______, _______, _______, _______, _______, _______,      _______, KC_HOME, KC_PGDN, KC_PGUP,  KC_END, _______,\
  // --------+--------+--------+--------+--------+--------+|  |+--------+--------+--------+--------+--------+--------|
                                 _______, _______, _______,      _______, _______, _______ \
                              //`--------------------------'  `---------------------------'
  ),

  [_ADJUST] = LAYOUT( \
  //,-----------------------------------------------------.    ,-----------------------------------------------------.
      _______, RGB_MOD, RGB_HUI, RGB_SAI, RGB_VAI, RGB_TOG,      _______, _______, _______, _______, _______, _______,\
  // --------+--------+--------+--------+--------+--------|    |--------+--------+--------+--------+--------+--------|
      _______,  MU_TOG, CK_TOGG,   AU_ON,  AU_OFF, AG_NORM,      AG_SWAP,  QWERTY, COLEMAK,  DVORAK, _______, _______, \
  // --------+--------+--------+--------+--------+--------|    |--------+--------+--------+--------+--------+--------|
      _______,RGB_RMOD, RGB_HUD, RGB_SAD, RGB_VAD, KC_RGB_T,     MG_NKRO, KC_MUTE, KC_VOLD, KC_VOLU, KC_MNXT, _______,\
  // --------+--------+--------+--------+--------+--------+|  |+--------+--------+--------+--------+--------+--------|
                                 _______, _______, _______,      _______, _______, _______ \
                              //`--------------------------'  `---------------------------'
  ),
};

int RGB_current_mode;

void matrix_init_user(void) {
  //SSD1306 OLED init, make sure to add #define SSD1306OLED in config.h
  #ifdef SSD1306OLED
      iota_gfx_init(!has_usb());   // turns on the display
  #endif

  #ifdef RGBLIGHT_ENABLE
    RGB_current_mode = rgblight_config.mode;
  #endif

  DDRD &= ~(1<<5);
  PORTD &= ~(1<<5);

  DDRB &= ~(1<<0);
  PORTB &= ~(1<<0);
}

//SSD1306 OLED update loop, make sure to add #define SSD1306OLED in config.h
#ifdef SSD1306OLED

// When add source files to SRC in rules.mk, you can use functions.
const char *read_logo(void);
char layer_state_str[24];
char modifier_state_str[24];
char host_led_state_str[24];

#ifndef NO_KEYLOG
char keylog_str[24] = {};
char keylogs_str[21] = {};
int keylogs_str_idx = 0;

// const char *read_mode_icon(bool swap);
// void set_timelog(void);
// const char *read_timelog(void);

const char code_to_name[60] = {
    ' ', ' ', ' ', ' ', 'a', 'b', 'c', 'd', 'e', 'f',
    'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p',
    'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
    '1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
    'R', 'E', 'B', 'T', '_', '-', '=', '[', ']', '\\',
    '#', ';', '\'', '`', ',', '.', '/', ' ', ' ', ' '};

void set_keylog(uint16_t keycode, keyrecord_t *record) {
  char name = ' ';
  if (keycode < 60) {
    name = code_to_name[keycode];
  }

  // update keylog
  snprintf(keylog_str, sizeof(keylog_str), "%dx%d, k%2d : %c",
           record->event.key.row, record->event.key.col,
           keycode, name);

  // update keylogs
  if (keylogs_str_idx == sizeof(keylogs_str) - 1) {
    keylogs_str_idx = 0;
    for (int i = 0; i < sizeof(keylogs_str) - 1; i++) {
      keylogs_str[i] = ' ';
    }
  }

  keylogs_str[keylogs_str_idx] = name;
  keylogs_str_idx++;
}

const char *read_keylog(void) {
  return keylog_str;
}

const char *read_keylogs(void) {
  return keylogs_str;
}
#endif // NO_KEYLOG

const char* read_modifier_state(void) {
  uint8_t modifiers = get_mods();
  uint8_t one_shot = get_oneshot_mods();

  snprintf(modifier_state_str, sizeof(modifier_state_str), "Mods:%s %s %s %s",
    (modifiers & MODS_CTRL_MASK || one_shot & MODS_CTRL_MASK) ? "CTL" : "   ",
    (modifiers & MODS_GUI_MASK || one_shot & MODS_GUI_MASK) ? "GUI" : "   ",
    (modifiers & MODS_ALT_MASK || one_shot & MODS_ALT_MASK) ? "ALT" : "   ",
    (modifiers & MODS_SHIFT_MASK || one_shot & MODS_SHIFT_MASK) ? "SFT" : "   "
  );

  return modifier_state_str;
}

const char *read_host_led_state(void) {
  uint8_t leds = host_keyboard_leds();

  snprintf(host_led_state_str, sizeof(host_led_state_str), "NL:%s CL:%s SL:%s",
    (leds & (1 << USB_LED_NUM_LOCK)) ? "on" : "- ",
    (leds & (1 << USB_LED_CAPS_LOCK)) ? "on" : "- ",
    (leds & (1 << USB_LED_SCROLL_LOCK)) ? "on" : "- "
  );

  return host_led_state_str;
}

const char* read_layer_state(void) {
  switch (biton32(layer_state)) {
    case _RAISE:
      snprintf(layer_state_str, sizeof(layer_state_str), "Layer: Raise  ");
      break;
    case _LOWER:
      snprintf(layer_state_str, sizeof(layer_state_str), "Layer: Lower  ");
      break;
    case _ADJUST:
      snprintf(layer_state_str, sizeof(layer_state_str), "Layer: Adjust ");
      break;
    default:
      switch (biton32(default_layer_state)) {
        case _QWERTY:
          snprintf(layer_state_str, sizeof(layer_state_str), "Layer: Qwerty ");
          break;
        case _COLEMAK:
          snprintf(layer_state_str, sizeof(layer_state_str), "Layer: Colemak");
          break;
        case _DVORAK:
          snprintf(layer_state_str, sizeof(layer_state_str), "Layer: Dvorak ");
          break;
      }
      break;
  }

  return layer_state_str;
}

void matrix_scan_user(void) {
   iota_gfx_task();
}

void matrix_render_user(struct CharacterMatrix *matrix) {
  if (is_master) {
    //If you want to change the display of OLED, you need to change here
    matrix_write_ln(matrix, read_layer_state());
    matrix_write_ln(matrix, read_modifier_state());
    // matrix_write_ln(matrix, read_keylog());
#ifndef NO_KEYLOG
    matrix_write_ln(matrix, read_keylogs());
#endif // NO_KEYLOG
    // matrix_write_ln(matrix, read_mode_icon(keymap_config.swap_lalt_lgui));
    matrix_write(matrix, read_host_led_state());
    //matrix_write_ln(matrix, read_timelog());
  } else {
    matrix_write(matrix, read_logo());
  }
}

void matrix_update(struct CharacterMatrix *dest, const struct CharacterMatrix *source) {
  if (memcmp(dest->display, source->display, sizeof(dest->display))) {
    memcpy(dest->display, source->display, sizeof(dest->display));
    dest->dirty = true;
  }
}

void iota_gfx_task_user(void) {
  struct CharacterMatrix matrix;
  matrix_clear(&matrix);
  matrix_render_user(&matrix);
  matrix_update(&display, &matrix);
}
#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
#ifdef SSD1306OLED
#ifndef NO_KEYLOG
  switch (keycode) {
    case KC_A ... KC_SLASH:
    case KC_F1 ... KC_F12:
    case KC_INSERT ... KC_UP:
    case KC_KP_SLASH ... KC_KP_DOT:
    case KC_F13 ... KC_F24:
    if (record->event.pressed) { set_keylog(keycode, record); }
      break;
    // set_timelog();
  }
#endif
#endif

  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_QWERTY);
      }
      break;
    case COLEMAK:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_COLEMAK);
      }
      break;
    case DVORAK:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_DVORAK);
      }
      break;
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
    case KC_BSPC:
      if (record->event.pressed) {
        // If shift was pressed, send delete.
        if ((get_mods() & (MOD_BIT(KC_RSFT) | MOD_BIT(KC_LSFT))) != 0)
        {
          uint8_t temp_mods = get_mods(); // Save the originally pressed modifier keys.

          // If only one shift was pressed, ignore it.
          if ((temp_mods & MOD_BIT(KC_LSFT)) == 0 || (temp_mods & MOD_BIT(KC_RSFT)) == 0)
          {
            if ((temp_mods & MOD_BIT(KC_LSFT)) != 0)
            {
              set_mods(temp_mods &~MOD_BIT(KC_LSFT)); // Unshift the left shift.
            }
            else if ((temp_mods & MOD_BIT(KC_RSFT)) != 0)
            {
              set_mods(temp_mods &~MOD_BIT(KC_RSFT)); // Unshift the right shift.
            }
          }

          register_code(KC_DEL);

          set_mods(temp_mods); // Restore the original held modifier keys.
        }
        else
        {
          // On a regular press, send backspace.
          register_code(KC_BSPC);
        }
      }
      else
      {
        // Because the above subroutine altered what code was registered, we need
        // to manually unregister the codes. Unregistering both can't hurt and
        // makes it so we don't have to do bookkeeping.
        unregister_code(KC_DEL);
        unregister_code(KC_BSPC);
      }
      // The keypress is handled, don't let QMK handle it.
      return false;
      break;
    case RGB_MOD:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          rgblight_mode(RGB_current_mode);
          rgblight_step();
          RGB_current_mode = rgblight_config.mode;
        }
      #endif
      return false;
      break;
    case RGBRST:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          eeconfig_update_rgblight_default();
          rgblight_enable();
          RGB_current_mode = rgblight_config.mode;
        }
      #endif
      break;
  }
  return true;
}

