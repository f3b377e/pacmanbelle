/*
 * logic.h
 *
 *      Author: Belle & BruceS
 */
#ifndef LOGIC_H_
#define LOGIC_H_

    void init_audio(AUDIO_t&);
    void init_bitmap(BITMAP_t&);
    void init_font(FONT_t&);
    void init_pacman(PLAYER_t&);
    void init_fantasma(FANTASMA_t&);
    void init_blinky(FANTASMA_t &);
    void init_pinky(FANTASMA_t &);
    void init_inky(FANTASMA_t &);
    void init_clyde(FANTASMA_t &);
    void dest_bitmap(BITMAP_t &);
    void dest_font(FONT_t &);
    void init_mappa(MAPPA_t &);
    bool collision (const PLAYER_t &, const float, const float,
                    const float, const float, const float,
                    const float, const float, const float);
    void dest_audio(AUDIO_t &);
    void move_pacman(PLAYER_t&, BITMAP_t, MAPPA_t, AUDIO_t);

#endif /* LOGIC_H_ */
