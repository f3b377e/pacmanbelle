/*
 * logic.h
 *
 *      Author: Belle & BruceS
 */
#include "io.h"
#include "gui.h"

#ifndef LOGIC_H_
#define LOGIC_H_

    void init_audio(AUDIO_t&);
    void init_bitmap(BITMAP_t&);
    void init_font(FONT_t&);
    void init_pacman(PLAYER_t&);
    void dest_bitmap(BITMAP_t& b);
    void dest_font(FONT_t& f);

#endif /* LOGIC_H_ */
