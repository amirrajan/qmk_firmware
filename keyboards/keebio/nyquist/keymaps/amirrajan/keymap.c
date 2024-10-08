// Copyright 2023 Danny Nguyen (danny@keeb.io)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "keymap_steno.h"

// https://didoesdigital.com/typey-type/lessons/fundamentals/introduction/

#define MOUSEKEY_DELAY             500
#define MOUSEKEY_INTERVAL          20
#define MOUSEKEY_MAX_SPEED         5
#define MOUSEKEY_TIME_TO_MAX       50

#define ST_BOLT QK_STENO_BOLT
#define ST_GEM  QK_STENO_GEMINI

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum layer_names {
    _QWERTY,
    _SYMBOLS,
    _MODS,
    _PLOVER
};

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  PHOTOSHOP_PREV_LAYER,
  PHOTOSHOP_NEXT_LAYER,
  PLOVER_OR_0,
  QWERTY_OR_0,
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case PHOTOSHOP_PREV_LAYER:
        if (record->event.pressed) {
            // when keycode QMKBEST is pressed
            SEND_STRING(SS_DOWN(X_LALT)SS_TAP(X_RBRC)SS_UP(X_LALT));
        } else {
            // when keycode QMKBEST is released
        }
        break;
    case PHOTOSHOP_NEXT_LAYER:
        if (record->event.pressed) {
            // when keycode QMKBEST is pressed
            SEND_STRING(SS_DOWN(X_LALT)SS_TAP(X_LBRC)SS_UP(X_LALT));
        } else {
            // when keycode QMKBEST is released
        }
        break;
    case PLOVER_OR_0:
        if (record->event.pressed) {
            if (layer_state_is(_PLOVER)) {
                layer_off(_PLOVER);
                layer_on(_QWERTY);
            } else {
                // if control is move to layer 3 and do not send 0
                if (get_mods() & MOD_BIT(KC_LCTL)) {
                    layer_on(_PLOVER);
                    return false;
                } else {
                    SEND_STRING(SS_TAP(X_0));
                }
            }
        }
        break;
    }

    return true;
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_QWERTY] = LAYOUT_ortho_5x12(
 KC_GRAVE,      KC_1,           KC_2,             KC_3,           KC_4,           KC_5,                   KC_6,            KC_7,           KC_8,            KC_9,           PLOVER_OR_0,     KC_MINUS,            \
 KC_TAB,        KC_Q,           KC_W,             KC_E,           KC_R,           KC_T,                   KC_Y,            KC_U,           KC_I,            KC_O,           KC_P,            GUI_T(KC_BACKSLASH), \
 KC_LCTL,       KC_A,           KC_S,             KC_D,           KC_F,           KC_G,                   KC_H,            KC_J,           KC_K,            KC_L,           KC_SEMICOLON,    LALT_T(KC_QUOTE),    \
 KC_LSFT,       KC_Z,           KC_X,             KC_C,           KC_V,           KC_B,                   KC_N,            KC_M,           KC_COMMA,        KC_DOT,         KC_SLASH,        KC_RSFT,             \
 KC_LCTL,       KC_LALT,        KC_LCMD,          KC_EQUAL,       KC_UNDS,        LT(1, KC_ENTER),        KC_SPACE,        KC_BSPC,        KC_LEFT,         KC_DOWN,        KC_UP,           KC_RGHT \
),

[_SYMBOLS] = LAYOUT_ortho_5x12(
 KC_TILDE,      KC_EXCLAIM,     KC_AT,            KC_HASH,        KC_DOLLAR,      KC_PERCENT,            KC_CIRCUMFLEX,    KC_AMPERSAND,   KC_ASTERISK,     KC_LEFT_PAREN,  KC_RIGHT_PAREN,       KC_BACKSPACE,         \
 KC_TAB,        KC_QUOTE,       KC_EQUAL,         KC_EQUAL,       KC_ENTER,       KC_TILDE,              KC_QUESTION,      KC_LEFT_PAREN,  KC_RIGHT_PAREN,  KC_PIPE,        KC_PLUS,              GUI_T(KC_BACKSLASH),  \
 KC_LEFT,       KC_AMPERSAND,   S(KC_S),          KC_MINUS,       KC_UNDS,        KC_RABK,               KC_HASH,          KC_LBRC,        KC_RBRC,         KC_LABK,        KC_COLON,             KC_DQUO,              \
 KC_RGHT,       KC_COMMA,       KC_ASTERISK,      KC_MS_BTN1,     LGUI(KC_V),     KC_BACKSPACE,          KC_EXCLAIM,       KC_LCBR,        KC_RCBR,         KC_RABK,        PHOTOSHOP_PREV_LAYER, PHOTOSHOP_NEXT_LAYER, \
 KC_DOWN,       KC_LALT,        KC_LCMD,          KC_MS_BTN2,     KC_MS_BTN1,     KC_SPACE,              KC_SPACE,         KC_BSPC,        KC_MS_L,         KC_MS_D,        KC_MS_U,              KC_MS_R               \
),

[_MODS] = LAYOUT_ortho_5x12(
 XXXXXXX,       XXXXXXX,        XXXXXXX,          XXXXXXX,        XXXXXXX,        XXXXXXX,               XXXXXXX,          XXXXXXX,        XXXXXXX,         XXXXXXX,        XXXXXXX,         XXXXXXX,        \
 XXXXXXX,       XXXXXXX,        XXXXXXX,          XXXXXXX,        XXXXXXX,        XXXXXXX,               XXXXXXX,          XXXXXXX,        XXXXXXX,         XXXXXXX,        XXXXXXX,         XXXXXXX,        \
 XXXXXXX,       XXXXXXX,        XXXXXXX,          XXXXXXX,        XXXXXXX,        XXXXXXX,               XXXXXXX,          XXXXXXX,        XXXXXXX,         XXXXXXX,        XXXXXXX,         XXXXXXX,        \
 XXXXXXX,       XXXXXXX,        XXXXXXX,          XXXXXXX,        LGUI(KC_V),     XXXXXXX,               XXXXXXX,          XXXXXXX,        XXXXXXX,         XXXXXXX,        XXXXXXX,         XXXXXXX,        \
 XXXXXXX,       XXXXXXX,        XXXXXXX,          XXXXXXX,        XXXXXXX,        XXXXXXX,               XXXXXXX,          XXXXXXX,        XXXXXXX,         XXXXXXX,        XXXXXXX,         XXXXXXX         \
),

[_PLOVER] = LAYOUT_ortho_5x12(
 STN_N1,        STN_N2,         STN_N3,           STN_N4,         STN_N5,         STN_N6,        STN_N7,          STN_N8,         STN_N9,          STN_NA,          STN_NB,      STN_NC,              \
 STN_FN,        STN_S1,         STN_TL,           STN_PL,         STN_HL,         STN_ST1,       STN_ST3,         STN_FR,         STN_PR,          STN_LR,          STN_TR,      STN_DR,              \
 XXXXXXX,       STN_S2,         STN_KL,           STN_WL,         STN_RL,         STN_ST2,       STN_ST4,         STN_RR,         STN_BR,          STN_GR,          STN_SR,      STN_ZR,              \
 XXXXXXX,       XXXXXXX,        XXXXXXX,          XXXXXXX,        XXXXXXX,        XXXXXXX,       XXXXXXX,         XXXXXXX,        XXXXXXX,         XXXXXXX,        XXXXXXX,      XXXXXXX,             \
 PLOVER_OR_0,   XXXXXXX,        XXXXXXX,          XXXXXXX,        STN_A,          STN_O,         STN_E,           STN_U,          XXXXXXX,         XXXXXXX,        XXXXXXX,      XXXXXXX              \
)

};

#ifdef AUDIO_ENABLE
float aone_qwerty[][2]     = SONG(QWERTY_SOUND);
#endif

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [_QWERTY] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_PGUP, KC_PGDN) },
    [_SYMBOLS] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_PGUP, KC_PGDN) },
    [_MODS] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_PGUP, KC_PGDN) },
    [_PLOVER] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_PGUP, KC_PGDN) }
};
#endif

void keyboard_post_init_user(void) {
    // Call the post init code.
    rgblight_disable_noeeprom();  // Turn off RGB lighting.
}
