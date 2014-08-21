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
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>

//header interni
#include "data_struct.h"
#include "logic.h"
#include "io.h"

void init_audio(AUDIO_t& a)
{
     a.id; /**< non so se va bene*/
	 a.ghost_eaten = al_load_sample("data/sound/ghost_eaten.wav");
	 a.ghosts_scared = al_load_sample("data/sound/ghosts_scared.wav");
	 a.pacman_beginning = al_load_sample("data/sound/pacman_beginning.wav");
	 a.pacman_eaten = al_load_sample("data/sound/pacman_eaten.wav");
	 a.pacman_eatfruit = al_load_sample("data/sound/pacman_eatfruit.wav");
	 a.pallet_eaten1 = al_load_sample("data/sound/pallet_eaten1.wav");
	 a.pallet_eaten2 = al_load_sample("data/sound/pallet_eaten2.wav");
	 a.siren = al_load_sample("data/sound/siren.wav");

}
void init_bitmap(BITMAP_t& b)
{
    b.header_image = al_load_bitmap("data/img/pacman_header.jpg");
    b.puntino = al_load_bitmap("data/img/puntino_bianco.png");
    b.autotile = al_load_bitmap("data/img/autotile.jpg");
    b.main_image = al_load_bitmap("data/img/pacman_all_sprites2.png");
}

void init_font(FONT_t& f)
{
    f.h1 = al_load_font("data/font/pac-font.ttf", 32, 0);
    f.h2 = al_load_font("data/font/pac-font.ttf", 18, 0);
    f.h3 = al_load_font("data/font/pac-font.ttf", 20, 0);
    f.h4 = al_load_font("data/font/orbitron-black.ttf", 10, 0);
}

void init_pacman (PLAYER_t& pacman){
	pacman.dir = FERMO;
	pacman.movespeed = 3;
	pacman.sourcex = 6;
	pacman.sourcey = 6;
	pacman.x = 10;
	pacman.y = 10;
	pacman.stato = 1;   /**< da 1 a 3 per la gestione della sprites di pacman*/
	pacman.vita = 3;		/**< Vite di pacman che possono essere minimo 0 massimo 3*/
	pacman.potente = false;		/**< se vera pacman aumenta la velocità e può mangiare i fantasmi*/
	pacman.punteggio = 0;		/**< punteggio attuale*/
	pacman.mangiato = false;		/**< se vera pacman è mangiato dai fantasmi */
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
    al_destroy_bitmap(b.main_image);
    al_destroy_bitmap(b.puntino);
}
