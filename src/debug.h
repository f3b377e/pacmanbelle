/*
 * debug.h
 *
 *      Author: Belle & Bruce
 */
#ifdef DEBUG_MODE

 void debug_console(ALLEGRO_TIMER *timer, ALLEGRO_TIMER *timer2, PLAYER_t &pacman, FANTASMA_t &blinky, FANTASMA_t &pinky
                   , FANTASMA_t &inky, FANTASMA_t &clyde, MAPPA_t &mappa, AUDIO_t &audio, int &livello, bool &caricamappa, STATO_GIOCO &stato_gioco);
#endif // DEBUG_MODE
