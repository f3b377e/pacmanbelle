/*
 * init.h
 *
 *      Author: Belle & Bruce
 */
#ifndef INIT_H_
#define INIT_H_
    /**Caricamento dei file audio*/
    void init_audio(AUDIO_t&);
    /**Caricamento delle immagini*/
    void init_bitmap(BITMAP_t&);
    /**Caricamento dei font*/
    void init_font(FONT_t&);
    /**Inizializzazione della mappa*/
    void init_mappa(MAPPA_t &);
    /**Inizializzazione di Pacman*/
    void init_pacman(PLAYER_t&);
    /**Inizializzazione di Blinky*/
    void init_blinky(FANTASMA_t &, int);
    /**Inizializzazione di Pinky*/
    void init_pinky(FANTASMA_t &, int);
    /**Inizializzazione di Inky*/
    void init_inky(FANTASMA_t &, int);
    /**Inizializzazione di Clyde*/
    void init_clyde(FANTASMA_t &, int);
    /**Funzione che dealloca le immagini caricate */
    void dest_bitmap(BITMAP_t &);
    /**Funzione che dealloca i font caricati */
    void dest_font(FONT_t &);
    /**Funzione che dealloca l'audio */
    void dest_audio(AUDIO_t &);

#endif // INIT_H_
