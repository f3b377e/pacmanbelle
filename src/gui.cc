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

void draw_screen_menu(const int menu, FONT_t f, BITMAP_t b)
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

void draw_pause(FONT_t f)
{
    al_draw_text(f.h2, al_map_rgb(255,255,255), SCREENWIDTH / 2, SCREENHEIGHT *50/100, ALLEGRO_ALIGN_CENTER, "gAME pAUSE");
	al_flip_display();
}

void draw_countdown(FONT_t &f, BITMAP_t &b,const MAPPA_t &m)
{
    al_clear_to_color(al_map_rgb(0,0,0));
    draw_path(b,m);
    al_draw_text(f.h5, al_map_rgb(255,255,255), SCREENWIDTH / 2, SCREENHEIGHT *50/100, ALLEGRO_ALIGN_CENTER, "TRE");
    al_flip_display();
    al_rest(1.4);
    
    al_clear_to_color(al_map_rgb(0,0,0));
    draw_path(b,m);
    al_draw_text(f.h5, al_map_rgb(255,255,255), SCREENWIDTH / 2, SCREENHEIGHT *50/100, ALLEGRO_ALIGN_CENTER, "DUE");
    al_flip_display();
    al_rest(1.4);
    
    al_clear_to_color(al_map_rgb(0,0,0));
    draw_path(b,m);
    al_draw_text(f.h5, al_map_rgb(255,255,255), SCREENWIDTH / 2, SCREENHEIGHT *50/100, ALLEGRO_ALIGN_CENTER, "UNO");
    al_flip_display();
    al_rest(1.4);
}


void draw_path(BITMAP_t b, const MAPPA_t &m)
{
    for (int j = 0; j < m.r; j++){
        for (int i= 0; i < m.c; i++){
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

/**Funzione che controlla lo spostamento del pacman e gli fa mangiare i pallini*/
static bool controllo_percorso(MAPPA_t m, PLAYER_t &pg, AUDIO_t audio)
{
	int mapx;
	int mapy;
	static bool p_eaten = false; //uso questa variabile per controllare se usare pallet_eaten1 o pallet_eaten2

	if (pg.x < OFFSETX + BLOCKSIZE - 14 && pg.dir == SX)
        	pg.x = 27 * BLOCKSIZE + OFFSETX + BLOCKSIZE;

	switch (pg.dir){
        case FERMO:
        break;
		case GIU:
			mapx = (pg.x - OFFSETX)/BLOCKSIZE;
			mapy = (pg.y + BLOCKSIZE - OFFSETY)/BLOCKSIZE;
            cout<<"\n ("<<pg.x<<","<<pg.y<<") ";
			cout<<"\n ["<<mapx<<","<<mapy<<"] = "<<m.mappa[mapx][mapy];
			if(m.mappa[mapx][mapy]!='P'
			   && m.mappa[mapx][mapy]!='0'
			   && m.mappa[mapx][mapy]!='Q'
               && collision(pg, pg.x, pg.y, 17, 16, mapx * BLOCKSIZE + OFFSETX, mapy * BLOCKSIZE + OFFSETY, BLOCKSIZE, BLOCKSIZE))
				return false;
		break;
		case SU:
			mapx = (pg.x - OFFSETX)/BLOCKSIZE;
			mapy = (pg.y - BLOCKSIZE - OFFSETY)/BLOCKSIZE;
			cout<<"\n ("<<pg.x<<","<<pg.y<<") ";
			cout<<"\n ["<<mapx<<","<<mapy<<"] = "<<m.mappa[mapx][mapy];
            if(m.mappa[mapx][mapy]!='P'
			   && m.mappa[mapx][mapy]!='0'
			   && m.mappa[mapx][mapy]!='Q'
               && collision(pg, pg.x, pg.y, 17, 16, mapx * BLOCKSIZE + OFFSETX, mapy * BLOCKSIZE + OFFSETY, BLOCKSIZE, BLOCKSIZE))
				return false;
		break;
		case SX:
			mapx = (pg.x - BLOCKSIZE - OFFSETX)/BLOCKSIZE;
			mapy = (pg.y - OFFSETY)/BLOCKSIZE;
			cout<<"\n ("<<pg.x<<","<<pg.y<<") ";
			cout<<"\n ["<<mapx<<","<<mapy<<"] = "<<m.mappa[mapx][mapy];
			if(m.mappa[mapx][mapy]!='P'
			   && m.mappa[mapx][mapy]!='0'
			   && m.mappa[mapx][mapy]!='Q'
               && collision(pg, pg.x, pg.y, 17, 16, mapx * BLOCKSIZE + OFFSETX, mapy * BLOCKSIZE + OFFSETY, BLOCKSIZE, BLOCKSIZE))
				return false;
		break;
		case DX:
			mapx = (pg.x + BLOCKSIZE - OFFSETX)/BLOCKSIZE;
			mapy = (pg.y - OFFSETY)/BLOCKSIZE;
			cout<<"\n ("<<pg.x<<","<<pg.y<<") ";
			cout<<"\n ["<<mapx<<","<<mapy<<"] = "<<m.mappa[mapx][mapy];
			if(m.mappa[mapx][mapy]!='P'
			   && m.mappa[mapx][mapy]!='0'
			   && m.mappa[mapx][mapy]!='Q'
               && collision(pg, pg.x, pg.y, 17, 16, mapx * BLOCKSIZE + OFFSETX, mapy * BLOCKSIZE + OFFSETY, BLOCKSIZE, BLOCKSIZE))
				return false;
		break;
	}

	mapx = (pg.x - OFFSETX)/BLOCKSIZE;
	mapy = (pg.y - OFFSETY)/BLOCKSIZE;
	if(m.mappa[mapx][mapy] == 'P'
	   || m.mappa[mapx][mapy] == 'Q'){
		m.mappa[mapx][mapy] = '0';
        	scrivi_mappa_su_file(m, "data/map/mappatest.txt");
		if(!p_eaten){
			al_play_sample(audio.pallet_eaten1,1.0,0.0, 1, ALLEGRO_PLAYMODE_ONCE , 0);
			p_eaten = true;
		}
		else{
			al_play_sample(audio.pallet_eaten2,1.0,0.0, 1, ALLEGRO_PLAYMODE_ONCE , 0);
			p_eaten = false;
		}
	}
	return true;

}

void move_pacman(PLAYER_t& pg, BITMAP_t b, MAPPA_t m, AUDIO_t audio)
{
		switch (pg.dir)
	{
	   case FERMO:
	   break;
	   case SU:
		if(controllo_percorso(m,pg,audio)){
			pg.precdir = pg.dir;
            pg.y -= pg.movespeed;
		}
		else if(pg.dir == pg.precdir)
			pg.dir = FERMO;
		else
			pg.dir = pg.precdir;
	   break;
	   case GIU:
		if(controllo_percorso(m, pg, audio)){
			pg.precdir = pg.dir;
            pg.y += pg.movespeed;
		}
		else if(pg.dir == pg.precdir)
			pg.dir = FERMO;
		else
			pg.dir = pg.precdir;
	   break;
	   case SX:
		if(controllo_percorso(m,pg, audio)){
			pg.precdir = pg.dir;
            pg.x -= pg.movespeed;
		}
		else if(pg.dir == pg.precdir)
			pg.dir = FERMO;
		else
			pg.dir = pg.precdir;
	   break;
	   case DX:
		if(controllo_percorso(m,pg,audio)){
			pg.precdir = pg.dir;
            pg.x += pg.movespeed;
		}
		else if(pg.dir == pg.precdir)
			pg.dir = FERMO;
		else
			pg.dir = pg.precdir;
	   break;
	}
}


void draw_pacman(PLAYER_t& pg, BITMAP_t b)
{
    pg.sourcex += al_get_bitmap_width(b.pacman_image)/3;
	if(pg.sourcex >= al_get_bitmap_width(b.pacman_image))
		pg.sourcex = 0;

	pg.sourcey = pg.dir;
	if(pg.dir == FERMO){
		pg.sourcey = pg.precdir;
		pg.sourcex = 0;
}

	al_draw_bitmap_region(b.pacman_image, pg.sourcex, pg.sourcey * al_get_bitmap_height(b.pacman_image)/4, 17, 16, pg.x, pg.y, 0);
}
