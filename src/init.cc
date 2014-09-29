/*
 * init.cc
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

     a.pacman_extrapac = al_load_sample("data/sound/pacman_extrapac.wav");
	 if (a.pacman_extrapac == NULL)
        	cout<<"\n Audio Error, pacman_extrapac.wav error!";
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

    b.f_pericolo = al_load_bitmap("data/img/fantasma_pericolo.png");
	 if (b.f_pericolo == NULL)
        cout<<"\n Bitmap Error, clyde - fantasma4 error!";

    b.frutta= al_load_bitmap("data/img/frutta.png");
	 if (b.frutta == NULL)
        cout<<"\n Bitmap Error, frutta.png error!";
    b.morte= al_load_bitmap("data/img/morte.png");
	 if (b.frutta == NULL)
        cout<<"\n Bitmap Error, morte.png error!";
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
    if (f.h1 == NULL)
        cout<<"\n Font Error, orbitron-black.ttf error!";
    f.h5 = al_load_font("data/font/orbitron-black.ttf", 20, 0);
}

void init_pacman (PLAYER_t& pacman)
{
	pacman.dir = FERMO;
	pacman.precdir = SX;
	pacman.succdir = FERMO;
	pacman.movespeed = 5;
	pacman.sourcex = 0;
	pacman.sourcey = 0;
	pacman.x = 13*BLOCKSIZE+OFFSETX;
	pacman.y = 23*BLOCKSIZE+OFFSETY;
	pacman.potente = false;		/**< se vera pacman aumenta la velocità e può mangiare i fantasmi*/
	pacman.punteggio = 0;		/**< punteggio attuale*/
	pacman.mangiato = false;	/**< se vera pacman è mangiato dai fantasmi */
	pacman.vita = 2;
    pacman.img = al_load_bitmap("data/img/pacman2.png");
	 if (pacman.img == NULL)
        cout<<"\n Bitmap Error, pacman2 error!";
}


void init_blinky(FANTASMA_t &b)
{
    b.dir = SU;
    b.sourcex = 0;
    b.sourcey = 0;
    b.stato = INSEGUIMENTO;
    b.movespeed = 4;
    b.x = 13 * BLOCKSIZE + OFFSETX;
    b.y = 13 * BLOCKSIZE + OFFSETY;
    b.mangiato = false;
    b.img = al_load_bitmap("data/img/fantasma1.png");
    if(b.img == NULL)
        cout<<"\n Bitmap Error, blinky - fantasma1 error!";
}

void init_pinky(FANTASMA_t &p)
{
    p.dir = SU;
    p.sourcex = 0;
    p.sourcey = 0;
    p.stato = ONDULA;
    p.movespeed = 4;
    p.x = 11 * BLOCKSIZE + OFFSETX;
    p.y = 15 * BLOCKSIZE + OFFSETY;
    p.mangiato = false;
    p.img = al_load_bitmap("data/img/fantasma2.png");
    if(p.img == NULL)
        cout<<"\n Bitmap Error, pinky - fantasma2 error!";
}

void init_inky(FANTASMA_t &i)
{
    i.dir = SU;
    i.sourcex = 0;
    i.sourcey = 0;
    i.stato = ONDULA;
    i.movespeed = 4;
    i.x = 15 * BLOCKSIZE + OFFSETX;
    i.y = 15 * BLOCKSIZE + OFFSETY;
    i.mangiato = false;
    i.img = al_load_bitmap("data/img/fantasma3.png");
    if(i.img == NULL)
        cout<<"\n Bitmap Error, inky - fantasma3 error!";
}

void init_clyde(FANTASMA_t &c)
{
    c.dir = SU;
    c.sourcex = 0;
    c.sourcey = 0;
    c.stato = ONDULA;
    c.movespeed = 4;
    c.x = 13 * BLOCKSIZE + OFFSETX;
    c.y = 15 * BLOCKSIZE + OFFSETY;
    c.mangiato = false;
    c.img = al_load_bitmap("data/img/fantasma4.png");
    if(c.img == NULL)
        cout<<"\n Bitmap Error, clyde - fantasma4 error!";
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
    al_destroy_bitmap(b.puntino);
    al_destroy_bitmap(b.f_pericolo);
    al_destroy_bitmap(b.frutta);
}

void dest_audio(AUDIO_t& a)
{
    #if defined(unix) || defined(__unix__) || defined(__unix)
        al_destroy_sample(a.ghost_eaten);
        al_destroy_sample(a.ghosts_scared);
        al_destroy_sample(a.pacman_beginning);
        al_destroy_sample(a.pacman_extrapac);
        al_destroy_sample(a.pacman_eaten);
        al_destroy_sample(a.pacman_eatfruit);
        al_destroy_sample(a.pallet_eaten1);
        al_destroy_sample(a.pallet_eaten2);
        al_destroy_sample(a.siren);
        al_destroy_sample(a.pacman_intermission);
    #endif // defined unix
    #if defined(_WIN32)
        al_free(a.ghost_eaten);
        al_free(a.ghosts_scared);
        al_free(a.pacman_beginning);
        al_free(a.pacman_eaten);
        al_free(a.pacman_extrapac);
        al_free(a.pacman_eatfruit);
        al_free(a.pallet_eaten1);
        al_free(a.pallet_eaten2);
        al_free(a.siren);
        al_free(a.pacman_intermission);
    #endif // defined win32
}

