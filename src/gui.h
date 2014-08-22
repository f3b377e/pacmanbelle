/*
 * gui.h
 *
 *      Author: Belle & Bruce
 */
#include "data_struct.h"

#ifndef STAMPA_H_
#define STAMPA_H_

void draw_screen_menu(int, FONT_t, BITMAP_t);
void draw_pause(FONT_t);
void draw_path(BITMAP_t);
bool move_pacman(PLAYER_t&, BITMAP_t, bool);

/**
 *  Stampa a video pacman
 */
void draw_pacman(PLAYER_t& pg, BITMAP_t b);

#endif /* STAMPA_H_ */
