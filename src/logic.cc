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
     //a.id = NULL;
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

	 a.pacman_intermission = al_load_sample("data/sound/pacman_intermission.wav");
	 if (a.pacman_intermission == NULL)
        	cout<<"\n Audio Error, pacman_intermission.wav error!";
}

void init_bitmap(BITMAP_t& b)
{
    b.header_image = al_load_bitmap("data/img/pacman_header.jpg");
	 if (b.header_image == NULL)
        cout<<"\n Bitmap Error, pacman_header error!";

    b.puntino = al_load_bitmap("data/img/puntino_bianco.png");
	 if (b.puntino == NULL)
        cout<<"\n Bitmap Error, puntino_bianco error!";

    b.autotile = al_load_bitmap("data/img/autotile.jpg");
	 if (b.autotile == NULL)
        cout<<"\n Bitmap Error, autotile error!";

    b.pacman_image = al_load_bitmap("data/img/pacman2.png");
	 if (b.pacman_image == NULL)
        cout<<"\n Bitmap Error, pacman2 error!";

    b.blinky = al_load_bitmap("data/img/fantasma1.png");
	 if (b.blinky == NULL)
        cout<<"\n Bitmap Error, blinky - fantasma1 error!";

    b.pinky = al_load_bitmap("data/img/fantasma2.png");
	 if (b.pinky == NULL)
        cout<<"\n Bitmap Error, pinky - fantasma2 error!";

    b.inky = al_load_bitmap("data/img/fantasma3.png");
	 if (b.inky == NULL)
        cout<<"\n Bitmap Error, inky - fantasma3 error!";

    b.clyde = al_load_bitmap("data/img/fantasma4.png");
	 if (b.clyde == NULL)
        cout<<"\n Bitmap Error, clyde - fantasma4 error!";

    b.f_pericolo = al_load_bitmap("data/img/fantasma_pericolo.png");
	 if (b.f_pericolo == NULL)
        cout<<"\n Bitmap Error, clyde - fantasma4 error!";

    b.fantasma1 = al_load_bitmap("data/img/fantasma1.png");
	 if (b.fantasma1 == NULL)
        cout<<"\n Bitmap Error, fantasma1.jpg error!";

    b.fantasma2 = al_load_bitmap("data/img/fantasma2.png");
	 if (b.fantasma2 == NULL)
        cout<<"\n Bitmap Error, fantasma2.jpg error!";

    b.fantasma3 = al_load_bitmap("data/img/fantasma3.png");
	 if (b.fantasma3 == NULL)
        cout<<"\n Bitmap Error, fantasma3.jpg error!";

    b.fantasma4 = al_load_bitmap("data/img/fantasma4.png");
	 if (b.fantasma4 == NULL)
        cout<<"\n Bitmap Error, fantasma4.jpg error!";
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

void init_pacman (PLAYER_t& pacman)
{
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

void init_fantasma (FANTASMA_t& fantasma){
	fantasma.dir = FERMO;
	fantasma.movespeed = 4;
	fantasma.sourcex = 0;
	fantasma.sourcey = 0;
	fantasma.x = 14*BLOCKSIZE+OFFSETX;
	fantasma.y = 13*BLOCKSIZE+OFFSETY;
	fantasma.debole = false;
	fantasma.mangiato = false;
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

void init_blinky(FANTASMA_t &b)
{
    b.dir = FERMO;
    b.sourcex = 0;
    b.sourcey = 0;
    b.movespeed = 4;
    b.x = 13 * BLOCKSIZE + OFFSETX + 8;
    b.y = 13 * BLOCKSIZE + OFFSETY;
    b.debole = false;
    b.mangiato = false;
}

void init_pinky(FANTASMA_t &p)
{
    p.dir = FERMO;
    p.sourcex = 0;
    p.sourcey = 0;
    p.movespeed = 4;
    p.x = 11 * BLOCKSIZE + OFFSETX + 8;
    p.y = 15 * BLOCKSIZE + OFFSETY;
    p.debole = false;
    p.mangiato = false;

}

void init_inky(FANTASMA_t &i)
{
    i.dir = FERMO;
    i.sourcex = 0;
    i.sourcey = 0;
    i.movespeed = 4;
    i.x = 15 * BLOCKSIZE + OFFSETX + 8;
    i.y = 15 * BLOCKSIZE + OFFSETY;
    i.debole = false;
    i.mangiato = false;
}

void init_clyde(FANTASMA_t &c)
{
    c.dir = FERMO;
    c.sourcex = 0;
    c.sourcey = 0;
    c.movespeed = 4;
    c.x = 13 * BLOCKSIZE + OFFSETX + 8;
    c.y = 15 * BLOCKSIZE + OFFSETY;
    c.debole = false;
    c.mangiato = false;
}

void dest_font(FONT_t& f)
{
    al_destroy_font(f.h1);
    al_destroy_font(f.h2);
    al_destroy_font(f.h3);
    al_destroy_font(f.h4);
    al_destroy_font(f.h5);
}

void dest_bitmap(BITMAP_t& b)
{
    al_destroy_bitmap(b.autotile);
    al_destroy_bitmap(b.header_image);
    al_destroy_bitmap(b.pacman_image);
    al_destroy_bitmap(b.puntino);
    al_destroy_bitmap(b.blinky);
    al_destroy_bitmap(b.pinky);
    al_destroy_bitmap(b.clyde);
    al_destroy_bitmap(b.inky);
    al_destroy_bitmap(b.f_pericolo);
}

