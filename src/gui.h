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
void anima_menu(int &, bool [],STATO_GIOCO &);

/** Stampa il menu inziale*/
void draw_screen_menu(const int menu, const FONT_t &, const BITMAP_t &);

/** Stampa la pausa*/
void draw_pause(const FONT_t &);

/** Stampa la mappa*/
void draw_path(const BITMAP_t &, const MAPPA_t &);

/** Stampa pacman*/
void draw_pacman(PLAYER_t&);

/** Stampa il Countdown iniziale*/
void draw_countdown(const FONT_t &, const BITMAP_t &, const MAPPA_t &);

/**Stampa il fantasma quando è in fuga*/
void draw_fant_fuga(const BITMAP_t &b, FANTASMA_t& pg, int fine_fuga);

/**Stampa il fantasma quando è stato mangiato*/
void draw_fant_mangiato(const BITMAP_t &b, FANTASMA_t& pg);

/** Stampa il fantasma*/
void draw_fantasma(FANTASMA_t&);

/** Stampa gAME oVER*/
void draw_gameover(const FONT_t &, const BITMAP_t &, bool nuovo_record);

/** Stampa gAME wIN*/
void draw_win(const FONT_t &, const BITMAP_t &, bool nuovo_record);


#endif /* STAMPA_H_ */
