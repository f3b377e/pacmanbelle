/*
 * gui.h
 *
 *      Author: Belle & Bruce
 */
#ifndef STAMPA_H_
#define STAMPA_H_

void draw_screen_menu(const int menu, FONT_t, BITMAP_t);
void draw_pause(FONT_t);
void draw_path(BITMAP_t, const MAPPA_t &);
void move_pacman(PLAYER_t&, BITMAP_t, MAPPA_t, AUDIO_t);
void draw_pacman(PLAYER_t&, BITMAP_t );
void draw_countdown(FONT_t &, BITMAP_t &, const MAPPA_t &);

#endif /* STAMPA_H_ */
