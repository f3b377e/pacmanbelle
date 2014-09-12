/*
 * logic.h
 *
 *      Author: Belle & Bruce
 */
#ifndef LOGIC_H_
#define LOGIC_H_

/** Funzione che si occupa del movimento di pacman*/
void move_pacman(PLAYER_t&, MAPPA_t &, AUDIO_t &, bool []);

/**Gestisce il movimento ondulatorio dei fantasmi all'inizio del gioco*/
void ondula(float &y);

/** Gestisce il Movimento di Blinky*/
void move_blinky(const MAPPA_t &, const PLAYER_t &, FANTASMA_t &);

/** Gestisce il Movimento di Pinky*/
void move_pinky(const MAPPA_t &, const PLAYER_t &, FANTASMA_t &);

/** Gestisce il Movimento di Inky*/
void move_inky(const MAPPA_t &, const PLAYER_t &, FANTASMA_t &);

/** Gestisce il Movimento di Clyde*/
void move_clyde(const MAPPA_t &, const PLAYER_t &, FANTASMA_t &);

/** Ritorna Vero quando pacman collide con un fantasma*/
bool collision_pacman(const PLAYER_t &, const FANTASMA_t &);

/** Gestisce la morte di pacman*/
void death_pacman(PLAYER_t &, STATO_GIOCO &, bool &);

/** Controlla la vittoria del giocatore*/
bool victory(const MAPPA_t &, STATO_GIOCO &, bool &);

#endif /* LOGIC_H_ */
