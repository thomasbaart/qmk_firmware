
#include QMK_KEYBOARD_H
#include <stdio.h>
#include "macro11.h"

#define _BASE 0
#define _LOWER 1
#define _RAISE 2
#define _ADJUST 3

char layer_state_str[24];

const char *read_layer_state(void) {
  switch (layer_state)
  {
  case _BASE:
    snprintf(layer_state_str, sizeof(layer_state_str), "Layer: Default");
    break;
  case _RAISE:
    snprintf(layer_state_str, sizeof(layer_state_str), "Layer: Raise");
    break;
  case _LOWER:
    snprintf(layer_state_str, sizeof(layer_state_str), "Layer: Lower");
    break;
  case _ADJUST:
    snprintf(layer_state_str, sizeof(layer_state_str), "Layer: Adjust");
    break;
  default:
    snprintf(layer_state_str, sizeof(layer_state_str), "Layer: Undef-%ld", layer_state);
  }

  return layer_state_str;
}
