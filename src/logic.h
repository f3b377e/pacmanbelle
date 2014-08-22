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

#endif /* LOGIC_H_ */
