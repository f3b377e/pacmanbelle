/*
 * logic.h
 *
 *      Author: Belle & Bruce
 */
#ifndef LOGIC_H_
#define LOGIC_H_

/**La funzione gestisce l'animazione del menu in base al tasto premuto
 * @param menu: indica quale campo si sta selezionando
 * @param tasto: array contenente lo stato dei tasti premuti o rilasciati
 * @param stato_gioco: indica lo stato del gioco di tipo STATO_GIOCO
 * @param pg: varibaile contenente i dati di pac-man di tipo PLAYER_T
 * @param a: variabile di tipo struttura AUDIO_T contenente i suoni del gioco.
 */
void anima_menu(int &menu, bool tasto[],STATO_GIOCO &stato_gioco, PLAYER_t &pg, AUDIO_t &a);

/** Funzione che si occupa del movimento di pacman
 * @param pg: varibaile contenente i dati di pac-man di tipo PLAYER_T
 * @param a: variabile di tipo struttura AUDIO_T contenente i suoni del gioco.
 * @param tasto: array contenente lo stato dei tasti premuti o rilasciati
 * @param m: variabile contenente le informazioni riguardanti la mappa di gioco di tipo MAPPA_T
*/
void move_pacman(PLAYER_t& pg, MAPPA_t &m, AUDIO_t &a, bool tasto[]);

/** Funzione che si occupa di qualcosa
 * @param m: variabile contenente le informazioni riguardanti la mappa di gioco di tipo MAPPA_T
 * @param pg: varibaile contenente i dati di pac-man di tipo PLAYER_T
 * @param a: variabile di tipo struttura AUDIO_T contenente i suoni del gioco.
 * @param b: variabile di tipo FANTASMA_T contenente le informazioni di blinky
 * @param p: variabile di tipo FANTASMA_T contenente le informazioni di pinky
 * @param i: variabile di tipo FANTASMA_T contenente le informazioni di inky
 * @param c: variabile di tipo FANTASMA_T contenente le informazioni di clyde
 * @param t: timer di gioco che controlla i secondi trascorsi dall'inizio della vita
 * @param fuga_count: contatore che gestisce la fine della modalità di fuga dei fantasmi
 * @param livello: livello corrente in gioco.
 */
void pac_mangia(MAPPA_t &m, PLAYER_t &pg, AUDIO_t &audio, FANTASMA_t &b, FANTASMA_t &p, FANTASMA_t &i, FANTASMA_t &c,
                ALLEGRO_TIMER *t, int &fuga_count, int livello);

/**Serve per cambiare lo stato dei fantasmi quando pacman mangia il pallino powa
 e serve anche per cambiare lo stato quando il tempo di attivazione scade
 * @param b: variabile di tipo FANTASMA_T contenente le informazioni di blinky
 * @param p: variabile di tipo FANTASMA_T contenente le informazioni di pinky
 * @param i: variabile di tipo FANTASMA_T contenente le informazioni di inky
 * @param c: variabile di tipo FANTASMA_T contenente le informazioni di clyde
 * @param pg: varibaile contenente i dati di pac-man di tipo PLAYER_T
 */
void cambia_stato(FANTASMA_t &b, FANTASMA_t &p, FANTASMA_t &i, FANTASMA_t &c, PLAYER_t &pg);

/**Gestisce il movimento ondulatorio dei fantasmi all'inizio del gioco
 * @param m: variabile contenente le informazioni riguardanti la mappa di gioco di tipo MAPPA_T
 * @param f: variabile contenente le informazioni del fantasma
 */
void ondula(const MAPPA_t &m, FANTASMA_t &f);

/** Gestisce il Movimento di Blinky
 * @param m: variabile contenente le informazioni riguardanti la mappa di gioco di tipo MAPPA_T
 * @param pg: varibaile contenente i dati di pac-man di tipo PLAYER_T
 * @param f: variabile contenente le informazioni del fantasma
 */
void move_blinky(const MAPPA_t &m, const PLAYER_t &pg, FANTASMA_t &f);

/** Gestisce il Movimento di Pinky
 * @param m: variabile contenente le informazioni riguardanti la mappa di gioco di tipo MAPPA_T
 * @param pg: varibaile contenente i dati di pac-man di tipo PLAYER_T
 * @param f: variabile contenente le informazioni del fantasma
 */
void move_pinky(const MAPPA_t &m, const PLAYER_t &pg, FANTASMA_t &f);

/** Gestisce il Movimento di Inky
 * @param m: variabile contenente le informazioni riguardanti la mappa di gioco di tipo MAPPA_T
 * @param pg: varibaile contenente i dati di pac-man di tipo PLAYER_T
 * @param f: variabile contenente le informazioni del fantasma
 */
void move_inky(const MAPPA_t &m, const PLAYER_t &pg, FANTASMA_t &f, FANTASMA_t &b);

/** Gestisce il Movimento di Clyde
 * @param m: variabile contenente le informazioni riguardanti la mappa di gioco di tipo MAPPA_T
 * @param pg: varibaile contenente i dati di pac-man di tipo PLAYER_T
 * @param f: variabile contenente le informazioni del fantasma
 */
void move_clyde(const MAPPA_t &m, const PLAYER_t &pg, FANTASMA_t &f);

/** Ritorna Vero quando pacman collide con un fantasma
 * @param p: varibaile contenente i dati di pac-man di tipo PLAYER_T
 * @param f: variabile contenente le informazioni del fantasma
 */
bool collision_pacman(const PLAYER_t &p, const FANTASMA_t &f);

/** Gestisce la morte di pacman
 * @param m: variabile contenente le informazioni riguardanti la mappa di gioco di tipo MAPPA_T
 * @param stato: indica lo stato del gioco di tipo STATO_GIOCO
 * @param caricamappa: indica se è presente la mappa, true se è caricata in memoria.
 */
void death_pacman(PLAYER_t &pg, STATO_GIOCO &stato, bool &caricamappa);

/** Controlla la vittoria del giocatore
 * @param m: variabile contenente le informazioni riguardanti la mappa di gioco di tipo MAPPA_T
 * @param stato: indica lo stato del gioco di tipo STATO_GIOCO
 * @param caricamappa: indica se è presente la mappa, true se è caricata in memoria.
 * @param livello: livello corrente in gioco.
 */
bool victory(const MAPPA_t &m, STATO_GIOCO &stato, bool &caricamappa, int &livello, PLAYER_t &pg);

/** Controlla la logica dei fantasmi
 * @param pacman: varibaile contenente i dati di pac-man di tipo PLAYER_T
 * @param blinky: variabile di tipo FANTASMA_T contenente le informazioni di blinky
 * @param pinky: variabile di tipo FANTASMA_T contenente le informazioni di pinky
 * @param inky: variabile di tipo FANTASMA_T contenente le informazioni di inky
 * @param clyde: variabile di tipo FANTASMA_T contenente le informazioni di clyde
 * @param m: variabile contenente le informazioni riguardanti la mappa di gioco di tipo MAPPA_T
 * @param timer2: timer di gioco che controlla i secondi trascorsi dall'inizio della vita
 */
void controlla_fantasmi(PLAYER_t &pacman, FANTASMA_t &blinky, FANTASMA_t &inky,
                        FANTASMA_t &clyde, FANTASMA_t &pinky, MAPPA_t &mappa,
                        ALLEGRO_TIMER *timer2);
#endif /* LOGIC_H_ */
