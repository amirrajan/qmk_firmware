/**
 * Conway's Game of Life for the slave OLED, rotated 270 (portrait 32x128).
 *
 * Cells are 2x2 pixels, giving a 16x64 torus (edges wrap). Each row is packed
 * into one uint16_t, so the whole board is 128 bytes and generations are
 * computed bit-parallel: all 16 columns of a row advance in ~20 ops instead of
 * 16 separate neighbour counts.
 *
 * Purely decorative: timer driven, ignores typing.
 */

#pragma once

#define GOL_COLS 16 /* 32px  / 2px cell */
#define GOL_ROWS 64 /* 128px / 2px cell */

#ifndef GOL_FRAME_MS
#    define GOL_FRAME_MS 110 /* generation period */
#endif
#ifndef GOL_SEED_DENSITY
#    define GOL_SEED_DENSITY 40 /* percent of cells alive on reseed */
#endif
#ifndef GOL_STALL_GENS
#    define GOL_STALL_GENS 12 /* still/oscillating this long -> reseed */
#endif
#ifndef GOL_MAX_GENS
#    define GOL_MAX_GENS 500 /* hard reseed so it never gets boring */
#endif
/* Persist PRNG state in EEPROM so each power-on gets a different soup.
 * Without this the slave half has no entropy: its first render happens at
 * the same tick after every boot, so every boot replays the same board. */
#ifndef GOL_EEPROM_SEED
#    define GOL_EEPROM_SEED 1
#endif
/* 1 = HighLife (B36/S23), 0 = Conway's Life (B3/S23).
 * HighLife's extra birth-on-6 rule permits self-replicating patterns, so the
 * board churns for far longer before settling. */
#ifndef GOL_HIGHLIFE
#    define GOL_HIGHLIFE 1
#endif

static uint16_t gol_rows[GOL_ROWS];
static uint16_t gol_next[GOL_ROWS];
static bool     gol_ready = false;

/* Small xorshift PRNG; cheaper than pulling rand() onto AVR. */
static uint16_t gol_rand_state = 0;

static void gol_seed_prng(void) {
#if GOL_EEPROM_SEED
    uint32_t stored = eeconfig_read_user();
    gol_rand_state  = (uint16_t)(stored ^ (stored >> 16)) ^ (uint16_t)timer_read32();
    /* Advance the stored value so the next boot starts somewhere else. */
    eeconfig_update_user(stored * 1664525UL + 1013904223UL);
#else
    gol_rand_state = (uint16_t)timer_read32();
#endif
    if (gol_rand_state == 0) {
        gol_rand_state = 0xACE1u;
    }
}

static uint16_t gol_rand(void) {
    gol_rand_state ^= (uint16_t)(gol_rand_state << 7);
    gol_rand_state ^= (uint16_t)(gol_rand_state >> 9);
    gol_rand_state ^= (uint16_t)(gol_rand_state << 8);
    return gol_rand_state;
}

/* Horizontal wrap: rotate a packed row left/right by one column. */
static inline uint16_t gol_rotl(uint16_t v) {
    return (uint16_t)((v << 1) | (v >> (GOL_COLS - 1)));
}
static inline uint16_t gol_rotr(uint16_t v) {
    return (uint16_t)((v >> 1) | (v << (GOL_COLS - 1)));
}

/* Bit-sliced adders: sum single-bit lanes into 2-bit lanes. */
static inline void gol_add2(uint16_t a, uint16_t b, uint16_t *s0, uint16_t *s1) {
    *s0 = a ^ b;
    *s1 = a & b;
}
static inline void gol_add3(uint16_t a, uint16_t b, uint16_t c, uint16_t *s0, uint16_t *s1) {
    uint16_t t = a ^ b;
    *s0        = t ^ c;
    *s1        = (a & b) | (t & c);
}

/* Draw one cell as a 2x2 pixel block. */
static void gol_draw_cell(uint8_t col, uint8_t row, bool on) {
    uint8_t x = (uint8_t)(col * 2);
    uint8_t y = (uint8_t)(row * 2);
    oled_write_pixel(x, y, on);
    oled_write_pixel((uint8_t)(x + 1), y, on);
    oled_write_pixel(x, (uint8_t)(y + 1), on);
    oled_write_pixel((uint8_t)(x + 1), (uint8_t)(y + 1), on);
}

static void gol_seed(void) {
    for (uint8_t r = 0; r < GOL_ROWS; r++) {
        uint16_t word = 0;
        for (uint8_t c = 0; c < GOL_COLS; c++) {
            if ((gol_rand() % 100) < GOL_SEED_DENSITY) {
                word |= (uint16_t)(1u << c);
            }
        }
        gol_rows[r] = word;
    }

    oled_clear();
    for (uint8_t r = 0; r < GOL_ROWS; r++) {
        for (uint8_t c = 0; c < GOL_COLS; c++) {
            if (gol_rows[r] & (uint16_t)(1u << c)) {
                gol_draw_cell(c, r, true);
            }
        }
    }
}

static void oled_render_anim(void) {
    static uint32_t gol_timer = 0;
    static uint16_t gol_hash1 = 0; /* previous generation  */
    static uint16_t gol_hash2 = 0; /* two generations back */
    static uint8_t  gol_stall = 0;
    static uint16_t gol_gen   = 0;

    if (!gol_ready) {
        gol_seed_prng();
        gol_seed();
        gol_ready = true;
        gol_timer = timer_read32();
        return;
    }

    if (timer_elapsed32(gol_timer) < GOL_FRAME_MS) {
        return;
    }
    gol_timer = timer_read32();

    uint16_t hash = 0;

    for (uint8_t r = 0; r < GOL_ROWS; r++) {
        uint16_t u = gol_rows[(r == 0) ? (GOL_ROWS - 1) : (r - 1)];
        uint16_t m = gol_rows[r];
        uint16_t d = gol_rows[(r == GOL_ROWS - 1) ? 0 : (r + 1)];

        /* Neighbour sum, split into bit planes. */
        uint16_t u0, u1, m0, m1, d0, d1;
        gol_add3(gol_rotl(u), u, gol_rotr(u), &u0, &u1);
        gol_add2(gol_rotl(m), gol_rotr(m), &m0, &m1);
        gol_add3(gol_rotl(d), d, gol_rotr(d), &d0, &d1);

        uint16_t s0, c0, t0, t1, s1, c1;
        gol_add3(u0, m0, d0, &s0, &c0); /* bit 0 of the count */
        gol_add3(u1, m1, d1, &t0, &t1);
        gol_add2(t0, c0, &s1, &c1);     /* bit 1 of the count */
        uint16_t s2 = t1 ^ c1;          /* bit 2: t1 and c1 both carry weight 4 */
        uint16_t s3 = t1 & c1;          /* bit 3: only set when the count is 8  */

        /* Neighbour counts as bit patterns of (s3 s2 s1 s0). */
        uint16_t two   = (uint16_t)(~s0 & s1 & ~s2 & ~s3); /* 0010 */
        uint16_t three = (uint16_t)(s0 & s1 & ~s2 & ~s3);  /* 0011 */

        /* alive = (live && survives) || (dead && born) */
#if GOL_HIGHLIFE
        uint16_t six   = (uint16_t)(~s0 & s1 & s2 & ~s3);  /* 0110 */
        uint16_t alive = (uint16_t)((m & (two | three)) | (~m & (three | six)));
#else
        uint16_t alive = (uint16_t)((m & (two | three)) | (~m & three));
#endif

        gol_next[r] = alive;
        hash        = (uint16_t)((hash << 1 | hash >> 15) ^ alive);
    }

    /* Repaint only the cells that changed. */
    for (uint8_t r = 0; r < GOL_ROWS; r++) {
        uint16_t diff = (uint16_t)(gol_rows[r] ^ gol_next[r]);
        if (diff) {
            for (uint8_t c = 0; c < GOL_COLS; c++) {
                if (diff & (uint16_t)(1u << c)) {
                    gol_draw_cell(c, r, (gol_next[r] & (uint16_t)(1u << c)) != 0);
                }
            }
        }
        gol_rows[r] = gol_next[r];
    }

    /* Still lifes match the last gen, period-2 oscillators match two back. */
    if (hash == gol_hash1 || hash == gol_hash2) {
        gol_stall++;
    } else {
        gol_stall = 0;
    }
    gol_hash2 = gol_hash1;
    gol_hash1 = hash;

    if (gol_stall >= GOL_STALL_GENS || ++gol_gen >= GOL_MAX_GENS) {
        gol_stall = 0;
        gol_gen   = 0;
        gol_hash1 = 0;
        gol_hash2 = 0;
        gol_seed();
    }
}
