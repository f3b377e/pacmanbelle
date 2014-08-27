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
    void dest_bitmap(BITMAP_t& b);
    void dest_font(FONT_t& f);
    void init_mappa(MAPPA_t& m);
    bool collision (const PLAYER_t &, const float, const float,
                    const float, const float, const float,
                    const float, const float, const float);

#endif /* LOGIC_H_ */
