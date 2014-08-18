/*
 * data_struct.h
 *
 *      Author: Belle
 */

//C++ header
#include<iostream>

//allegro header
#include<allegro5/allegro.h>
#include<allegro5/allegro_audio.h>

using namespace std;

//Variabili Globali
const int ScreenWidth = 850;	/**< Larghezza dello schermo*/
const int ScreenHeight = 600;	/**< Altezza dello schermo*/

const int OffsetX = 100;	//non so cosa sia	
const int OffsetY = 112;	//non so cosa sia ahah
const int FPS = 25;		/**< Frame del gioco*/
const int Blocksize = 16;	/**< Blocchi della mappa*/

/**Stato di direzione per pacman e per i fantasmi*/
enum DIREZ{FERMO, SU, GIU, DX, SX};

/** 
 *  Stato del gioco, serve per il loop della funzione ::main per eseguire diverse
 *  operazioni a seconda della fase in cui si trova il gioco
 */
enum STATO_GIOCO{MENU, PLAY, PAUSA, CONTROLS, HIGH_SCORE, GAME_OVER};

/**Struttura contenente i dati del giocatore*/
struct PLAYER_t{
	DIREZ dir;		/**< Stato attuale della direzione di pacman*/
	float movespeed;	/**< Velocità del pacman*/
	int sourcex;		/**< Coordinata x per regione dello sheet di pacman*/
	int sourcey;		/**< Coordinata y per regione dello sheet di pacman*/
	float x;		/**< Coordinata x schermo*/
	float y;		/**< Coordinata y schermo*/
	int stato;		/**< da 1 a tre*/
	int vita;		/**< Vite di pacman che possono essere minimo 0 massimo 3*/
	bool potente;		/**< se vera pacman aumenta la velocità e può mangiare i fantasmi*/
	int punteggio;		/**< punteggio attuale*/
	int record;		/**< miglior punteggio*/
	bool mangiato;		/**< se vera pacman è mangiato dai fantasmi */
};

/**Struttura contenente i dati del singolo fantasma*/
struct FANTASMA_t{
	DIREZ dir;		/**< Stato attuale della direzione del fantasma*/
	float movespeed;	/**< Velocità del fantasma*/
	int sourcex;		/**< Coordinata x per regione dello sheet di pacman*/
	int sourcey;		/**< Coordinata y per regione dello sheet di pacman*/
	float x;		/**< Coordinata x schermo*/
	float y;		/**< Coordinata y schermo*/
	bool debole;		/**< Vera quando pacman mangia il pallino grande. Riduce la velocità dei fantasmi e possono essere mangiati*/
	bool mangiato;		/**< Vera quando pacman mangia il fantasma*/
};

/**Struttura contenente i dati dell'audio*/
struct AUDIO_t{
	ALLEGRO_SAMPLE_ID id; /**< Identificatore audio in riproduzione */ 
 
	ALLEGRO_SAMPLE *ghost_eaten;
	ALLEGRO_SAMPLE *ghosts_scared;
	ALLEGRO_SAMPLE *pacman_beginning;
	ALLEGRO_SAMPLE *pacman_death;
	ALLEGRO_SAMPLE *pacman_eaten;
	ALLEGRO_SAMPLE *pacman_eatfruit;
	ALLEGRO_SAMPLE *pallet_eaten1;
	ALLEGRO_SAMPLE *pallet_eaten2;
	ALLEGRO_SAMPLE *siren;
};
