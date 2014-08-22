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
#include <allegro5/allegro_font.h>

#include "data_struct.h"
#include "gui.h"
#include "io.h"

using namespace std;

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

void draw_path(BITMAP_t b, const MAPPA_t &m)
{
    for (int j = 0; j < m.r; j++){
        for (int i=0; i < m.c; i++){
            switch (m.mappa[i][j]){
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


bool move_pacman(PLAYER_t& pg, BITMAP_t b, bool active)
{
	switch (pg.dir)
	{
	   case FERMO:
		pg.dir = FERMO;
	   break;
	   case SU:
		pg.dir = SU;
		pg.y -= pg.movespeed;
	   break;
	   case GIU:
		pg.dir = GIU;
		pg.y += pg.movespeed;
	   break;
	   case SX:
		pg.dir = SX;
		pg.x -= pg.movespeed;
	   break;
	   case DX:
		pg.dir = DX;
		pg.x += pg.movespeed;
	   break;
	}
	if(active)
		pg.sourcex += al_get_bitmap_width(b.main_image)/3;
	else
		pg.sourcex = 21;
	if(pg.sourcex >= al_get_bitmap_width(b.main_image))
		pg.sourcex = 0;
	pg.sourcey = pg.dir;
	return true;
}

void draw_pacman(PLAYER_t& pg, BITMAP_t b)
{
	al_draw_bitmap_region(b.main_image, pg.sourcex, pg.sourcey * al_get_bitmap_height(b.main_image)/4, 16, 15, pg.x, pg.y, NULL);
}
