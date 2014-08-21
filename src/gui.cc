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


void draw_screen_menu(int menu, FONT_t f, BITMAP_t b)
{
    al_clear_to_color(al_map_rgb(0,0,0));
    al_draw_text(f.h1, al_map_rgb(255,255,255), SCREENWIDTH / 2, SCREENHEIGHT *10/100, ALLEGRO_ALIGN_CENTER, "pACMAN gAME");
    al_draw_bitmap(b.header_image, SCREENWIDTH *25/100, SCREENHEIGHT *25/100, 0);
    al_draw_text(f.h2, al_map_rgb(255,255,255), SCREENWIDTH / 2, SCREENHEIGHT *55/100, ALLEGRO_ALIGN_CENTER, "sTART gAME");
    al_draw_text(f.h2, al_map_rgb(255,255,255), SCREENWIDTH / 2, SCREENHEIGHT *65/100, ALLEGRO_ALIGN_CENTER, "cONTROLS");
    al_draw_text(f.h2, al_map_rgb(255,255,255), SCREENWIDTH / 2, SCREENHEIGHT *75/100, ALLEGRO_ALIGN_CENTER, "hIGH sCORES");
    al_draw_text(f.h4, al_map_rgb(255,255,255), SCREENWIDTH / 2, SCREENHEIGHT *95/100, ALLEGRO_ALIGN_CENTER, "Powered by Belle & Bruce");

    switch (menu)
    {
      case 0:
      break;
      case 1:
            al_draw_bitmap(b.puntino, SCREENWIDTH *65/100, SCREENHEIGHT *56/100, 0);
            al_draw_bitmap(b.puntino, SCREENWIDTH *35/100, SCREENHEIGHT *56/100, 0);
      break;
      case 2:
            al_draw_bitmap(b.puntino, SCREENWIDTH *65/100, SCREENHEIGHT *66/100, 0);
            al_draw_bitmap(b.puntino, SCREENWIDTH *35/100, SCREENHEIGHT *66/100, 0);
      break;
      case 3:
            al_draw_bitmap(b.puntino, SCREENWIDTH *65/100, SCREENHEIGHT *76/100, 0);
            al_draw_bitmap(b.puntino, SCREENWIDTH *35/100, SCREENHEIGHT *76/100, 0);
      break;
    }
    al_flip_display();
}

void draw_pause(FONT_t f)
{
    al_draw_text(f.h2, al_map_rgb(255,255,255), SCREENWIDTH / 2, SCREENHEIGHT *50/100, ALLEGRO_ALIGN_CENTER, "gAME pAUSE");
	al_flip_display();
}

void draw_path(BITMAP_t b)
{
    al_clear_to_color(al_map_rgb(0,0,0));
    int mapx, mapy;
    std::ifstream f(filenamelv1);

    f >> mapx >> mapy;
    char maps[mapx][mapy];

    for (int j = 0; j < mapy; j++){
        std::cout<<"\n";
        for (int i=0; i < mapx; i++){
            f >> maps[i][j];
            std::cout<<maps[i][j]<<" ";
            switch (maps[i][j]){
                case '0':
                    al_draw_bitmap_region(b.autotile, 32, 0, BLOCKSIZE, BLOCKSIZE, BLOCKSIZE * i + OFFSETX, BLOCKSIZE * j + OFFSETY, 0);
                break;
                case 'B':
                    al_draw_bitmap_region(b.autotile, 0, 0, BLOCKSIZE, BLOCKSIZE, BLOCKSIZE * i + OFFSETX, BLOCKSIZE * j + OFFSETY, 0);
                break;
                case 'C':
                    al_draw_bitmap_region(b.autotile, 16, 0, BLOCKSIZE, BLOCKSIZE, BLOCKSIZE * i + OFFSETX, BLOCKSIZE * j + OFFSETY, 0);
                break;
                case 'D':
                    al_draw_bitmap_region(b.autotile, 48, 0, BLOCKSIZE, BLOCKSIZE, BLOCKSIZE * i + OFFSETX, BLOCKSIZE * j + OFFSETY, 0);
                break;
                case 'E':
                    al_draw_bitmap_region(b.autotile, 0, 16, BLOCKSIZE, BLOCKSIZE, BLOCKSIZE * i + OFFSETX, BLOCKSIZE * j + OFFSETY, 0);
                break;
                case 'F':
                    al_draw_bitmap_region(b.autotile, 16, 16, BLOCKSIZE, BLOCKSIZE, BLOCKSIZE * i + OFFSETX, BLOCKSIZE * j + OFFSETY, 0);
                break;
                case 'G':
                    al_draw_bitmap_region(b.autotile, 32, 16, BLOCKSIZE, BLOCKSIZE, BLOCKSIZE * i + OFFSETX, BLOCKSIZE * j + OFFSETY, 0);
                break;
                case 'H':
                    al_draw_bitmap_region(b.autotile, 48, 16, BLOCKSIZE, BLOCKSIZE, BLOCKSIZE * i + OFFSETX, BLOCKSIZE * j + OFFSETY, 0);
                break;
                case 'I':
                    al_draw_bitmap_region(b.autotile, 0, 32, BLOCKSIZE, BLOCKSIZE, BLOCKSIZE * i + OFFSETX, BLOCKSIZE * j + OFFSETY, 0);
                break;
                case 'L':
                    al_draw_bitmap_region(b.autotile, 16, 32, BLOCKSIZE, BLOCKSIZE, BLOCKSIZE * i + OFFSETX, BLOCKSIZE * j + OFFSETY, 0);
                break;
                case 'M':
                    al_draw_bitmap_region(b.autotile, 32, 32, BLOCKSIZE, BLOCKSIZE, BLOCKSIZE * i + OFFSETX, BLOCKSIZE * j + OFFSETY, 0);
                break;
                case 'N':
                    al_draw_bitmap_region(b.autotile, 48, 32, BLOCKSIZE, BLOCKSIZE, BLOCKSIZE * i + OFFSETX, BLOCKSIZE * j + OFFSETY, 0);
                break;
                case 'P':
                    al_draw_bitmap_region(b.autotile, 0, 48, BLOCKSIZE, BLOCKSIZE, BLOCKSIZE * i + OFFSETX, BLOCKSIZE * j + OFFSETY, 0);
                break;
                case 'Q':
                    al_draw_bitmap_region(b.autotile, 16, 48, BLOCKSIZE, BLOCKSIZE, BLOCKSIZE * i + OFFSETX, BLOCKSIZE * j + OFFSETY, 0);
                break;
                case 'R':
                    al_draw_bitmap_region(b.autotile, 32, 48, BLOCKSIZE, BLOCKSIZE, BLOCKSIZE * i + OFFSETX, BLOCKSIZE * j + OFFSETY, 0);
                break;
                case 'S':
                    al_draw_bitmap_region(b.autotile, 48, 48, BLOCKSIZE, BLOCKSIZE, BLOCKSIZE * i + OFFSETX, BLOCKSIZE * j + OFFSETY, 0);
                break;
                case 'J':
                    al_draw_bitmap_region(b.autotile, 0, 64, BLOCKSIZE, BLOCKSIZE, BLOCKSIZE * i + OFFSETX, BLOCKSIZE * j + OFFSETY, 0);
                break;
                case 'K':
                    al_draw_bitmap_region(b.autotile, 16, 64, BLOCKSIZE, BLOCKSIZE, BLOCKSIZE * i + OFFSETX, BLOCKSIZE * j + OFFSETY, 0);
                break;
                case 'W':
                    al_draw_bitmap_region(b.autotile, 32, 64, BLOCKSIZE, BLOCKSIZE, BLOCKSIZE * i + OFFSETX, BLOCKSIZE * j + OFFSETY, 0);
                break;
                case 'X':
                    al_draw_bitmap_region(b.autotile, 48, 64, BLOCKSIZE, BLOCKSIZE, BLOCKSIZE * i + OFFSETX, BLOCKSIZE * j + OFFSETY, 0);
                break;
                case 'Y':
                    al_draw_bitmap_region(b.autotile, 32, 64, BLOCKSIZE, BLOCKSIZE, BLOCKSIZE * i + OFFSETX, BLOCKSIZE * j + OFFSETY, 1);
                break;
                case 'A':
                    al_draw_bitmap_region(b.autotile, 48, 64, BLOCKSIZE, BLOCKSIZE, BLOCKSIZE * i + OFFSETX, BLOCKSIZE * j + OFFSETY, 2);
                break;
                case 'T':
                    al_draw_bitmap_region(b.autotile, 0, 80, BLOCKSIZE, BLOCKSIZE, BLOCKSIZE * i + OFFSETX, BLOCKSIZE * j + OFFSETY, 0);
                break;
                case 'U':
                    al_draw_bitmap_region(b.autotile, 16, 80, BLOCKSIZE, BLOCKSIZE, BLOCKSIZE * i + OFFSETX, BLOCKSIZE * j + OFFSETY, 0);
                break;
                case 'V':
                    al_draw_bitmap_region(b.autotile, 32, 80, BLOCKSIZE, BLOCKSIZE, BLOCKSIZE * i + OFFSETX, BLOCKSIZE * j + OFFSETY, 0);
                break;
                case 'Z':
                    al_draw_bitmap_region(b.autotile, 48, 80, BLOCKSIZE, BLOCKSIZE, BLOCKSIZE * i + OFFSETX, BLOCKSIZE * j + OFFSETY, 0);
                break;
            }
        }
    }
}


void move_pacman(PLAYER_t& pg, BITMAP_t b)
{
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

	if (pg.stato > 9)
		pg.stato = 1;

	if (pg.stato >3  && pg.stato <= 6)
		al_draw_bitmap_region(b.main_image, 6, pg.sourcey, 14, 14, pg.x, pg.y, 0);

	else if (pg.stato > 0 && pg.stato <= 3)
		al_draw_bitmap_region(b.main_image, 6 * 2 + 14, pg.sourcey, 14, 14, pg.x, pg.y, 0);
	else if (pg.stato > 6 && pg.stato <= 9)
		al_draw_bitmap_region(b.main_image, 6 * 3 + 14 * 2, 6, 14, 14, pg.x, pg.y, 0);

	al_flip_display();
}
