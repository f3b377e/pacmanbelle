/*
 * logic.cc
 *
 *      Author: Belle & Bruce
 */
//C++ header
#include <iostream>

//allegro header
#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

//header interni
#include "data_struct.h"
#include "logic.h"
#include "io.h"

using namespace std;

void init_audio(AUDIO_t& a)
{
     a.id = NULL;
     a.ghost_eaten = al_load_sample("data/sound/ghost_eaten.wav");
	 if (a.ghost_eaten == NULL)
        cout<<"\n Audio Error, ghost_eaten.wav error!";

	 a.ghosts_scared = al_load_sample("data/sound/ghosts_scared.wav");
	 if (a.ghosts_scared == NULL)
        cout<<"\n Audio Error, ghosts_scared.wav error!";

	 a.pacman_beginning = al_load_sample("data/sound/pacman_beginning.wav");
	 if (a.pacman_beginning == NULL)
        cout<<"\n Audio Error, pacman_beginning.wav error!";

	 a.pacman_eaten = al_load_sample("data/sound/pacman_eaten.wav");
	 if (a.pacman_eaten == NULL)
        cout<<"\n Audio Error, pacman_eaten.wav error!";

	 a.pacman_eatfruit = al_load_sample("data/sound/pacman_eatfruit.wav");
	 if (a.pacman_eatfruit == NULL)
        cout<<"\n Audio Error, pacman_eatfruit.wav error!";

	 a.pallet_eaten1 = al_load_sample("data/sound/pallet_eaten1.wav");
	 if (a.pallet_eaten1 == NULL)
        cout<<"\n Audio Error, pallet_eaten1.wav error!";

	 a.pallet_eaten2 = al_load_sample("data/sound/pallet_eaten2.wav");
	 if (a.pallet_eaten2 == NULL)
        cout<<"\n Audio Error, pallet_eaten2.wav error!";

	 a.siren = al_load_sample("data/sound/siren.wav");
	 if (a.siren == NULL)
        cout<<"\n Audio Error, siren.wav error!";
}

void init_bitmap(BITMAP_t& b)
{
    b.header_image = al_load_bitmap("data/img/pacman_header.jpg");
	 if (b.header_image == NULL)
        cout<<"\n Bitmap Error, pacman_header.jpg error!";

    b.puntino = al_load_bitmap("data/img/puntino_bianco.png");
	 if (b.puntino == NULL)
        cout<<"\n Bitmap Error, puntino_bianco.jpg error!";

    b.autotile = al_load_bitmap("data/img/autotile.jpg");
	 if (b.autotile == NULL)
        cout<<"\n Bitmap Error, autotile.jpg error!";

    b.pacman_image = al_load_bitmap("data/img/pacman2.png");
	 if (b.pacman_image == NULL)
        cout<<"\n Bitmap Error, pacman2.jpg error!";
}

void init_mappa(MAPPA_t& m)
{
    m.c = 0;
    m.r = 0;
    m.mappa = NULL;
}

void init_font(FONT_t& f)
{
    f.h1 = al_load_font("data/font/pac-font.ttf", 32, 0);
	 if (f.h1 == NULL)
        cout<<"\n Font Error, pac-font.ttf error!";
    f.h2 = al_load_font("data/font/pac-font.ttf", 18, 0);
    f.h3 = al_load_font("data/font/pac-font.ttf", 20, 0);
    f.h4 = al_load_font("data/font/orbitron-black.ttf", 10, 0);
    f.h5 = al_load_font("data/font/orbitron-black.ttf", 20, 0);

}

void init_pacman (PLAYER_t& pacman){
	pacman.dir = FERMO;
	pacman.precdir = SX;
	pacman.movespeed = 4;
	pacman.sourcex = 0;
	pacman.sourcey = 0;
	pacman.x = 12*BLOCKSIZE+OFFSETX;
	pacman.y = 23*BLOCKSIZE+OFFSETY;
	pacman.stato = 1;   		/**< da 1 a 3 per la gestione della sprites di pacman*/
	pacman.vita = 3;		    /**< Vite di pacman che possono essere minimo 0 massimo 3*/
	pacman.potente = false;		/**< se vera pacman aumenta la velocità e può mangiare i fantasmi*/
	pacman.punteggio = 0;		/**< punteggio attuale*/
	pacman.mangiato = false;	/**< se vera pacman è mangiato dai fantasmi */
}
/** Funzione di Collisione oggetti
  * pg: Struttura di pacman
  * sx: sorgente x
  * sy: sorgente y
  * sw: larghezza sorgente
  * sh: altezza sorgente
  * dx: destinazione x
  * dy: destinazione y
  * dw: larghezza destinazione
  * dh: altezza destinazione
  * Collision
  */
bool collision (const PLAYER_t &pg, const float sx, const float sy,
                const float sw, const float sh, const float dx,
                const float dy, const float dw, const float dh)
{
    switch (pg.dir){
    case SX:
        if (sx <= dx + dw){
            cout<<"\n Collision Sinistra!";
            return true;
        }
    break;
    case DX:
        if (sx+sw >= dx){
            cout<<"\n Collision Destra!";
            return true;
        }
    break;
    case SU:
        if (sy <= dy+dh){
            cout<<"\n Collision SU!";
            return true;
        }
    break;
    case GIU:
        if (sy+sh >= dy){
            cout<<"\n Collision GIU!";
            return true;
        }
    break;
    }
return false;
}

void dest_font(FONT_t& f)
{
    al_destroy_font(f.h1);
    al_destroy_font(f.h2);
    al_destroy_font(f.h3);
    al_destroy_font(f.h4);
}

void dest_bitmap(BITMAP_t& b)
{
    al_destroy_bitmap(b.autotile);
    al_destroy_bitmap(b.header_image);
    al_destroy_bitmap(b.pacman_image);
    al_destroy_bitmap(b.puntino);
}

