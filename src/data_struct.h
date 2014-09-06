/*
 * data_struct.h
 *
 *      Author: Belle & Bruce
 */
//C++ header
#include<iostream>

//allegro header
#include <allegro5/allegro.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_audio.h>

#ifndef DATA_STRUCT_
#define DATA_STRUCT_

//Variabili Globali
const int SCREENWIDTH = 650;	                /**< Larghezza dello schermo*/
const int SCREENHEIGHT = 600;	                /**< Altezza dello schermo*/
const int OFFSETX = SCREENWIDTH *15/100;	    /**< Margine laterale della finestra */
const int OFFSETY = SCREENHEIGHT *4/100;        /** < Margine Superiore della finestra */
const int FPS = 25;		                        /**< Frame del gioco*/
const int BLOCKSIZE = 16;	                    /**< Blocchi della mappa*/
const char filenamelv1[] = "data/map/map1.txt"; /**< Mappa Livello 1 */
const char filenamelv2[] = "data/map/map2.txt"; /**< Mappa Livello 2 */

/**Stato di direzione per pacman e per i fantasmi*/
enum DIREZ{GIU, SU, SX, DX, FERMO};
/**
 *  Stato del gioco, serve per il loop della funzione ::main per eseguire diverse
 *  operazioni a seconda della fase in cui si trova il gioco
 */
enum STATO_GIOCO{MENU, CARICA, PLAY, PAUSA, CONTROLS, HIGH_SCORE, GAME_OVER, QUIT};

/** Valori che verranno attribuiti all'array tasto del ::main*/
enum TASTI{ UP, DOWN, LEFT, RIGHT, ENTER, D, ESCAPE, SPACE};

struct MAPPA_t{
    int r;          /**< Numero di Colonne*/
    int c;          /**< Numero di Righe*/
    char **mappa;   /**< Matrice che definisce la mappa */
};

/** Descrittore di ogni elemento in lista */
struct ELEM_t{
    ELEM_t *succ;   /**< Puntatore all'elemento sucessivo */
    ELEM_t *prec;   /**< Puntatore all'elemento precedente */
    int x,y;
};

typedef ELEM_t * lista;

/**Struttura contenente i dati del giocatore*/
struct PLAYER_t{
	DIREZ dir;		    /**< Stato attuale della direzione di pacman*/
	DIREZ precdir;		/**< Stato della precedente direzione di pacman*/
	DIREZ succdir;      /**< Stato della sucessiva direzione di pacman*/
	float movespeed;	/**< Velocità del pacman*/
	int sourcex;		/**< Coordinata x per regione dello sheet di pacman*/
	int sourcey;		/**< Coordinata y per regione dello sheet di pacman*/
	float x;		    /**< Coordinata x schermo*/
	float y;		    /**< Coordinata y schermo*/
	int stato;		    /**< da 1 a tre che indica che immagine è in esecuzione*/
	int vita;		    /**< Vite di pacman che possono essere minimo 0 massimo 3*/
	bool potente;		/**< se vera pacman aumenta la velocità e può mangiare i fantasmi*/
	int punteggio;		/**< punteggio attuale*/
	bool mangiato;		/**< se vera pacman è mangiato dai fantasmi */
    ALLEGRO_BITMAP *img;   /**< L'immagine associata a Pacman */

};

/**Struttura contenente i dati del singolo fantasma*/
struct FANTASMA_t{
	DIREZ dir;		    /**< Stato attuale della direzione del fantasma*/
	DIREZ succdir;      /**< Stato della sucessiva direzione di pacman*/
	float movespeed;	/**< Velocità del fantasma*/
	int sourcex;		/**< Coordinata x per regione dello sheet di pacman*/
	int sourcey;		/**< Coordinata y per regione dello sheet di pacman*/
	float x;            /**< Coordinata x schermo*/
	float y;		    /**< Coordinata y schermo*/
	bool debole;		/**< Vera quando pacman mangia il pallino grande. Riduce la velocità dei fantasmi e possono essere mangiati*/
	bool mangiato;		/**< Vera quando pacman mangia il fantasma*/
    ALLEGRO_BITMAP *img;   /**< Immagine relativa al fantasma */

};

/**Struttura contenente i dati dell'audio*/
struct AUDIO_t{
	ALLEGRO_SAMPLE_ID id;               /**< Identificatore audio in riproduzione */
	ALLEGRO_SAMPLE *ghost_eaten;        /**< Quando i fantasmi muoiono*/
	ALLEGRO_SAMPLE *ghosts_scared;      /**< Quando i fantasmi sono in in modalità spavento*/
	ALLEGRO_SAMPLE *pacman_beginning;   /**< Quando inizia il gioco */
	ALLEGRO_SAMPLE *pacman_extrapac;    /**< Quando pacman mangia i pallini speciali*/
	ALLEGRO_SAMPLE *pacman_eaten;       /**< Quando pacman muore */
	ALLEGRO_SAMPLE *pacman_eatfruit;    /**< Quando pacman mangia la frutta */
	ALLEGRO_SAMPLE *pallet_eaten1;      /**< Quando pacman mangia i pallini */
	ALLEGRO_SAMPLE *pallet_eaten2;      /**< Quando pacman mangia i pallini */
	ALLEGRO_SAMPLE *siren;              /**< Quando pacman deve scappare dai fantasmi */
	ALLEGRO_SAMPLE *pacman_intermission;    /**< Per gli intermezzi tra un livello e l'altro*/
};

/**Struttura contenente le bitmap utilizzate*/
struct BITMAP_t{
    ALLEGRO_BITMAP *header_image;   /** Immagine Principale del menu */
    ALLEGRO_BITMAP *puntino;        /** Immagine per la comparsa del puntino nel menu */
    ALLEGRO_BITMAP *autotile;       /** Immagine per la composizione della mappa */
    ALLEGRO_BITMAP *f_pericolo;     /** Fantasmi spaventati e morti*/
    ALLEGRO_BITMAP *frutta;         /** Immagine della frutta*/
};

/**Struttura contenente i font del gioco*/
struct FONT_t{
    ALLEGRO_FONT *h1;   /** Font H1*/
    ALLEGRO_FONT *h2;   /** Font H2*/
    ALLEGRO_FONT *h3;   /** Font H3*/
    ALLEGRO_FONT *h4;   /** Font H4*/
    ALLEGRO_FONT *h5;   /** Font H5*/
};
#endif // DATA_STRUCT_
