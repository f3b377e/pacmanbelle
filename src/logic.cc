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
        cout<<"\n Bitmap Error, fantasma1.png error!";

    b.fantasma2 = al_load_bitmap("data/img/fantasma2.png");
	 if (b.fantasma2 == NULL)
        cout<<"\n Bitmap Error, fantasma2.png error!";

    b.fantasma3 = al_load_bitmap("data/img/fantasma3.png");
	 if (b.fantasma3 == NULL)
        cout<<"\n Bitmap Error, fantasma3.png error!";

    b.fantasma4 = al_load_bitmap("data/img/fantasma4.png");
	 if (b.fantasma4 == NULL)
        cout<<"\n Bitmap Error, fantasma4.png error!";

    b.frutta= al_load_bitmap("data/img/frutta.png");
	 if (b.frutta == NULL)
        cout<<"\n Bitmap Error, frutta.png error!";
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
	pacman.succdir = FERMO;
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
    b.dir = SU;
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


/**Funzione che controlla lo spostamento del pacman e gli fa mangiare i pallini*/
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
          //  cout<<"\n ("<<pg.y<<","<<pg.x<<") ";
		//	cout<<"\n ["<<mapy<<","<<mapx<<"] = "<<m.mappa[mapy][mapx];
			if(m.mappa[mapy][mapx]!='P'
			   && m.mappa[mapy][mapx]!='0'
			   && m.mappa[mapy][mapx]!='Q'
               && collision(pg, pg.x, pg.y, 17, 16, mapx * BLOCKSIZE + OFFSETX, mapy * BLOCKSIZE + OFFSETY, BLOCKSIZE, BLOCKSIZE))
				return false;
		break;
		case SU:
			mapx = (pg.x - OFFSETX)/BLOCKSIZE;
			mapy = (pg.y - BLOCKSIZE - OFFSETY)/BLOCKSIZE;
		//	cout<<"\n ("<<pg.y<<","<<pg.x<<") ";
		//	cout<<"\n ["<<mapy<<","<<mapx<<"] = "<<m.mappa[mapy][mapx];
            if(m.mappa[mapy][mapx]!='P'
			   && m.mappa[mapy][mapx]!='0'
			   && m.mappa[mapy][mapx]!='Q'
               && collision(pg, pg.x, pg.y, 17, 16, mapx * BLOCKSIZE + OFFSETX, mapy * BLOCKSIZE + OFFSETY, BLOCKSIZE, BLOCKSIZE))
				return false;
		break;
		case SX:
			mapx = (pg.x - BLOCKSIZE - OFFSETX)/BLOCKSIZE;
			mapy = (pg.y - OFFSETY)/BLOCKSIZE;
		//	cout<<"\n ("<<pg.y<<","<<pg.x<<") ";
		//	cout<<"\n ["<<mapy<<","<<mapx<<"] = "<<m.mappa[mapy][mapx];
			if(m.mappa[mapy][mapx]!='P'
			   && m.mappa[mapy][mapx]!='0'
			   && m.mappa[mapy][mapx]!='Q'
               && collision(pg, pg.x, pg.y, 17, 16, mapx * BLOCKSIZE + OFFSETX, mapy * BLOCKSIZE + OFFSETY, BLOCKSIZE, BLOCKSIZE))
				return false;
		break;
		case DX:
			mapx = (pg.x + BLOCKSIZE - OFFSETX)/BLOCKSIZE;
			mapy = (pg.y - OFFSETY)/BLOCKSIZE;
		//	cout<<"\n ("<<pg.y<<","<<pg.x<<") ";
		//	cout<<"\n ["<<mapy<<","<<mapx<<"] = "<<m.mappa[mapy][mapx];
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

void move_pacman(PLAYER_t& pg, MAPPA_t m, AUDIO_t audio)
{
	int mapx = (pg.x - OFFSETX)/BLOCKSIZE;
	int mapy = (pg.y - OFFSETY)/BLOCKSIZE;
    int check_x = mapx * BLOCKSIZE + OFFSETX;
    int check_y = mapy * BLOCKSIZE + OFFSETY;
    DIREZ temporanea;

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

    const char lol[] = "data/map/mah.txt";
    ofstream s(lol);

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

void move_bliky(const MAPPA_t &m, const PLAYER_t &pg, FANTASMA_t &f)
{
    int fx = (f.x - OFFSETX) /BLOCKSIZE;
    int fy = (f.y - OFFSETY) /BLOCKSIZE;
    int px = (pg.x - OFFSETX) /BLOCKSIZE;
    int py = (pg.y - OFFSETY) /BLOCKSIZE;
    int check_x = fx * BLOCKSIZE + OFFSETX;
    int check_y = fy * BLOCKSIZE + OFFSETY;

    f.succdir = bfs(m, f, fx, fy, px, py);

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

