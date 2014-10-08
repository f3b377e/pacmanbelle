/*
 * logic.h
 *
 *      Author: Belle & Bruce
 */
#ifndef LOGIC_H_
#define LOGIC_H_

/** Funzione che si occupa del movimento di pacman*/
void move_pacman(PLAYER_t&, MAPPA_t &, AUDIO_t &, bool []);

/** Funzione che si occupa di cambiare le immagini della mappa quando pacman mangia i pallini e richiamare la
 * cambiare la funzione che cambia di stato i fantasmi quando Pacman mangia il pallino powa!
 */
void pac_mangia(MAPPA_t &m, PLAYER_t &pg, AUDIO_t &audio, FANTASMA_t &b, FANTASMA_t &p, FANTASMA_t &i, FANTASMA_t &c,
                ALLEGRO_TIMER *t, int &fuga_count, FONT_t f, int livello);

/**Serve per cambiare lo stato dei fantasmi quando pacman mangia il pallino powa e serve anche per cambiare lo stato quando il tempo di attivazione scade*/
void cambia_stato(FANTASMA_t &b, FANTASMA_t &p, FANTASMA_t &i, FANTASMA_t &c, PLAYER_t &pg);

/**Gestisce il movimento ondulatorio dei fantasmi all'inizio del gioco*/
void ondula(const MAPPA_t &m, FANTASMA_t &f);

/** Gestisce il Movimento di Blinky*/
void move_blinky(const MAPPA_t &, const PLAYER_t &, FANTASMA_t &);

/** Gestisce il Movimento di Pinky*/
void move_pinky(const MAPPA_t &, const PLAYER_t &, FANTASMA_t &);

/** Gestisce il Movimento di Inky*/
void move_inky(const MAPPA_t &, const PLAYER_t &, FANTASMA_t &, FANTASMA_t &);

/** Gestisce il Movimento di Clyde*/
void move_clyde(const MAPPA_t &, const PLAYER_t &, FANTASMA_t &);

/** Ritorna Vero quando pacman collide con un fantasma*/
bool collision_pacman(const PLAYER_t &, const FANTASMA_t &);

/** Gestisce la morte di pacman*/
void death_pacman(PLAYER_t &, STATO_GIOCO &, bool &);

/** Controlla la vittoria del giocatore*/
bool victory(const MAPPA_t &, STATO_GIOCO &, bool &, int &, PLAYER_t &pg);

#endif /* LOGIC_H_ */
