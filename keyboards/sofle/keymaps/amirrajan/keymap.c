// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later
#include QMK_KEYBOARD_H
#undef TAPPING_TERM
#define TAPPING_TERM 100
// #define MASTER_RIGHT 1

enum sofle_layers {
    ____QWERTY,
    ____PHONETIC_SYMBOLS,
    ____VIM_EMULATION
};

#define LT_SYM LT(____PHONETIC_SYMBOLS, KC_ENT)
#define LT_VIM LT(____VIM_EMULATION, KC_SPC)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*
                 ,-----------------------------------------.                                                       ,-----------------------------------------.
                |      |      |      |      |      |      |                                                       |      |      |      |      |      |      |
                |------+------+------+------+------+------|                                                       |------+------+------+------+------+------|
                |      |      |      |      |      |      |                                                       |      |      |      |      |      |      |
                |------+------+------+------+------+------|                                                       |------+------+------+------+------+------|
                |      |      |      |      |      |      |-------.                                       ,-------|      |      |      |      |      |      |
                |------+------+------+------+------+------|       |            MY SOFLE KEYMAP            |       |------+------+------+------+------+------|
                |      |      |      |      |      |      |-------|                                       |-------|      |      |      |      |      |      |
                `-----------------------------------------/       /                                        \      \-----------------------------------------'
                           |      |      |      |      | /       /                                          \      \  |      |      |      |      |
                           |      |      |      |      |/       /                                            \      \ |      |      |      |      |
                           `----------------------------------'                                              '------''---------------------------'
*/
[____QWERTY] = LAYOUT(
  /*`*/       /*1*/       /*2*/       /*3*/       /*4*/       /*5*/                                       /*6*/       /*7*/       /*8*/       /*9*/       /*0*/       /*BSPC*/
  KC_GRV,     KC_1,       KC_2,       KC_3,       KC_4,       KC_5,                                       KC_6,       KC_7,       KC_8,       KC_9,       KC_0,       KC_MINUS,
  /*TAB*/     /*q*/       /*w*/       /*e*/       /*r*/       /*t*/                                       /*y*/       /*u*/       /*i*/       /*o*/       /*p*/       /*\*/
  KC_TAB,     KC_Q,       KC_W,       KC_E,       KC_R,       KC_T,                                       KC_Y,       KC_U,       KC_I,       KC_O,       KC_P,       MT(MOD_LALT, KC_BACKSLASH),
  /*CTRL*/    /*a*/       /*s*/       /*d*/       /*f*/       /*g*/                                       /*h*/       /*j*/       /*k*/       /*l*/       /*;*/       /*'*/
  KC_LCTL,    KC_A,       KC_S,       KC_D,       KC_F,       KC_G,                                       KC_H,       KC_J,       KC_K,       KC_L,       KC_SCLN,    LGUI_T(KC_QUOTE),
  /*SHFT*/    /*z*/       /*x*/       /*c*/       /*v*/       /*b*/       /*◯*/               /*◯*/       /*n*/       /*m*/       /*,*/       /*.*/       /*/*/       /*SHFT*/
  KC_LSFT,    KC_Z,       KC_X,       KC_C,       KC_V,       KC_B,       QK_BOOT,            QK_REBOOT,  KC_N,       KC_M,       KC_COMM,    KC_DOT,     KC_SLSH,    KC_RSFT,
                          /*CTRL*/    /*META*/    /*THUMB*/   /*THUMB*/   /*THUMB*/           /*THUMB*/   /*THUMB*/   /*THUMB*/   /*LFT*/     /*RHT*/
                          KC_LCTL,    KC_LCMD,    KC_UNDS,    LT_SYM,     KC_UP,              KC_DOWN,    LT_VIM,     KC_BSPC,    KC_LEFT,    KC_RIGHT),                                          /*
                                                                ┬                                           ┬
                                                                │                                           │
                          PRESS AND HOLD KEY UNDER LEFT THUMB   │                                           │   PRESS AND HOLD KEY UNDER RIGHT THUMB
                          TO GO TO THE PHONETIC SYMBOL LAYER    │                                           │   TO GO TO THE VIM EMULATION LAYER
                                                                │                                           │
                                                                │                                           │
                                                                │                       ┌───────────────────┘
     WELCOME! 🭮─────────────────────────────────────────────────┘                       │                                                                                                         */
[____PHONETIC_SYMBOLS] = LAYOUT(                                                    /*  │  */
  /*`*/       /*1*/       /*2*/       /*3*/       /*4*/       /*5*/                 /*  │  */             /*6*/       /*7*/       /*8*/       /*9*/      /*0*/       /*BSPC*/
  KC_TILDE,   KC_EXCLAIM, KC_AT,      KC_HASH,    KC_DOLLAR,  KC_PERCENT,           /*  │  */             KC_CIRC,    KC_AMPR,    KC_ASTR,    KC_LPRN,   KC_RPRN,    KC_BSPC,
  /*TAB*/     /*q*/       /*w*/       /*e*/       /*r*/       /*t*/                 /*  │  */             /*y*/       /*u*/       /*i*/       /*o*/      /*p*/       /*\*/
  KC_TAB,     KC_QUOTE,   KC_EQUAL,   KC_EQUAL,   KC_ENTER,   KC_TILDE,             /*  │  */             KC_QUES,    KC_LPRN,    KC_RPRN,    KC_PIPE,   KC_PLUS,    CMD_T(KC_BSLS),
  /*CTRL*/    /*a*/       /*s*/       /*d*/       /*f*/       /*g*/                 /*  │  */             /*h*/       /*j*/       /*k*/       /*l*/      /*;*/       /*'*/
  KC_LEFT,    KC_AMPR,    S(KC_S),    KC_MINUS,   KC_UNDS,    KC_RABK,              /*  │  */             KC_HASH,    KC_LBRC,    KC_RBRC,    KC_LABK,   KC_COLON,   KC_DQUO,
  /*SHFT*/    /*z*/       /*x*/       /*c*/       /*v*/       /*b*/       /*◯*/     /*  │  */ /*◯*/       /*n*/       /*m*/       /*,*/       /*.*/      /*/*/       /*SHFT*/
  KC_RGHT,    KC_COMMA,   KC_ASTR,    KC_MS_BTN1, LGUI(KC_V), KC_BSPC,    KC_MUTE,  /*  │  */ XXXXXXX,    KC_EXCLAIM, KC_LCBR,    KC_RCBR,    KC_DOT,    KC_SLSH,    KC_LEFT,
                          /*CTRL*/    /*META*/    /*THUMB*/   /*THUMB*/   /*THUMB*/ /*  │  */ /*THUMB*/   /*THUMB*/   /*THUMB*/   /*LFT*/     /*RHT*/
                          KC_SPACE,   KC_SPACE,   KC_SPACE,   KC_SPACE,   KC_SPACE, /*  │  */ KC_BSPC,    KC_SPACE,   KC_SPACE,   KC_SPACE,   KC_SPACE),                                          /*
                                                                                        │
                                                                                        │
                                                                                        │
                                                                                        │
                                                                                        │
     WELCOME! 🭮─────────────────────────────────────────────────────────────────────────┘                                                                                                         */
[____VIM_EMULATION] = LAYOUT(
  /*`*/       /*1*/       /*2*/       /*3*/       /*4*/       /*5*/                                       /*6*/       /*7*/       /*8*/       /*9*/       /*0*/       /*BSPC*/
  XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,                                    XXXXXXX,    XXXXXXX,    KC_END,     XXXXXXX,    KC_HOME,    XXXXXXX,
  /*TAB*/     /*q*/       /*w*/       /*e*/       /*r*/       /*t*/                                       /*y*/       /*u*/       /*i*/       /*o*/       /*p*/       /*\*/
  XXXXXXX,    KC_Q,       KC_W,       C(KC_E),    KC_ENTER,   C(KC_T),                                    XXXXXXX,    XXXXXXX,    C(KC_I),    XXXXXXX,    XXXXXXX,    XXXXXXX,
  /*CTRL*/    /*a*/       /*s*/       /*d*/       /*f*/       /*g*/                                       /*h*/       /*j*/       /*k*/       /*l*/       /*;*/       /*'*/
  KC_LCTL,    XXXXXXX,    KC_LSFT,    C(KC_K),    C(KC_F),    C(KC_G),                                    KC_LEFT,    KC_DOWN,    KC_UP,      KC_RIGHT,   KC_COLON,   KC_QUOTE,
  /*SHFT*/    /*z*/       /*x*/       /*c*/       /*v*/       /*b*/       /*◯*/               /*◯*/       /*n*/       /*m*/       /*,*/       /*.*/       /*/*/       /*SHFT*/
  XXXXXXX,    C(KC_Z),    XXXXXXX,    C(KC_C),    C(KC_V),    C(KC_B),    XXXXXXX,            XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,
                          /*CTRL*/    /*META*/    /*THUMB*/   /*THUMB*/   /*THUMB*/           /*THUMB*/   /*THUMB*/   /*THUMB*/   /*LFT*/     /*RHT*/
                          XXXXXXX,    XXXXXXX,    XXXXXXX,    KC_ESC,     XXXXXXX,            XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX
)
};

bool encoder_update_user(uint8_t index, bool clockwise) {
    return false; /* swallow rotation, do nothing */
}

/* Session keypress count (resets on power loss). Counted on master. */
static uint32_t keypress_count = 0;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        keypress_count++;
    }
    return true;
}

#ifdef OLED_ENABLE

/* Master half: live WPM + session peak WPM + session keypresses (270). */
static void render_status(void) {
    uint8_t wpm = get_current_wpm();
    static uint8_t max_wpm = 0;
    if (wpm > max_wpm) {
        max_wpm = wpm;
    }

    char buf[11];

    oled_write_ln_P(PSTR("WPM"), false);
    snprintf(buf, sizeof(buf), "%u", wpm);
    oled_write_ln(buf, false);

    oled_write_P(PSTR("\n"), false);

    oled_write_ln_P(PSTR("MAX"), false);
    snprintf(buf, sizeof(buf), "%u", max_wpm);
    oled_write_ln(buf, false);

    oled_write_P(PSTR("\n"), false);

    oled_write_ln_P(PSTR("KEYS"), false);
    /* OLED line is 5 chars wide; compact past 99,999 so it doesn't wrap. */
    if (keypress_count > 9999999UL) {
        snprintf(buf, sizeof(buf), "%luM", (unsigned long)(keypress_count / 1000000UL));
    } else if (keypress_count > 99999UL) {
        snprintf(buf, sizeof(buf), "%luK", (unsigned long)(keypress_count / 1000UL));
    } else {
        snprintf(buf, sizeof(buf), "%lu", (unsigned long)keypress_count);
    }
    oled_write_ln(buf, false);
}

/* Slave-half eye candy. Pick one. */
#define ANIM_GAME_OF_LIFE
// #define ANIM_MATRIX_RAIN

#ifdef ANIM_GAME_OF_LIFE
#    include "game-of-life.c"
#else
#    include "matrix-rain.c"
#endif

/* Both halves portrait so the animation runs along the long axis. */
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_270;
}

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        render_status();
    } else {
        oled_render_anim(); /* purely decorative */
    }
    return false;
}

#endif
