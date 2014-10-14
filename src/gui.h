/*
 * gui.h
 *
 *      Author: Belle & Bruce
 */
#ifndef STAMPA_H_
#define STAMPA_H_

/** Stampa il menu inziale
 * utilizza le immagini e i font caricate in memoria, e si occupa dell'effetto di ingrandimento, di rimpicciolimento dei pallini di selezione
 * @param menu: indica il valore del campo selezionato nel menu da >1 e <3
 * @param f: variabile contenente i font del gioco di tipo FONT_T
 * @param b: variabile contenente le immagini utilizzate in gioco di tipo BITMAP_T
 * @return void
 */
void draw_screen_menu(const int menu, const FONT_t &f, const BITMAP_t &b);

/** Stampa la pausa
 * @param f: variabile contenente i font del gioco di tipo FONT_T
 * @return void
 */
void draw_pause(const FONT_t &f);

/** Stampa la mappa
 * la stampa della mappa prevede anche un effetto neon grazie a due variabili statiche che modificano l'alpha delle immagini.
 * @param b: variabile contenente le immagini utilizzate in gioco di tipo BITMAP_T
 * @param m: variabile contenente le informazioni riguardanti la mappa di gioco di tipo MAPPA_T
 * @return void
 */
void draw_path(const BITMAP_t &b, const MAPPA_t &m);

/** Stampa pacman
 * @param pg: varibaile contenente i dati di pac-man di tipo PLAYER_T
 * @return void
 */
void draw_pacman(PLAYER_t&pg);

/** Stampa il Countdown iniziale partendo da 3 fino a 1
 * @param f: variabile contenente i font del gioco di tipo FONT_T
 * @param b: variabile contenente le immagini utilizzate in gioco di tipo BITMAP_T
 * @param m: variabile contenente le informazioni riguardanti la mappa di gioco di tipo MAPPA_T
 * @return void
 */
void draw_countdown(const FONT_t &f, const BITMAP_t &b, const MAPPA_t &m);

/**Stampa il fantasma quando e' in fuga
 * @param b: variabile contenente le immagini utilizzate in gioco di tipo BITMAP_T
 * @param pg: varibaile contenente i dati di pac-man di tipo PLAYER_T
 * @param fine_fuga: 0 o 1 e indica se i fantasmi si trovano alla fine della fuga
 * @return void
 */
void draw_fant_fuga(const BITMAP_t &b, FANTASMA_t& f, int fine_fuga);

/**Stampa il fantasma quando e' stato mangiato
 * @param f: variabile contenente i font del gioco di tipo FONT_T
 * @param b: variabile contenente le immagini utilizzate in gioco di tipo BITMAP_T
 * @return void
 */
void draw_fant_mangiato(const BITMAP_t &b, FANTASMA_t& f);

/**Stampa il fantasma
 * @param f: variabile contenente i font del gioco di tipo FONT_T
 * @return void
 */
void draw_fantasma(FANTASMA_t& f);

/**Stampa la frutta
 * @param t: timer di gioco che controlla i secondi trascorsi dall'inizio della vita
 * @param b: variabile contenente le immagini utilizzate in gioco di tipo BITMAP_T
 * @param liv: livello attuale del gioco.
 * @param pg: varibaile contenente i dati di pac-man di tipo PLAYER_T
 * @param a: variabile di tipo struttura AUDIO_T contenente i suoni del gioco
 * @return void
 */
void draw_frutta(ALLEGRO_TIMER *t, BITMAP_t b, int liv, PLAYER_t &pg, AUDIO_t &a);

/**Stampa gAME oVER
 * @param f: variabile contenente i font del gioco di tipo FONT_T
 * @param b: variabile contenente le immagini utilizzate in gioco di tipo BITMAP_T
 * @param nuovo_record: tipo boleano vero se si e' raggiunto un nuovo record
 * @return void
 */
void draw_gameover(const FONT_t &f, const BITMAP_t &b, bool nuovo_record, int punteggio);

/**Stampa gAME wIN
 * @param f: variabile contenente i font del gioco di tipo FONT_T
 * @param b: variabile contenente le immagini utilizzate in gioco di tipo BITMAP_T
 * @param nuovo_record: tipo boleano vero se si e' raggiunto un nuovo record
 * @return void
 */
void draw_win(const FONT_t &f, const BITMAP_t &b, bool nuovo_record);

/**Stampa i controlli del gioco
 * @param f: variabile contenente i font del gioco di tipo FONT_T
 * @param b: variabile contenente le immagini utilizzate in gioco di tipo BITMAP_T
 * @return void
 */
void draw_controls(const FONT_t &f, const BITMAP_t &b);

/**Stampa il record
 * @param f: variabile contenente i font del gioco di tipo FONT_T
 * @param record: contenente il record attualmente raggiunto
 * @return void
 */
void draw_high_score(const FONT_t &f, int record);


#endif /* STAMPA_H_ */
