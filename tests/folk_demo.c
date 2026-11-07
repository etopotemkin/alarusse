/* SPDX-License-Identifier: GPL-3.0-only */
/* Felucca RAVE fork: a folk-rave demo through the real engines (hostsim.c), 130 BPM, 8 bars:
 *   part 0  DRUM FOLK KIT: RUMBLE kick on every beat, spoons on the 16ths, the rattle and tambourine on 2 and 4,
 *           sleigh bells on the off-beats, a hand bell at the turn
 *   part 1  PHYS BALALAIKA: the tune (Korobeiniki, traditional) in tremolo, re-plucked every 1/32
 *   part 2  ANALOG BAYAN: off-beat chords
 *   part 3  VOICE ZHALEIKA: the tune an octave up, bars 5..8
 *   build/host/folk_demo OUT.wav */
#define main hostsim_main
#include "hostsim.c"
#undef main

#define BPM 130u
#define S16 (FS * 60u / BPM / 4u)          /* a 16th, samples */
#define BARS 8u

/* the tune: (16th step, note, length in 16ths) over 4 bars, repeated */
static const uint8_t TUNE[][3] = {
    {0, 76, 4}, {4, 71, 2}, {6, 72, 2}, {8, 74, 4}, {12, 72, 2}, {14, 71, 2},
    {16, 69, 4}, {20, 69, 2}, {22, 72, 2}, {24, 76, 4}, {28, 74, 2}, {30, 72, 2},
    {32, 71, 6}, {38, 72, 2}, {40, 74, 4}, {44, 76, 4},
    {48, 72, 4}, {52, 69, 4}, {56, 69, 8},
};
/* the bayan's chords per bar (Am Am E Am / Dm Am E Am), three notes */
static const uint8_t CHORD[8][3] = {
    {57, 60, 64}, {57, 60, 64}, {56, 59, 64}, {57, 60, 64}, {57, 62, 65}, {57, 60, 64}, {56, 59, 64}, {57, 60, 64},
};

static void note(uint32_t p, uint32_t n, uint32_t vel) { trk_note_on(&trk[p], n, vel); }
static void off(uint32_t p, uint32_t n) { trk_note_off(&trk[p], n); }

int main(int argc, char **argv)
{
    const char *out = argc > 1 ? argv[1] : "folk_demo.wav";
    uint32_t frames = BARS * 16u * S16 + 2u * FS, f, k;
    FILE *w;
    host_tracks_init();
    host_preset(&trk[0], ENGI_DRUM, 5);                  /* FOLK KIT */
    host_preset(&trk[1], ENGI_PHYS, 9);                  /* BALALAIKA */
    host_preset(&trk[2], 0, 12);                         /* BAYAN */
    host_preset(&trk[3], 5, 4);                          /* ZHALEIKA */
    trk[2].p[P_LEVEL] = 70;
    trk[3].p[P_LEVEL] = 80;
    song.master_q12 = 4096;
    w = fopen(out, "wb");
    if (!w)
        return 1;
    wav_hdr(w, frames);
    for (f = 0; f < frames; f += CTL) {
        int32_t o[2 * CTL];
        uint32_t s = f / S16, ph = f % S16, step = s % 64u, bar = s / 16u;
        int on16 = ph < CTL, on32 = (f % (S16 / 2u)) < CTL;
        if (bar < BARS) {
            if (on16) {                                  /* drums */
                uint32_t b = step % 16u;
                if (b % 4u == 0)
                    note(0, 36, 120);                     /* KICK: RUMBLE */
                note(0, 42, b % 2u ? 70 : 95);            /* spoons on every 16th */
                if (b == 4u || b == 12u) {
                    note(0, 39, 100);                     /* the rattle */
                    note(0, 38, 90);                      /* the tambourine */
                }
                if (b % 4u == 2u)
                    note(0, 46, 85);                      /* sleigh bells, off-beats */
                if (b == 14u && bar % 2u)
                    note(0, 37, 80);                      /* higher spoons */
                if (step == 60u)
                    note(0, 56, 90);                      /* the hand bell at the turn */
                if (b == 2u || b == 6u || b == 10u || b == 14u) {   /* bayan off-beat chords, a 16th long */
                    for (k = 0; k < 3u; k++)
                        note(2, CHORD[bar][k], 90);
                } else if (b == 3u || b == 7u || b == 11u || b == 15u) {
                    for (k = 0; k < 3u; k++)
                        off(2, CHORD[bar][k]);
                }
            }
            if (ph >= S16 / 2u && ph < S16 / 2u + CTL) { /* drum key-offs half a 16th later (the hits ring on) */
                static const uint8_t DN[] = {36, 37, 38, 39, 42, 46, 56};
                for (k = 0; k < sizeof DN; k++)
                    off(0, DN[k]);
            }
            for (k = 0; k < NELEM(TUNE); k++) {           /* the tune */
                uint32_t a = TUNE[k][0], e = a + TUNE[k][2];
                if (step >= a && step < e) {
                    if (on32)                             /* balalaika tremolo: re-pluck every 1/32 */
                        note(1, TUNE[k][1] - 12u, step == a && ph < CTL ? 110 : 80);
                    if (bar >= 4u && step == a && on16)
                        note(3, TUNE[k][1], 100);
                }
                if (step == e % 64u && on16) {
                    off(1, TUNE[k][1] - 12u);
                    if (bar >= 4u || (bar == 4u && e == 64u))
                        off(3, TUNE[k][1]);
                }
            }
        } else if (s == BARS * 16u && on16) {
            note(0, 36, 127);                             /* the last kick, and the bell */
            note(0, 56, 100);
            for (k = 0; k < NELEM(TUNE); k++)
                off(1, TUNE[k][1] - 12u), off(3, TUNE[k][1]);
        }
        mix_block(o, CTL);
        for (k = 0; k < CTL; k++)
            wav_put(w, o[2 * k], o[2 * k + 1]);
    }
    fclose(w);
    return 0;
}
