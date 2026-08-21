/**
 * Matrix rain for the slave OLED, rotated 270 like the master half, so the
 * panel is portrait 32x128: 5 cols x 16 rows of the default 6x8 font.
 * Purely decorative: driven by a timer, not by typing.
 *
 * Text-mode only, so PROGMEM cost is a few hundred bytes instead of the
 * 512 bytes per frame a raw bitmap animation needs.
 */

#pragma once

#define MR_COLS 5   /* 32px  / 6px glyph */
#define MR_ROWS 16  /* 128px / 8px glyph */

#ifndef MR_FRAME_MS
#    define MR_FRAME_MS 45 /* tick rate; column speeds are multiples of this */
#endif
#ifndef MR_SHIMMER
#    define MR_SHIMMER 2 /* glyph mutations per tick, for the flicker effect */
#endif

/* Small xorshift PRNG: cheaper than pulling in rand() on AVR. */
static uint16_t mr_rand_state = 0;

static uint16_t mr_rand(void) {
    if (mr_rand_state == 0) {
        mr_rand_state = (uint16_t)timer_read() | 1u;
    }
    mr_rand_state ^= (uint16_t)(mr_rand_state << 7);
    mr_rand_state ^= (uint16_t)(mr_rand_state >> 9);
    mr_rand_state ^= (uint16_t)(mr_rand_state << 8);
    return mr_rand_state;
}

static char mr_glyph(void) {
    static const char mr_charset[] PROGMEM = "0123456789ABCDEFGHJKLMNPRSTUVWXYZ<>*+-=/\\|:;.";
    return (char)pgm_read_byte(&mr_charset[mr_rand() % (sizeof(mr_charset) - 1)]);
}

typedef struct {
    int8_t  head;  /* row index of the leading glyph; negative = above screen */
    uint8_t len;   /* trail length in rows */
    uint8_t speed; /* ticks per row step */
    uint8_t tick;
} mr_col_t;

static mr_col_t mr_cols[MR_COLS];
static bool     mr_ready = false;

static void mr_put(uint8_t col, int8_t row, char c) {
    if (row < 0 || row >= MR_ROWS) {
        return;
    }
    oled_set_cursor(col, (uint8_t)row);
    oled_write_char(c, false);
}

static void mr_respawn(uint8_t i) {
    mr_cols[i].head  = -(int8_t)(mr_rand() % 20);
    mr_cols[i].len   = 5 + (uint8_t)(mr_rand() % 8);
    mr_cols[i].speed = 1 + (uint8_t)(mr_rand() % 5);
    mr_cols[i].tick  = 0;
}

static void oled_render_anim(void) {
    static uint32_t mr_timer = 0;

    if (!mr_ready) {
        oled_clear();
        for (uint8_t i = 0; i < MR_COLS; i++) {
            mr_respawn(i);
        }
        mr_ready  = true;
        mr_timer  = timer_read32();
    }

    if (timer_elapsed32(mr_timer) < MR_FRAME_MS) {
        return;
    }
    mr_timer = timer_read32();

    for (uint8_t i = 0; i < MR_COLS; i++) {
        mr_col_t *c = &mr_cols[i];

        if (++c->tick < c->speed) {
            continue;
        }
        c->tick = 0;
        c->head++;

        /* Draw the new head, erase the row the trail just left behind. */
        mr_put(i, c->head, mr_glyph());
        mr_put(i, (int8_t)(c->head - c->len), ' ');

        /* Whole trail has scrolled off the bottom: start a new drop. */
        if (c->head - (int8_t)c->len >= MR_ROWS) {
            mr_respawn(i);
        }
    }

    /* Randomly re-roll a few visible glyphs so the trails flicker. */
    for (uint8_t n = 0; n < MR_SHIMMER; n++) {
        uint8_t   i = mr_rand() % MR_COLS;
        mr_col_t *c = &mr_cols[i];
        if (c->len == 0) {
            continue;
        }
        int8_t row = (int8_t)(c->head - (mr_rand() % c->len));
        mr_put(i, row, mr_glyph());
    }
}
