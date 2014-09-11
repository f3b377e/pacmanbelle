/*
 * gui.cc
 *
 *      Author: Belle & Bruce
 */

#include <stdio.h>
#include <iostream>
#include <fstream>
//#include <windows.h>

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
#include "logic.h"

using namespace std;

void anima_menu(int &menu, bool tasto[],STATO_GIOCO &stato_gioco)
{
    //static int tempo = 0;
    if(tasto[DOWN]){
        menu ++;
        if(menu > 3)
            menu = 3;
        tasto[DOWN] = false;
    }
   else if(tasto[UP]){
        menu --;
        if(menu < 1)
            menu = 1;
        tasto[UP] = false;
    }
    if(tasto[ENTER]){
        tasto[ENTER] = false;
        switch (menu){
        case 1:
           stato_gioco = CARICA;
        break;
        case 2:
            stato_gioco = CONTROLS;
        break;
        case 3:
            stato_gioco = HIGH_SCORE;
        break;
        }
    }
}

void draw_screen_menu(const int menu, const FONT_t &f, const BITMAP_t &b)
{
    al_clear_to_color(al_map_rgb(0,0,0));
    al_draw_text(f.h1, al_map_rgb(255,255,255), SCREENWIDTH / 2, SCREENHEIGHT *10/100, ALLEGRO_ALIGN_CENTER, "pACMAN gAME");
    al_draw_bitmap(b.header_image, SCREENWIDTH *21/100, SCREENHEIGHT *25/100, 0);
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
            al_draw_bitmap(b.puntino, SCREENWIDTH *34/100, SCREENHEIGHT *56/100, 0);
      break;
      case 2:
            al_draw_bitmap(b.puntino, SCREENWIDTH *65/100, SCREENHEIGHT *66/100, 0);
            al_draw_bitmap(b.puntino, SCREENWIDTH *34/100, SCREENHEIGHT *66/100, 0);
      break;
      case 3:
            al_draw_bitmap(b.puntino, SCREENWIDTH *65/100, SCREENHEIGHT *76/100, 0);
            al_draw_bitmap(b.puntino, SCREENWIDTH *34/100, SCREENHEIGHT *76/100, 0);
      break;
    }
    al_flip_display();
}

void draw_pause(const FONT_t &f)
{
    al_draw_text(f.h2, al_map_rgb(255,15,15), SCREENWIDTH / 2, SCREENHEIGHT *50/100, ALLEGRO_ALIGN_CENTER, "gAME pAUSE");
	al_flip_display();
}

void draw_countdown(const FONT_t &f, const BITMAP_t &b, const MAPPA_t &m)
{
    al_clear_to_color(al_map_rgb(0,0,0));
    draw_path(b,m);
    al_draw_text(f.h5, al_map_rgb(255,15,15), SCREENWIDTH / 2, SCREENHEIGHT *50/100, ALLEGRO_ALIGN_CENTER, "TRE");
    al_flip_display();
    al_rest(1.4);

    al_clear_to_color(al_map_rgb(0,0,0));
    draw_path(b,m);
    al_draw_text(f.h5, al_map_rgb(255,15,15), SCREENWIDTH / 2, SCREENHEIGHT *50/100, ALLEGRO_ALIGN_CENTER, "DUE");
    al_flip_display();
    al_rest(1.4);

    al_clear_to_color(al_map_rgb(0,0,0));
    draw_path(b,m);
    al_draw_text(f.h5, al_map_rgb(255,15,15), SCREENWIDTH / 2, SCREENHEIGHT *50/100, ALLEGRO_ALIGN_CENTER, "UNO");
    al_flip_display();
    al_rest(1.4);
}


void draw_path(const BITMAP_t &b, const MAPPA_t &m)
{

    for (int i=0; i < m.r; i++){
        for (int j = 0; j < m.c; j++){
            switch (m.mappa[i][j]){
                case '0':
                    al_draw_bitmap_region(b.autotile, 32, 0, BLOCKSIZE, BLOCKSIZE, BLOCKSIZE * j + OFFSETX, BLOCKSIZE * i + OFFSETY, 0);
                break;
                case 'B':
                    al_draw_bitmap_region(b.autotile, 0, 0, BLOCKSIZE, BLOCKSIZE, BLOCKSIZE * j + OFFSETX, BLOCKSIZE * i + OFFSETY, 0);
                break;
                case 'C':
                    al_draw_bitmap_region(b.autotile, 16, 0, BLOCKSIZE, BLOCKSIZE, BLOCKSIZE * j + OFFSETX, BLOCKSIZE * i + OFFSETY, 0);
                break;
                case 'D':
                    al_draw_bitmap_region(b.autotile, 48, 0, BLOCKSIZE, BLOCKSIZE, BLOCKSIZE * j + OFFSETX, BLOCKSIZE * i + OFFSETY, 0);
                break;
                case 'E':
                    al_draw_bitmap_region(b.autotile, 0, 16, BLOCKSIZE, BLOCKSIZE, BLOCKSIZE * j + OFFSETX, BLOCKSIZE * i + OFFSETY, 0);
                break;
                case 'F':
                    al_draw_bitmap_region(b.autotile, 16, 16, BLOCKSIZE, BLOCKSIZE, BLOCKSIZE * j + OFFSETX, BLOCKSIZE * i + OFFSETY, 0);
                break;
                case 'G':
                    al_draw_bitmap_region(b.autotile, 32, 16, BLOCKSIZE, BLOCKSIZE, BLOCKSIZE * j + OFFSETX, BLOCKSIZE * i + OFFSETY, 0);
                break;
                case 'H':
                    al_draw_bitmap_region(b.autotile, 48, 16, BLOCKSIZE, BLOCKSIZE, BLOCKSIZE * j + OFFSETX, BLOCKSIZE * i + OFFSETY, 0);
                break;
                case 'I':
                    al_draw_bitmap_region(b.autotile, 0, 32, BLOCKSIZE, BLOCKSIZE, BLOCKSIZE * j + OFFSETX, BLOCKSIZE * i + OFFSETY, 0);
                break;
                case 'L':
                    al_draw_bitmap_region(b.autotile, 16, 32, BLOCKSIZE, BLOCKSIZE, BLOCKSIZE * j + OFFSETX, BLOCKSIZE * i + OFFSETY, 0);
                break;
                case 'M':
                    al_draw_bitmap_region(b.autotile, 32, 32, BLOCKSIZE, BLOCKSIZE, BLOCKSIZE * j + OFFSETX, BLOCKSIZE * i + OFFSETY, 0);
                break;
                case 'N':
                    al_draw_bitmap_region(b.autotile, 48, 32, BLOCKSIZE, BLOCKSIZE, BLOCKSIZE * j + OFFSETX, BLOCKSIZE * i + OFFSETY, 0);
                break;
                case 'P':
                    al_draw_bitmap_region(b.autotile, 0, 48, BLOCKSIZE, BLOCKSIZE, BLOCKSIZE * j + OFFSETX, BLOCKSIZE * i + OFFSETY, 0);
                break;
                case 'Q':
                    al_draw_bitmap_region(b.autotile, 16, 48, BLOCKSIZE, BLOCKSIZE, BLOCKSIZE * j + OFFSETX, BLOCKSIZE * i + OFFSETY, 0);
                break;
                case 'R':
                    al_draw_bitmap_region(b.autotile, 32, 48, BLOCKSIZE, BLOCKSIZE, BLOCKSIZE * j + OFFSETX, BLOCKSIZE * i + OFFSETY, 0);
                break;
                case 'S':
                    al_draw_bitmap_region(b.autotile, 48, 48, BLOCKSIZE, BLOCKSIZE, BLOCKSIZE * j + OFFSETX, BLOCKSIZE * i + OFFSETY, 0);
                break;
                case 'J':
                    al_draw_bitmap_region(b.autotile, 0, 64, BLOCKSIZE, BLOCKSIZE, BLOCKSIZE * j + OFFSETX, BLOCKSIZE * i + OFFSETY, 0);
                break;
                case 'K':
                    al_draw_bitmap_region(b.autotile, 16, 64, BLOCKSIZE, BLOCKSIZE, BLOCKSIZE * j + OFFSETX, BLOCKSIZE * i + OFFSETY, 0);
                break;
                case 'W':
                    al_draw_bitmap_region(b.autotile, 32, 64, BLOCKSIZE, BLOCKSIZE, BLOCKSIZE * j + OFFSETX, BLOCKSIZE * i + OFFSETY, 0);
                break;
                case 'X':
                    al_draw_bitmap_region(b.autotile, 48, 64, BLOCKSIZE, BLOCKSIZE, BLOCKSIZE * j + OFFSETX, BLOCKSIZE * i + OFFSETY, 0);
                break;
                case 'Y':
                    al_draw_bitmap_region(b.autotile, 32, 64, BLOCKSIZE, BLOCKSIZE, BLOCKSIZE * j + OFFSETX, BLOCKSIZE * i + OFFSETY, 1);
                break;
                case 'A':
                    al_draw_bitmap_region(b.autotile, 48, 64, BLOCKSIZE, BLOCKSIZE, BLOCKSIZE * j + OFFSETX, BLOCKSIZE * i + OFFSETY, 2);
                break;
                case 'T':
                    al_draw_bitmap_region(b.autotile, 0, 80, BLOCKSIZE, BLOCKSIZE, BLOCKSIZE * j + OFFSETX, BLOCKSIZE * i + OFFSETY, 0);
                break;
                case 'U':
                    al_draw_bitmap_region(b.autotile, 16, 80, BLOCKSIZE, BLOCKSIZE, BLOCKSIZE * j + OFFSETX, BLOCKSIZE * i + OFFSETY, 0);
                break;
                case 'V':
                    al_draw_bitmap_region(b.autotile, 32, 80, BLOCKSIZE, BLOCKSIZE, BLOCKSIZE * j + OFFSETX, BLOCKSIZE * i + OFFSETY, 0);
                break;
                case 'Z':
                    al_draw_bitmap_region(b.autotile, 48, 80, BLOCKSIZE, BLOCKSIZE, BLOCKSIZE * j + OFFSETX, BLOCKSIZE * i + OFFSETY, 0);
                break;
            }
        }
    }
}

void draw_pacman(PLAYER_t& pg)
{
    pg.sourcex += al_get_bitmap_width(pg.img)/3;
	if(pg.sourcex >= al_get_bitmap_width(pg.img))
		pg.sourcex = 0;

	pg.sourcey = pg.dir;
	if(pg.dir == FERMO){
		pg.sourcey = pg.precdir;
		pg.sourcex = 0;
    }

	al_draw_bitmap_region(pg.img, pg.sourcex
                          , pg.sourcey * al_get_bitmap_height(pg.img)/4
                          , al_get_bitmap_width(pg.img)/3
                          , al_get_bitmap_height(pg.img)/4
                          , pg.x, pg.y, 0);
}

void draw_fantasma(FANTASMA_t& pg)
{
    pg.sourcex += al_get_bitmap_width(pg.img)/2;
	if(pg.sourcex >= al_get_bitmap_width(pg.img))
		pg.sourcex = 0;
    switch (pg.dir){
    case SU:
    	pg.sourcey = 0 * al_get_bitmap_height(pg.img)/4;
    break;
    case GIU:
    	pg.sourcey = 1 * al_get_bitmap_height(pg.img)/4;
    break;
    case DX:
    	pg.sourcey = 3 * al_get_bitmap_height(pg.img)/4;
    break;
    case SX:
    	pg.sourcey = 2 * al_get_bitmap_height(pg.img)/4;
    break;
    default:
    	pg.sourcey = 0 * al_get_bitmap_height(pg.img)/4;
    break;
    }

	al_draw_bitmap_region(pg.img, pg.sourcex, pg.sourcey, al_get_bitmap_width(pg.img)/2, al_get_bitmap_height(pg.img)/4, pg.x, pg.y, 0);
}



void draw_gameover(const FONT_t &f, const BITMAP_t &b)
{
    al_clear_to_color(al_map_rgb(0,0,0));
    al_draw_text(f.h1, al_map_rgb(255,15,15), SCREENWIDTH / 2, SCREENHEIGHT *50/100, ALLEGRO_ALIGN_CENTER, "**** g a m e  o v e r ****");
    al_flip_display();
}

void draw_win(const FONT_t &f, const BITMAP_t &b)
{
    al_clear_to_color(al_map_rgb(0,0,0));
    al_draw_text(f.h1, al_map_rgb(15,255,15), SCREENWIDTH / 2, SCREENHEIGHT *50/100, ALLEGRO_ALIGN_CENTER, "**** v i c t o r y ****");
    al_flip_display();
}
