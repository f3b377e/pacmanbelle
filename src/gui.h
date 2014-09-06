/*
 * gui.h
 *
 *      Author: Belle & Bruce
 */
#ifndef STAMPA_H_
#define STAMPA_H_

/**La funzione gestisce l'animazione del menu in base al tasto premuto
 * Parametri: menu, indica quale campo si sta selezionando
 * Parametri: tasto, array contenente lo stato dei tasti premuti o rilasciati
 * Parametri: stato_gioco, stato del gioco
 */
void anima_menu(int &menu, bool tasto[],STATO_GIOCO &stato_gioco);
void draw_screen_menu(const int menu, FONT_t, BITMAP_t);
void draw_pause(FONT_t);
void draw_path(BITMAP_t, const MAPPA_t &);
void draw_pacman(PLAYER_t&, BITMAP_t );
void draw_countdown(FONT_t &, BITMAP_t &, const MAPPA_t &);
void draw_blinky(FANTASMA_t&, const BITMAP_t &);
void draw_pinky(FANTASMA_t&, const BITMAP_t &);
void draw_inky(FANTASMA_t&, const BITMAP_t &);
void draw_clyde(FANTASMA_t&, const BITMAP_t &);

#endif /* STAMPA_H_ */
