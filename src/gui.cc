/*
 * gui.cc
 *
 *      Author: Belle & Bruce
 */

#include <stdio.h>
#include <iostream>
#include <fstream>

#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>

#include "data_struct.h"
#include "gui.h"


void draw_screen_menu(int menu)
{

   ALLEGRO_FONT *h1 = al_load_font("data/font/pac-font.ttf", 32, 0);
   ALLEGRO_FONT *h2 = al_load_font("data/font/pac-font.ttf", 18, 0);
   ALLEGRO_FONT *h4 = al_load_font("data/font/orbitron-black.ttf", 10, 0);

   ALLEGRO_BITMAP *header_image = al_load_bitmap("data/img/pacman_header.jpg");
   ALLEGRO_BITMAP *puntino = al_load_bitmap("data/img/puntino_bianco.png");

    /*
     *ho ridotto del codice che era ridondante, per esempio le draw_text le ho messe prima dello switch dato che venivano scritte
     *in modo uguale per ogni case, questo quindi non comporta nessuna modifica dal lato dell'utente
     */
    al_clear_to_color(al_map_rgb(0,0,0));
    al_draw_text(h1, al_map_rgb(255,255,255), ScreenWidth / 2, ScreenHeight *10/100, ALLEGRO_ALIGN_CENTER, "pACMAN gAME");
    al_draw_bitmap(header_image, ScreenWidth *25/100, ScreenHeight *25/100, 0);
    al_draw_text(h2, al_map_rgb(255,255,255), ScreenWidth / 2, ScreenHeight *55/100, ALLEGRO_ALIGN_CENTER, "sTART gAME");
    al_draw_text(h2, al_map_rgb(255,255,255), ScreenWidth / 2, ScreenHeight *65/100, ALLEGRO_ALIGN_CENTER, "cONTROLS");
    al_draw_text(h2, al_map_rgb(255,255,255), ScreenWidth / 2, ScreenHeight *75/100, ALLEGRO_ALIGN_CENTER, "hIGH sCORES");
    al_draw_text(h4, al_map_rgb(255,255,255), ScreenWidth / 2, ScreenHeight *95/100, ALLEGRO_ALIGN_CENTER, "Powered by Belle");

    switch (menu)
    {
      case 0:
      break;
      case 1:
            al_draw_bitmap(puntino, ScreenWidth *65/100, ScreenHeight *56/100, 0);
            al_draw_bitmap(puntino, ScreenWidth *35/100, ScreenHeight *56/100, 0);
      break;
      case 2:
            al_draw_bitmap(puntino, ScreenWidth *65/100, ScreenHeight *66/100, 0);
            al_draw_bitmap(puntino, ScreenWidth *35/100, ScreenHeight *66/100, 0);
      break;
      case 3:
            al_draw_bitmap(puntino, ScreenWidth *65/100, ScreenHeight *76/100, 0);
            al_draw_bitmap(puntino, ScreenWidth *35/100, ScreenHeight *76/100, 0);
      break;
    }
    al_flip_display();
}

/* -------- White-Points --------- */
void draw_points(){

   ALLEGRO_COLOR color_white = al_color_html("f0f2ef");

int dist = 20;
int points_x = 30;
int points_y = 20;

	al_clear_to_color(al_map_rgb(0,0,0));
	for (int i=OffsetX; i<OffsetX + points_x*dist; i=i+dist)
		for (int j=OffsetY; j<OffsetY + points_y*dist; j=j+dist)
			al_draw_filled_circle(i, j, 2, color_white );

	al_flip_display();
}

/*  NON USARE
 *  non funziona bene, da problemi con gli eventi!
 *  link a gui.h nn fatto
 *
 *  Funzione che stampa il conto alla rovescia 3... 2... 1...
 */


void draw_pause()
{
    ALLEGRO_FONT *h2 = al_load_font("data/font/pac-font.ttf", 20, 0);

    al_draw_text(h2, al_map_rgb(255,255,255), ScreenWidth / 2, ScreenHeight *50/100, ALLEGRO_ALIGN_CENTER, "gAME pAUSE");
	al_flip_display();
}

/*  NON USARE
 *  non funziona bene, da problemi con gli eventi!
 *  link a gui.h nn fatto
 *
 *  Funzione che stampa il conto alla rovescia 3... 2... 1...
 */
void draw_countdown()
{
    ALLEGRO_FONT *h2 = al_load_font("data/font/pac-font.ttf", 20, 0);
    ALLEGRO_FONT *h4 = al_load_font("data/font/orbitron-black.ttf", 18, 0);

        al_draw_text(h2, al_map_rgb(255,255,255), ScreenWidth / 2, ScreenHeight *50/100, ALLEGRO_ALIGN_CENTER, "gAME pAUSE");
        al_draw_text(h4, al_map_rgb(255,255,255), ScreenWidth *40/100, ScreenHeight *60/100, ALLEGRO_ALIGN_CENTER, "3");
        al_flip_display();
        al_rest(1.0);

        al_draw_text(h2, al_map_rgb(255,255,255), ScreenWidth / 2, ScreenHeight *50/100, ALLEGRO_ALIGN_CENTER, "gAME pAUSE");
        al_draw_text(h4, al_map_rgb(255,255,255), ScreenWidth *50/100, ScreenHeight *60/100, ALLEGRO_ALIGN_CENTER, "2");
        al_flip_display();
        al_rest(1.0);

        al_draw_text(h2, al_map_rgb(255,255,255), ScreenWidth / 2, ScreenHeight *50/100, ALLEGRO_ALIGN_CENTER, "gAME pAUSE");
        al_draw_text(h4, al_map_rgb(255,255,255), ScreenWidth *60/100, ScreenHeight *60/100, ALLEGRO_ALIGN_CENTER, "1");
        al_rest(1.0);
        al_flip_display();
}


void draw_path()
{
   ALLEGRO_BITMAP *background = al_load_bitmap("data/img/autotile.jpg");

    al_clear_to_color(al_map_rgb(0,0,0));

    char mapfilename[] = "data/map/map2.txt";
    int mapx, mapy;
    std::ifstream f(mapfilename);

    f >> mapx >> mapy;
    char maps[mapx][mapy];

    for (int j = 0; j < mapy; j++){
        std::cout<<"\n";
        for (int i=0; i < mapx; i++){
            f >> maps[i][j];
            std::cout<<maps[i][j]<<" ";
            switch (maps[i][j]){
                case '0':
                    al_draw_bitmap_region(background, 32, 0, Blocksize, Blocksize, Blocksize * i + 20, Blocksize * j + 20, 0);
                break;
                case 'B':
                    al_draw_bitmap_region(background, 0, 0, Blocksize, Blocksize, Blocksize * i + 20, Blocksize * j + 20, 0);
                break;
                case 'C':
                    al_draw_bitmap_region(background, 16, 0, Blocksize, Blocksize, Blocksize * i + 20, Blocksize * j + 20, 0);
                break;
                case 'D':
                    al_draw_bitmap_region(background, 48, 0, Blocksize, Blocksize, Blocksize * i + 20, Blocksize * j + 20, 0);
                break;
                case 'E':
                    al_draw_bitmap_region(background, 0, 16, Blocksize, Blocksize, Blocksize * i + 20, Blocksize * j + 20, 0);
                break;
                case 'F':
                    al_draw_bitmap_region(background, 16, 16, Blocksize, Blocksize, Blocksize * i + 20, Blocksize * j + 20, 0);
                break;
                case 'G':
                    al_draw_bitmap_region(background, 32, 16, Blocksize, Blocksize, Blocksize * i + 20, Blocksize * j + 20, 0);
                break;
                case 'H':
                    al_draw_bitmap_region(background, 48, 16, Blocksize, Blocksize, Blocksize * i + 20, Blocksize * j + 20, 0);
                break;
                case 'I':
                    al_draw_bitmap_region(background, 0, 32, Blocksize, Blocksize, Blocksize * i + 20, Blocksize * j + 20, 0);
                break;
                case 'L':
                    al_draw_bitmap_region(background, 16, 32, Blocksize, Blocksize, Blocksize * i + 20, Blocksize * j + 20, 0);
                break;
                case 'M':
                    al_draw_bitmap_region(background, 32, 32, Blocksize, Blocksize, Blocksize * i + 20, Blocksize * j + 20, 0);
                break;
                case 'N':
                    al_draw_bitmap_region(background, 48, 32, Blocksize, Blocksize, Blocksize * i + 20, Blocksize * j + 20, 0);
                break;
                case 'P':
                    al_draw_bitmap_region(background, 0, 48, Blocksize, Blocksize, Blocksize * i + 20, Blocksize * j + 20, 0);
                break;
                case 'Q':
                    al_draw_bitmap_region(background, 16, 48, Blocksize, Blocksize, Blocksize * i + 20, Blocksize * j + 20, 0);
                break;
                case 'R':
                    al_draw_bitmap_region(background, 32, 48, Blocksize, Blocksize, Blocksize * i + 20, Blocksize * j + 20, 0);
                break;
                case 'S':
                    al_draw_bitmap_region(background, 48, 48, Blocksize, Blocksize, Blocksize * i + 20, Blocksize * j + 20, 0);
                break;
            }
        }
    }
    al_destroy_bitmap(background);

}


void move_pacman(PLAYER_t& pg)
{

   ALLEGRO_BITMAP *main_image = al_load_bitmap("data/img/pacman_all_sprites2.png");
   ALLEGRO_BITMAP *background = al_load_bitmap("data/img/autotile.jpg");


	switch (pg.dir)
	{
	   case FERMO:
		pg.dir = FERMO;
	   break;
	   case SU:
		pg.dir = SU;
		pg.stato +=1;
		pg.sourcey = 6*3 + 14*2 ;
		pg.y -= pg.movespeed;
	   break;
	   case GIU:
		pg.dir = GIU;
		pg.stato +=1;
		pg.sourcey = 6*4 + 14*3 ;
		pg.y += pg.movespeed;
	   break;
	   case SX:
		pg.dir = SX;
		pg.stato +=1;
		pg.sourcey = 6;
		pg.x -= pg.movespeed;
	   break;
	   case DX:
		pg.dir = DX;
		pg.stato +=1;
		pg.sourcey = 6*2 + 14*1 ;
		pg.x += pg.movespeed;
	   break;
	}

	al_clear_to_color(al_map_rgb(0,0,0));
    al_draw_bitmap(background, OffsetX, OffsetY, 0);

	if (pg.stato > 9)
		pg.stato = 1;

	if (pg.stato >3  && pg.stato <= 6)
		al_draw_bitmap_region(main_image, 6, pg.sourcey, 14, 14, pg.x, pg.y, 0);

	else if (pg.stato > 0 && pg.stato <= 3)
		al_draw_bitmap_region(main_image, 6 * 2 + 14, pg.sourcey, 14, 14, pg.x, pg.y, 0);
	else if (pg.stato > 6 && pg.stato <= 9)
		al_draw_bitmap_region(main_image, 6 * 3 + 14 * 2, 6, 14, 14, pg.x, pg.y, 0);

	al_flip_display();

	al_destroy_bitmap(background);
}

void pippo(){}
