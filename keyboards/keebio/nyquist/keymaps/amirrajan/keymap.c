#include QMK_KEYBOARD_H

extern keymap_config_t keymap_config;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#include QMK_KEYBOARD_H

extern keymap_config_t keymap_config;

#define _BASE 0
#define _SYMBOLS 1

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  MACRO_ARROW,
  MACRO_FAT_ARROW,
  MACRO_VIM_SAVE,
  MACRO_UNDERSCORE,
  MACRO_PLUS_EQUAL,
  MACRO_DOLLAR_A,
  MACRO_CAPITAL_J,
  MACRO_PARENS,
  MACRO_DOUBLE_QUOTE
};

// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_BASE] = LAYOUT( \
  KC_GRAVE,      KC_1,           KC_2,             KC_3,           KC_4,           KC_5,             KC_6,          KC_7,             KC_8,           KC_9,           KC_0,            KC_MINUS,         \
  KC_TAB,        KC_Q,           KC_W,             KC_E,           KC_R,           KC_T,             KC_Y,          KC_U,             KC_I,           KC_O,           KC_P,            GUI_T(KC_BSLASH), \
  KC_LCTL,       KC_A,           KC_S,             KC_D,           KC_F,           KC_G,             KC_H,          KC_J,             KC_K,           KC_L,           KC_SCOLON,       KC_QUOTE,         \
  LSFT_T(KC_9),  KC_Z,           KC_X,             KC_C,           KC_V,           KC_B,             KC_N,          KC_M,             KC_COMMA,       KC_DOT,         KC_SLASH,        RSFT_T(KC_0),     \
  KC_LCTL,       KC_LALT,        KC_LCMD,          KC_EQUAL,       KC_UNDS,        LT(1, KC_ENTER),  KC_SPACE,      KC_BSPACE,        KC_LEFT,        KC_DOWN,        KC_UP,           KC_RGHT           \
),

[_SYMBOLS] = LAYOUT( \
  KC_TILDE,      KC_EXCLAIM,     KC_AT,            KC_HASH,        KC_DOLLAR,      KC_PERCENT,       KC_CIRCUMFLEX, KC_AMPERSAND,     KC_ASTERISK,    KC_LEFT_PAREN,  KC_RIGHT_PAREN,  KC_BSPACE,          \
  KC_TAB,        KC_QUOTE,       MACRO_PLUS_EQUAL, KC_EQUAL,       KC_ENTER,       KC_TILDE,         KC_QUESTION,   KC_LEFT_PAREN,    KC_RIGHT_PAREN, KC_PIPE,        KC_PLUS,         KC_BSLASH,          \
  KC_LEFT,       KC_AMPERSAND,   KC_AT,            KC_MINUS,       KC_UNDS,        KC_RABK,          KC_HASH,       KC_LBRACKET,      KC_RBRACKET,    KC_LABK,        KC_COLON,        MACRO_DOUBLE_QUOTE, \
  KC_RGHT,       KC_COMMA,       KC_ASTERISK,      KC_COMMA,       KC_TRANSPARENT, MACRO_PARENS,     KC_EXCLAIM,    KC_LCBR,          KC_RCBR,        KC_RABK,        KC_QUESTION,     KC_RIGHT_PAREN,     \
  KC_DOWN,       KC_LALT,        KC_LCMD,          KC_DOLLAR,      KC_BSPACE,      KC_SPACE,         KC_SPACE,      KC_BSPACE,        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,  GUI_T(KC_NO)        \
)

};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    // dynamically generate these.
    case MACRO_ARROW:
      if (record->event.pressed) {
        SEND_STRING("->");
      }
      break;
    case MACRO_FAT_ARROW:
      if (record->event.pressed) {
        SEND_STRING("=>");
      }
      break;
  case MACRO_VIM_SAVE:
      if (record->event.pressed) {
        SEND_STRING(SS_TAP(X_ESCAPE)":wa\n");
      }
  case MACRO_PLUS_EQUAL:
      if (record->event.pressed) {
        SEND_STRING(" += ");
      }
      break;
  case MACRO_DOLLAR_A:
      if (record->event.pressed) {
        SEND_STRING("$A");
      }
      break;
  case MACRO_CAPITAL_J:
      if (record->event.pressed) {
        SEND_STRING("J");
      }
  case MACRO_PARENS:
      if (record->event.pressed) {
        SEND_STRING("()");
      }
      break;
  case MACRO_DOUBLE_QUOTE:
      if (record->event.pressed) {
        SEND_STRING("\"");
      }
      break;
  }
  return true;
}
