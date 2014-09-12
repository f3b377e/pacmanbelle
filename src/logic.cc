/*
 * logic.cc
 *
 *      Author: Belle & Bruce
 */

//C++ header
#include <iostream>
#include <fstream>

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

/** Funzione di Collisione oggetti ritorna vero se pacman collide con l'oggetto */
static bool collision (const DIREZ &direzione, const float sx, const float sy,
                const float sw, const float sh, const float dx,
                const float dy, const float dw, const float dh)
{
    switch (direzione){
    case FERMO:
    break;
    case SX:
        if (sx <= dx + dw)
            return true;
    break;
    case DX:
        if (sx+sw >= dx)
            return true;
    break;
    case SU:
        if (sy <= dy+dh)
            return true;
    break;
    case GIU:
        if (sy+sh >= dy)
            return true;
    break;
    }
return false;
}

static bool controllo_percorso(const MAPPA_t &m, const DIREZ &direzione, int posx, int posy)
{
    switch (direzione){
        case FERMO:
            return false;
            break;
		case GIU:
			posy ++;
			if(posy >= m.r || posy < 0)
                return false;

			if(m.mappa[posy][posx]!='P'
			   && m.mappa[posy][posx]!='0'
			   && m.mappa[posy][posx]!='Q')
                return false;
		break;
		case SU:
		    posy --;
		    if(posy >= m.r || posy < 0)
                return false;

            if(m.mappa[posy][posx]!='P'
			   && m.mappa[posy][posx]!='0'
			   && m.mappa[posy][posx]!='Q')
				return false;
		break;
		case SX:
		    posx --;
            if(posx >= m.c+1 || posx < 0)
                return false;
			if(m.mappa[posy][posx]!='P'
			   && m.mappa[posy][posx]!='0'
			   && m.mappa[posy][posx]!='Q')
				return false;
		break;
		case DX:
		    posx ++;
            if(posx >= m.c+1 || posx < 0)
                return false;
			if(m.mappa[posy][posx]!='P'
			   && m.mappa[posy][posx]!='0'
			   && m.mappa[posy][posx]!='Q')
				return false;
		break;
    }
    return true;
}

static void pac_mangia(MAPPA_t &m, PLAYER_t &pg, AUDIO_t &audio)
{
	int mapx = (pg.x - OFFSETX)/BLOCKSIZE;
	int mapy = (pg.y - OFFSETY)/BLOCKSIZE;
    static bool p_eaten = false;


    if (m.mappa[mapy][mapx] == 'P')
        pg.punteggio += 10;
    if (m.mappa[mapy][mapx] == 'Q')
        pg.punteggio += 100;

    m.mappa[mapy][mapx] = '0';

    if(!p_eaten){
        al_play_sample(audio.pallet_eaten1,1.0,0.0, 1, ALLEGRO_PLAYMODE_ONCE , 0);
        p_eaten = true;
    }
    else{
        al_play_sample(audio.pallet_eaten2,1.0,0.0, 1, ALLEGRO_PLAYMODE_ONCE , 0);
        p_eaten = false;
    }
}


void move_pacman(PLAYER_t& pg, MAPPA_t &m, AUDIO_t &a, bool tasto[])
{
	int mapx = (pg.x - OFFSETX)/BLOCKSIZE;
	int mapy = (pg.y - OFFSETY)/BLOCKSIZE;
    int succx =  mapx * BLOCKSIZE + OFFSETX;
    int succy =  mapy * BLOCKSIZE + OFFSETY;
    float pgh = al_get_bitmap_height(pg.img)/4;
    float pgw = al_get_bitmap_width(pg.img)/3;

    if(tasto[UP])
        pg.succdir = SU;

    else if(tasto[DOWN])
        pg.succdir = GIU;

    else if(tasto[LEFT])
        pg.succdir = SX;

    else if(tasto[RIGHT])
        pg.succdir= DX;

    if (m.mappa[mapy][mapx] == 'P' || m.mappa[mapy][mapx] == 'Q')
        pac_mangia(m,pg,a);

    if (controllo_percorso(m,pg.succdir,mapx,mapy) && (succx == pg.x) && (succy == pg.y)){
        pg.dir = pg.succdir;
        pg.precdir = pg.dir;
    }

    switch (pg.dir){
        case SU:
            succy -= BLOCKSIZE;
            if ( controllo_percorso(m,pg.dir,mapx,mapy) || !collision(pg.dir, pg.x, pg.y, pgw, pgh, succx, succy, BLOCKSIZE, BLOCKSIZE))
                pg.y -= pg.movespeed;
            else
                pg.dir = FERMO;
        break;
        case GIU:
            succy += BLOCKSIZE;
            if ( controllo_percorso(m,pg.dir,mapx,mapy) || !collision(pg.dir, pg.x, pg.y, pgw, pgh,succx, succy, BLOCKSIZE, BLOCKSIZE))
                pg.y += pg.movespeed;
            else
                pg.dir = FERMO;
        break;
        case SX:
            succx -= BLOCKSIZE;
            if ( controllo_percorso(m,pg.dir,mapx,mapy) || !collision(pg.dir, pg.x, pg.y, pgw, pgh,succx, succy, BLOCKSIZE, BLOCKSIZE))
                pg.x -= pg.movespeed;
            else
                pg.dir = FERMO;
        break;
        case DX:
            succx += BLOCKSIZE;
            if ( controllo_percorso(m,pg.dir,mapx,mapy) || !collision(pg.dir, pg.x, pg.y, pgw, pgh,succx, succy, BLOCKSIZE, BLOCKSIZE))
                pg.x += pg.movespeed;
            else
                pg.dir = FERMO;
        break;
    }

    if (pg.x < OFFSETX + 1 && pg.dir == SX)
        pg.x = 28 * BLOCKSIZE + OFFSETX;

    if (pg.x > 27 * BLOCKSIZE + OFFSETX && pg.dir == DX)
        pg.x = OFFSETX;
}

/** inserisce in testa alla lista, la lista serve per la bfs */
static void inserisci(lista &testa, lista &coda, int x, int y){
    ELEM_t *temp = new ELEM_t;
    temp->x = x;
    temp->y = y;
    temp->succ = NULL;
    temp->prec = testa;

    if (testa != NULL) //lista nn vuota
        testa->succ = temp;
    if (coda == NULL)
        coda = temp;
    testa = temp;
}

/** estrae in coda alla lista, la lista serve per la bfs */
static ELEM_t estrai(lista &testa, lista &coda){

    ELEM_t temp;

    temp.x = coda->x;
    temp.y = coda->y;
    temp.prec = NULL;
    temp.succ = NULL;
    if (coda->succ == NULL){ //ultimo elemento in coda;
        coda = NULL;
        testa = NULL;
        delete [] coda;
    }else{
        ELEM_t *p = coda->succ;
        p->prec = NULL;
        delete [] coda;
        coda = p;
    }
    return temp;
}

void controlla_pos()
{



}

static DIREZ bfs(const MAPPA_t &m, const FANTASMA_t &f, int fx, int fy, int pgx, int pgy)
{
    DIREZ dir;
    int matt[m.r][m.c + 1];
    //inizializzo la mappa a infinito (-1)
    for (int j = 0; j < m.c +1; j++)
        for (int i=0; i < m.r; i++)
            matt[i][j] = -2;

    for (int j = 0; j < m.c; j++)
        for (int i=0; i < m.r; i++)
            if (m.mappa[i][j] == 'P' || m.mappa[i][j] == 'Q' || m.mappa[i][j] == '0')
                matt[i][j] = -1;

    if (pgy >= m.r)
        pgy = m.r -1;
    if (pgx >= m.c)
        pgx = m.c -1;
    if (pgy < 0)
        pgy = 0;
    if (pgx < 0)
        pgx = 0;

    switch(f.dir){
        case SU:
            matt[fy +1][fx] = -2;
            break;
        case DX:
            matt[fy][fx -1] = -2;
            break;
        case SX:
            matt[fy][fx +1] = -2;
            break;
        case GIU:
            matt[fy -1][fx] = -2;
            break;
        }

    if (matt[pgy][pgx] == -2){
        if (matt[pgy+1][pgx] == -2 &&
            matt[pgy-1][pgx] == -2 &&
            matt[pgy][pgx+1] == -2 &&
            matt[pgy][pgx-1] == -2 &&
            pgx != m.r && pgy != m.c
            && pgx != 0 && pgy != 0)
                matt[pgy-1][pgx] = -1;
        matt[pgy][pgx] = -1;
    }

    ELEM_t *testa = NULL;
    ELEM_t *coda = NULL;

    inserisci(testa, coda, pgx, pgy);

    while (testa!= NULL){
        ELEM_t u = estrai(testa, coda);

            if ( matt[u.y -1][u.x] == -1){
                matt[u.y -1][u.x] = matt[u.y][u.x] +1;
                inserisci(testa, coda, u.x, u.y -1);
			   }

            if ( matt[u.y][u.x +1] == -1){
                matt[u.y][u.x +1] = matt[u.y][u.x] +1;
                inserisci(testa, coda, u.x +1, u.y);
			   }

            if ( matt[u.y +1][u.x] == -1){
                matt[u.y +1][u.x] = matt[u.y][u.x] +1;
                inserisci(testa, coda, u.x, u.y +1);
			   }

            if ( matt[u.y][u.x -1] == -1){
                matt[u.y][u.x -1] = matt[u.y][u.x] +1;
                inserisci(testa, coda, u.x -1, u.y);
			   }
    }

    int minore = 10000;
    dir = SX;

    //su
    if (matt[fy -1][fx] > -1  && matt[fy -1][fx] < minore){
        minore = matt[fy -1][fx];
        dir = SU;
    }
    //dx
    if (matt[fy][fx +1] > -1 && matt[fy][fx +1] < minore){
        minore = matt[fy][fx +1];
        dir = DX;
    }
    //giu
    if (matt[fy +1][fx] > -1 &&  matt[fy +1][fx] < minore){
        minore = matt[fy +1][fx];
        dir = GIU;
    }
    //sx
    if (matt[fy][fx -1] > -1 && matt[fy][fx -1] < minore){
        minore = matt[fy][fx -1];
        dir = SX;
    }
    return dir;

}


static bool do_bfs(const MAPPA_t &m, FANTASMA_t &f){

int fx = (f.x - OFFSETX) /BLOCKSIZE;
int fy = (f.y - OFFSETY) /BLOCKSIZE;

    switch (f.dir){
    case FERMO:
        break;
    case SU:
        if (controllo_percorso(m,SU,fx,fy) && !controllo_percorso(m,DX,fx,fy) && !controllo_percorso(m,SX,fx,fy))
            return false;
        break;
    case GIU:
        if (controllo_percorso(m,GIU,fx,fy) && !controllo_percorso(m,DX,fx,fy) && !controllo_percorso(m,SX,fx,fy))
            return false;
        break;
    case SX:
        if (controllo_percorso(m,SX,fx,fy) && !controllo_percorso(m,SU,fx,fy) && !controllo_percorso(m,GIU,fx,fy))
            return false;
        break;
    case DX:
        if (controllo_percorso(m,DX,fx,fy) && !controllo_percorso(m,SU,fx,fy) && !controllo_percorso(m,GIU,fx,fy))
            return false;
        break;
    }
    return true;
}

void ondula(float &y){
    static bool d = true;
    if(y > 13 * BLOCKSIZE + OFFSETY && d == true){
        y--;
        if(y <= 13 * BLOCKSIZE + OFFSETY){
            d = false;
            y++;
        }
    }
    else if(y < 15 * BLOCKSIZE + OFFSETY && d == false){
        y++;
        if(y >= 15 * BLOCKSIZE + OFFSETY){
            d = true;
            y--;
        }
    }

}


void move_blinky(const MAPPA_t &m, const PLAYER_t &pg, FANTASMA_t &f)
{
    int fx = (f.x - OFFSETX) /BLOCKSIZE;
    int fy = (f.y - OFFSETY) /BLOCKSIZE;
    int px = (pg.x - OFFSETX) /BLOCKSIZE;
    int py = (pg.y - OFFSETY) /BLOCKSIZE;
    int check_x = fx * BLOCKSIZE + OFFSETX;
    int check_y = fy * BLOCKSIZE + OFFSETY;



    if(check_x == f.x && check_y == f.y){
        if (do_bfs(m,f))
            f.succdir = bfs(m, f, fx, fy, px, py);
        f.dir = f.succdir;
    }

    switch (f.dir){
        case FERMO:
        break;
	   case SU:
	        f.y -= f.movespeed;
	   break;
	   case GIU:
            f.y += f.movespeed;
	   break;
	   case SX:
            f.x -= f.movespeed;
	   break;
	   case DX:
            f.x += f.movespeed;
	   break;
	}
}

void move_pinky(const MAPPA_t &m, const PLAYER_t &pg, FANTASMA_t &f)
{
    int fx = (f.x - OFFSETX) /BLOCKSIZE;
    int fy = (f.y - OFFSETY) /BLOCKSIZE;
    int px = (pg.x - OFFSETX) /BLOCKSIZE;
    int py = (pg.y - OFFSETY) /BLOCKSIZE;
    int check_x = fx * BLOCKSIZE + OFFSETX;
    int check_y = fy * BLOCKSIZE + OFFSETY;


    if(check_x == f.x && check_y == f.y){
        if (do_bfs(m,f)){
            switch(pg.dir){
                case FERMO:{
                    switch(pg.precdir){
                        case SU:
                            f.succdir = bfs(m, f, fx, fy, px -4, py -4);
                            break;
                        case DX:
                            f.succdir = bfs(m, f, fx, fy, px +4, py);
                            break;
                        case SX:
                            f.succdir = bfs(m, f, fx, fy, px -4, py);
                            break;
                        case GIU:
                            f.succdir = bfs(m, f, fx, fy, px, py +4);
                            break;
                        }
                    }break;
                case SU:
                    f.succdir = bfs(m, f, fx, fy, px -4, py -4);
                    break;
                case DX:
                    f.succdir = bfs(m, f, fx, fy, px +4, py);
                    break;
                case SX:
                    f.succdir = bfs(m, f, fx, fy, px -4, py);
                    break;
                case GIU:
                    f.succdir = bfs(m, f, fx, fy, px, py +4);
                    break;
            }
        }
        f.dir = f.succdir;
    }

    switch (f.dir){
        case FERMO:
        break;
	   case SU:
	        f.y -= f.movespeed;
	   break;
	   case GIU:
            f.y += f.movespeed;
	   break;
	   case SX:
            f.x -= f.movespeed;
	   break;
	   case DX:
            f.x += f.movespeed;
	   break;
	}
}

bool collision_pacman(const PLAYER_t &p, const FANTASMA_t &f)
{
    float dist = 5;
    float px = p.x + dist;
    float py = p.y + dist;
    float fx = f.x + dist;
    float fy = f.y + dist;
    float ph = p.y + BLOCKSIZE -dist;
    float pw = p.x + BLOCKSIZE -dist;
    float fh = f.y + BLOCKSIZE -dist;
    float fw = f.x + BLOCKSIZE -dist;

    if (( fx>=px && fx<=pw || fw>=px && fw<=pw )
        &&
        ( fy>=py && fy<=ph || fh>=py && fh<=ph ))
       return true;
    else
        return false;
}

void death_pacman(PLAYER_t &pg, STATO_GIOCO &stato, bool &caricamappa)
{
    if (pg.vita >0){
        pg.vita--;
        stato = CARICA;
        caricamappa = false;
    }
    else{
        stato = GAME_OVER;
        caricamappa = true;
    }
}

bool victory(const MAPPA_t &m, STATO_GIOCO &stato, bool &caricamappa)
{
    for (int i=0; i<m.r; i++)
        for (int j=0; j<m.c; j++)
            if (m.mappa[i][j] == 'P' || m.mappa[i][j]  == 'Q')
                return false;
    stato = WIN;
    caricamappa = true;
    return true;
}
