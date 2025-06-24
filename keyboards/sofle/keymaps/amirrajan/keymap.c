// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later
#include QMK_KEYBOARD_H
#undef TAPPING_TERM
#define TAPPING_TERM 100
// #define MASTER_RIGHT 1

enum sofle_layers {
    /* _M_XYZ = Mac Os, _W_XYZ = Win/Linux */
    _QWERTY,
    _SYMBOLS
};

enum custom_keycodes {
    QWERTY = SAFE_RANGE
};

#define KC_QWERTY PDF(_QWERTY)
#define KC_COLEMAK PDF(_COLEMAK)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*
 * QWERTY
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |  `   |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |  `   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | ESC  |   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  | Bspc |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Tab  |   A  |   S  |   D  |   F  |   G  |-------.    ,-------|   H  |   J  |   K  |   L  |   ;  |  '   |
 * |------+------+------+------+------+------|  MUTE |    |       |------+------+------+------+------+------|
 * |LShift|   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |   ,  |   .  |   /  |RShift|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            | LGUI | LAlt | LCTR |LOWER | /Enter  /       \Space \  |RAISE | RCTR | RAlt | RGUI |
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *            `----------------------------------'           '------''---------------------------'
 */

[_QWERTY] = LAYOUT(
  KC_GRV,   KC_1,   KC_2,    KC_3,    KC_4,    KC_5,                                KC_6,    KC_7,    KC_8,    KC_9,   KC_0,     KC_MINUS,
  KC_TAB,   KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,                                KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,     MT(MOD_LALT, KC_BACKSLASH),
  KC_LCTL,  KC_A,   KC_S,    KC_D,    KC_F,    KC_G,                                KC_H,    KC_J,    KC_K,    KC_L,   KC_SCLN,  LGUI_T(KC_QUOTE),
  KC_LSFT,  KC_Z,   KC_X,    KC_C,    KC_V,    KC_B,            QK_BOOT,   KC_PEQL, KC_N,    KC_M,    KC_COMM, KC_DOT, KC_SLSH,  KC_RSFT,
                    KC_LCTL, KC_LALT, KC_UNDS, LT(1, KC_ENTER), KC_DOWN,   KC_UP, LT(1, KC_SPC),  KC_BSPC, KC_LEFT, KC_RIGHT
),

[_SYMBOLS] = LAYOUT(
  KC_TILDE, KC_EXCLAIM,     KC_AT,          KC_HASH,       KC_DOLLAR,     KC_PERCENT,                       KC_CIRCUMFLEX,     KC_AMPERSAND,  KC_ASTERISK,       KC_LEFT_PAREN,  KC_RIGHT_PAREN,        KC_BACKSPACE,
  KC_TAB,   KC_QUOTE,       KC_EQUAL,       KC_EQUAL,      KC_ENTER,      KC_TILDE,                         KC_QUESTION,       KC_LEFT_PAREN, KC_RIGHT_PAREN,    KC_PIPE,        KC_PLUS,               GUI_T(KC_BACKSLASH),
  KC_LEFT,  KC_AMPERSAND,   S(KC_S),        KC_MINUS,      KC_UNDS,       KC_RABK,                          KC_HASH,           KC_LBRC,       KC_RBRC,           KC_LABK,        KC_COLON,              KC_DQUO,
  KC_RGHT,  KC_COMMA,       KC_ASTERISK,    KC_MS_BTN1,    LGUI(KC_V),    KC_BACKSPACE, KC_MUTE,    XXXXXXX,KC_EXCLAIM,        KC_LCBR,       KC_RCBR,           KC_RABK,        KC_UP,              KC_COLON,
                                                KC_SPACE,KC_SPACE, KC_SPACE, KC_SPACE, KC_SPACE,    KC_BSPC,  KC_SPACE, KC_SPACE, KC_SPACE, KC_SPACE
)
/* /\* */
/*  * COLEMAK */
/*  * ,-----------------------------------------.                    ,-----------------------------------------. */
/*  * |  `   |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |  `   | */
/*  * |------+------+------+------+------+------|                    |------+------+------+------+------+------| */
/*  * | ESC  |   Q  |   W  |   F  |   P  |   G  |                    |   J  |   L  |   U  |   Y  |   ;  | Bspc | */
/*  * |------+------+------+------+------+------|                    |------+------+------+------+------+------| */
/*  * | TAB  |   A  |   R  |   S  |   T  |   D  |-------.    ,-------|   H  |   N  |   E  |   I  |   O  |  '   | */
/*  * |------+------+------+------+------+------|  MUTE |    |       |------+------+------+------+------+------| */
/*  * |LShift|   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   K  |   M  |   ,  |   .  |   /  |RShift| */
/*  * `-----------------------------------------/       /     \      \-----------------------------------------' */
/*  *            | LGUI | LAlt | LCTR |LOWER | /Enter  /       \Space \  |RAISE | RCTR | RAlt | RGUI | */
/*  *            |      |      |      |      |/       /         \      \ |      |      |      |      | */
/*  *            `----------------------------------'           '------''---------------------------' */
/*  *\/ */

/* [_COLEMAK] = LAYOUT( */
/*   KC_GRV,   KC_1,   KC_2,    KC_3,    KC_4,    KC_5,                      KC_6,    KC_7,    KC_8,    KC_9,    KC_0,  KC_GRV, */
/*   KC_ESC,   KC_Q,   KC_W,    KC_F,    KC_P,    KC_G,                      KC_J,    KC_L,    KC_U,    KC_Y, KC_SCLN,  KC_BSPC, */
/*   KC_TAB,   KC_A,   KC_R,    KC_S,    KC_T,    KC_D,                      KC_H,    KC_N,    KC_E,    KC_I,    KC_O,  KC_QUOT, */
/*   KC_LSFT,  KC_Z,   KC_X,    KC_C,    KC_V,    KC_B, KC_MUTE,      XXXXXXX,KC_K,    KC_M, KC_COMM,  KC_DOT, KC_SLSH,  KC_RSFT, */
/*                  KC_LGUI,KC_LALT,KC_LCTL,TL_LOWR, KC_ENT,        KC_SPC,  TL_UPPR, KC_RCTL, KC_RALT, KC_RGUI */
/* ), */
/* /\* LOWER */
/*  * ,-----------------------------------------.                    ,-----------------------------------------. */
/*  * |      |  F1  |  F2  |  F3  |  F4  |  F5  |                    |  F6  |  F7  |  F8  |  F9  | F10  | F11  | */
/*  * |------+------+------+------+------+------|                    |------+------+------+------+------+------| */
/*  * |  `   |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  | F12  | */
/*  * |------+------+------+------+------+------|                    |------+------+------+------+------+------| */
/*  * | Tab  |   !  |   @  |   #  |   $  |   %  |-------.    ,-------|   ^  |   &  |   *  |   (  |   )  |   |  | */
/*  * |------+------+------+------+------+------|  MUTE |    |       |------+------+------+------+------+------| */
/*  * | Shift|  =   |  -   |  +   |   {  |   }  |-------|    |-------|   [  |   ]  |   ;  |   :  |   \  | Shift| */
/*  * `-----------------------------------------/       /     \      \-----------------------------------------' */
/*  *            | LGUI | LAlt | LCTR |LOWER | /Enter  /       \Space \  |RAISE | RCTR | RAlt | RGUI | */
/*  *            |      |      |      |      |/       /         \      \ |      |      |      |      | */
/*  *            `----------------------------------'           '------''---------------------------' */
/*  *\/ */
/* [_LOWER] = LAYOUT( */
/*   _______,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                       KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11, */
/*   KC_GRV,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                       KC_6,    KC_7,    KC_8,    KC_9,    KC_0,  KC_F12, */
/*   _______, KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_PERC,                       KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_PIPE, */
/*   _______,  KC_EQL, KC_MINS, KC_PLUS, KC_LCBR, KC_RCBR, _______,       _______, KC_LBRC, KC_RBRC, KC_SCLN, KC_COLN, KC_BSLS, _______, */
/*                        _______, _______, _______, _______, _______,       _______, _______, _______, _______, _______ */
/* ), */
/* /\* RAISE */
/*  * ,----------------------------------------.                    ,-----------------------------------------. */
/*  * |      |      |      |      |      |      |                    |      |      |      |      |      |      | */
/*  * |------+------+------+------+------+------|                    |------+------+------+------+------+------| */
/*  * | Esc  | Ins  | Pscr | Menu |      |      |                    |      | PWrd |  Up  | NWrd | DLine| Bspc | */
/*  * |------+------+------+------+------+------|                    |------+------+------+------+------+------| */
/*  * | Tab  | LAt  | LCtl |LShift|      | Caps |-------.    ,-------|      | Left | Down | Rigth|  Del | Bspc | */
/*  * |------+------+------+------+------+------|  MUTE  |    |       |------+------+------+------+------+------| */
/*  * |Shift | Undo |  Cut | Copy | Paste|      |-------|    |-------|      | LStr |      | LEnd |      | Shift| */
/*  * `-----------------------------------------/       /     \      \-----------------------------------------' */
/*  *            | LGUI | LAlt | LCTR |LOWER | /Enter  /       \Space \  |RAISE | RCTR | RAlt | RGUI | */
/*  *            |      |      |      |      |/       /         \      \ |      |      |      |      | */
/*  *            `----------------------------------'           '------''---------------------------' */
/*  *\/ */
/* [_RAISE] = LAYOUT( */
/*   _______, _______ , _______ , _______ , _______ , _______,                           _______,  _______  , _______,  _______ ,  _______ ,_______, */
/*   _______,  KC_INS,  KC_PSCR,   KC_APP,  XXXXXXX, XXXXXXX,                        KC_PGUP, KC_PRVWD,   KC_UP, KC_NXTWD,C(KC_BSPC), KC_BSPC, */
/*   _______, KC_LALT,  KC_LCTL,  KC_LSFT,  XXXXXXX, KC_CAPS,                       KC_PGDN,  KC_LEFT, KC_DOWN, KC_RGHT,  KC_DEL, KC_BSPC, */
/*   _______, C(KC_Z), C(KC_X), C(KC_C), C(KC_V), XXXXXXX,  _______,       _______,  XXXXXXX, KC_LSTRT, XXXXXXX, KC_LEND,   XXXXXXX, _______, */
/*                          _______, _______, _______, _______, _______,       _______, _______, _______, _______, _______ */
/* ), */
/* ADJUST
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | QK_BOOT|      |QWERTY|COLEMAK|      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |MACWIN|      |      |      |-------.    ,-------|      | VOLDO| MUTE | VOLUP|      |      |
 * |------+------+------+------+------+------|  MUTE |    |       |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------|    |-------|      | PREV | PLAY | NEXT |      |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            | LGUI | LAlt | LCTR |LOWER | /Enter  /       \Space \  |RAISE | RCTR | RAlt | RGUI |
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *            `----------------------------------'           '------''---------------------------'
 */
  /* [_ADJUST] = LAYOUT( */
  /* XXXXXXX , XXXXXXX,  XXXXXXX ,  XXXXXXX , XXXXXXX, XXXXXXX,                     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, */
  /* QK_BOOT  , XXXXXXX,KC_QWERTY,KC_COLEMAK,CG_TOGG,XXXXXXX,                     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, */
  /* XXXXXXX , XXXXXXX,CG_TOGG, XXXXXXX,    XXXXXXX,  XXXXXXX,                     XXXXXXX, KC_VOLD, KC_MUTE, KC_VOLU, XXXXXXX, XXXXXXX, */
  /* XXXXXXX , XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX,  XXXXXXX, XXXXXXX,     XXXXXXX, XXXXXXX, KC_MPRV, KC_MPLY, KC_MNXT, XXXXXXX, XXXXXXX, */
  /*                  _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______ */
  /* ) */
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    return true;
}

bool encoder_update_user(uint8_t index, bool clockwise) {
    static int encoder_ticks = 0;

    if (clockwise) ++encoder_ticks;
    else --encoder_ticks;

    if (encoder_ticks >= 10) {
        encoder_ticks = 0;
        if (index == 0) { /* First encoder */
          if (clockwise) {
            tap_code(KC_VOLU); /* Volume up */
          } else {
            tap_code(KC_VOLD); /* Volume Down */
          }
        }
    }

    return true;
}
