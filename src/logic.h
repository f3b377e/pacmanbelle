/*
 * logic.h
 *
 *      Author: Belle & Bruce
 */
#ifndef LOGIC_H_
#define LOGIC_H_

/** Funzione che si occupa del movimento di pacman*/
void move_pacman(PLAYER_t&, MAPPA_t &, AUDIO_t &, bool []);

/** Gestisce il Movimento di Blinky*/
void move_blinky(const MAPPA_t &, const PLAYER_t &, FANTASMA_t &);

/** Gestisce il Movimento di Pinky*/
void move_pinky(const MAPPA_t &, const PLAYER_t &, FANTASMA_t &);

#endif /* LOGIC_H_ */
