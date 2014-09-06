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

static bool collision (const PLAYER_t &pg, const float sx, const float sy,
                const float sw, const float sh, const float dx,
                const float dy, const float dw, const float dh)
{
    switch (pg.dir){
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

static bool controllo_percorso(MAPPA_t m, PLAYER_t &pg, AUDIO_t audio)
{
	int mapx;
	int mapy;
	static bool p_eaten = false; //uso questa variabile per controllare se usare pallet_eaten1 o pallet_eaten2

	if (pg.x < OFFSETX + 1 && pg.dir == SX)
        pg.x = 28 * BLOCKSIZE + OFFSETX;

// Qui la funzione leggerebbe fuori dalla matrice 31 x 28
// Quindi ho aggiunto una colonna a tutti 0 non da file ma dall'algortmo nel file io.cc (31 x 29)
// in modo che il file rimanga una matrice 31 x 28 di conseguenza anche le proprietà della matrice rimangono invariate
// Ovvero m.r = 31, m.c = 28 (e non 29!)

    if (pg.x > 27 * BLOCKSIZE + OFFSETX && pg.dir == DX)
        pg.x = OFFSETX;

	switch (pg.dir){
        case FERMO:
        break;
		case GIU:
			mapx = (pg.x - OFFSETX)/BLOCKSIZE;
			mapy = (pg.y + BLOCKSIZE - OFFSETY)/BLOCKSIZE;
			if(m.mappa[mapy][mapx]!='P'
			   && m.mappa[mapy][mapx]!='0'
			   && m.mappa[mapy][mapx]!='Q'
               && collision(pg, pg.x, pg.y, 17, 16, mapx * BLOCKSIZE + OFFSETX, mapy * BLOCKSIZE + OFFSETY, BLOCKSIZE, BLOCKSIZE))
				return false;
		break;
		case SU:
			mapx = (pg.x - OFFSETX)/BLOCKSIZE;
			mapy = (pg.y - BLOCKSIZE - OFFSETY)/BLOCKSIZE;
            if(m.mappa[mapy][mapx]!='P'
			   && m.mappa[mapy][mapx]!='0'
			   && m.mappa[mapy][mapx]!='Q'
               && collision(pg, pg.x, pg.y, 17, 16, mapx * BLOCKSIZE + OFFSETX, mapy * BLOCKSIZE + OFFSETY, BLOCKSIZE, BLOCKSIZE))
				return false;
		break;
		case SX:
			mapx = (pg.x - BLOCKSIZE - OFFSETX)/BLOCKSIZE;
			mapy = (pg.y - OFFSETY)/BLOCKSIZE;
			if(m.mappa[mapy][mapx]!='P'
			   && m.mappa[mapy][mapx]!='0'
			   && m.mappa[mapy][mapx]!='Q'
               && collision(pg, pg.x, pg.y, 17, 16, mapx * BLOCKSIZE + OFFSETX, mapy * BLOCKSIZE + OFFSETY, BLOCKSIZE, BLOCKSIZE))
				return false;
		break;
		case DX:
			mapx = (pg.x + BLOCKSIZE - OFFSETX)/BLOCKSIZE;
			mapy = (pg.y - OFFSETY)/BLOCKSIZE;
			if(m.mappa[mapy][mapx]!='P'
			   && m.mappa[mapy][mapx]!='0'
			   && m.mappa[mapy][mapx]!='Q'
               && collision(pg, pg.x, pg.y, 17, 16, mapx * BLOCKSIZE + OFFSETX, mapy * BLOCKSIZE + OFFSETY, BLOCKSIZE, BLOCKSIZE))
				return false;
		break;
	}

	mapx = (pg.x - OFFSETX)/BLOCKSIZE;
	mapy = (pg.y - OFFSETY)/BLOCKSIZE;
	if(m.mappa[mapy][mapx] == 'P'
	   || m.mappa[mapy][mapx] == 'Q'){

		if(!p_eaten){
			al_play_sample(audio.pallet_eaten1,1.0,0.0, 1, ALLEGRO_PLAYMODE_ONCE , 0);
			p_eaten = true;
		}
		else{
			al_play_sample(audio.pallet_eaten2,1.0,0.0, 1, ALLEGRO_PLAYMODE_ONCE , 0);
			p_eaten = false;
		}
        if (m.mappa[mapy][mapx] == 'Q'){
            al_stop_sample(&audio.id);
            al_play_sample(audio.ghosts_scared,1.0,0.0, 1, ALLEGRO_PLAYMODE_LOOP , 0);
            //start_timer();
        }
        pg.punteggio += 10;
        m.mappa[mapy][mapx] = '0';

	}
	return true;
}

void move_pacman(PLAYER_t& pg, MAPPA_t &m, AUDIO_t &audio, bool tasto[])
{
	int mapx = (pg.x - OFFSETX)/BLOCKSIZE;
	int mapy = (pg.y - OFFSETY)/BLOCKSIZE;
    int check_x = mapx * BLOCKSIZE + OFFSETX;
    int check_y = mapy * BLOCKSIZE + OFFSETY;
    DIREZ temporanea;

    if(tasto[UP])
        pg.succdir = SU;

    else if(tasto[DOWN])
        pg.succdir = GIU;

    else if(tasto[LEFT])
        pg.succdir = SX;

    else if(tasto[RIGHT])
        pg.succdir= DX;

    if (pg.x == check_x && pg.y == check_y){
        temporanea = pg.dir;
        pg.dir = pg.succdir;
        if (controllo_percorso(m,pg,audio) == false)
            pg.dir = temporanea;
    }
    switch (pg.dir)
	{
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


/** Restituisce la direzione in cui deve andare il nemico per arrivare a pacman
  * pgx e pgy sono le coordinate di pacman sulla matrice
  * fx, fy sono le coordinate del fantasma sulla matrice
  * l'algoritmo per calcolare la distanza migliore utilizza una coda dove inserisce i nodi adiacenti.
  * inizialmente tutti i nodi sono posti a infinito
  * l'inserimento avviene in testa e l'estrazione in coda.
  * inizialmente viene inserito nella coda la sorgente con la posizione di pac-man con distanza 0
  * ogni volta che un nodo viene estratto dalla coda, viene aggiunta una unità alla distanza del nodo padre.
  */
static DIREZ bfs(const MAPPA_t &m, const FANTASMA_t &f, int fx, int fy, int pgx, int pgy)
{
    DIREZ dir;
    int matt[m.r][m.c];
    int i = 0;
    //inizializzo la mappa a infinito (-1)
    for (int j = 0; j < m.c +1; j++)
        for (int i=0; i < m.r; i++)
            matt[i][j +1] = -1;

    ELEM_t *testa = NULL;
    ELEM_t *coda = NULL;

    matt[pgy][pgx] = 0;
    inserisci(testa, coda, pgx, pgy);

    while (testa!= NULL){
        ELEM_t u = estrai(testa, coda);
            if ( matt[u.y -1][u.x] == -1 &&
               ( m.mappa[u.y -1][u.x]=='P'
			   || m.mappa[u.y -1][u.x]=='0'
			   || m.mappa[u.y -1][u.x]=='Q')){

                matt[u.y -1][u.x] = matt[u.y][u.x] +1;
                inserisci(testa, coda, u.x, u.y -1);
			   }

            if ( matt[u.y][u.x +1] == -1 &&
               ( m.mappa[u.y][u.x +1]=='P'
			   || m.mappa[u.y][u.x +1]=='0'
			   || m.mappa[u.y][u.x +1]=='Q')){

                matt[u.y][u.x +1] = matt[u.y][u.x] +1;
                inserisci(testa, coda, u.x +1, u.y);
			   }

            if ( matt[u.y +1][u.x] == -1 &&
               ( m.mappa[u.y +1][u.x]=='P'
			   || m.mappa[u.y +1][u.x]=='0'
			   || m.mappa[u.y +1][u.x]=='Q')){

                matt[u.y +1][u.x] = matt[u.y][u.x] +1;
                inserisci(testa, coda, u.x, u.y +1);
			   }

            if ( matt[u.y][u.x -1] == -1 &&
               ( m.mappa[u.y][u.x -1]=='P'
			   || m.mappa[u.y][u.x -1]=='0'
			   || m.mappa[u.y][u.x -1]=='Q')){

                matt[u.y][u.x -1] = matt[u.y][u.x] +1;
                inserisci(testa, coda, u.x -1, u.y);
			   }
    }
/*
    ofstream s("data/map/mah.txt");

    for (int i = 0; i < m.r; i++){
        s<<"\n";
        for (int j=0; j < m.c +1; j++){
            if (matt[i][j] < 10 && matt[i][j] >= 0)
                s<<"0"<<matt[i][j]<<" ";
            else
                s<<matt[i][j]<<" ";
        }
    }
    #ifdef DEBUG_MODE
    cout<<"\n File Done!";
	#endif
*/
    int minore = matt[fy][fx];
    dir = SX;

    //su
    if (matt[fy -1][fx] > -1 && matt[fy -1][fx] < minore){
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

void move_blinky(const MAPPA_t &m, const PLAYER_t &pg, FANTASMA_t &f)
{
    int fx = (f.x - OFFSETX) /BLOCKSIZE;
    int fy = (f.y - OFFSETY) /BLOCKSIZE;
    int px = (pg.x - OFFSETX) /BLOCKSIZE;
    int py = (pg.y - OFFSETY) /BLOCKSIZE;
    int check_x = fx * BLOCKSIZE + OFFSETX;
    int check_y = fy * BLOCKSIZE + OFFSETY;


    if(check_x == f.x && check_y == f.y)
        f.succdir = bfs(m, f, fx, fy, px, py);

    f.dir = f.succdir;

    switch (f.dir){
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


    switch (pg.dir){
        case FERMO:
            f.succdir = bfs(m, f, fx, fy, px, py);
        break;
	   case SU:
            f.succdir = bfs(m, f, fx, fy, px, (py+ BLOCKSIZE));
	   break;
	   case GIU:
            f.succdir = bfs(m, f, fx, fy, px, (py - BLOCKSIZE));
	   break;
	   case SX:
            f.succdir = bfs(m, f, fx, fy, (px - BLOCKSIZE), py);
	   break;
	   case DX:
            f.succdir = bfs(m, f, fx, fy, (px + BLOCKSIZE), py);
	   break;
	}

    if(check_x == f.x && check_y == f.y)
        f.dir = f.succdir;

    switch (f.dir)
	{
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
