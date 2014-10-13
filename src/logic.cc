/*
 * logic.cc
 *
 *      Author: Belle & Bruce
 */

//C++ header
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <time.h>

//allegro header
#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_primitives.h>
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
#include "init.h"

using namespace std;

void anima_menu(int &menu, bool tasto[],STATO_GIOCO &stato_gioco, PLAYER_t &pg, AUDIO_t &a)
{
    if(tasto[DOWN]){
        al_play_sample(a.pallet_eaten1,1.0,0.0, 1, ALLEGRO_PLAYMODE_ONCE , 0);
        menu ++;
        if(menu > 3)
            menu = 3;
        tasto[DOWN] = false;
    }
   else if(tasto[UP]){
        al_play_sample(a.pallet_eaten1,1.0,0.0, 1, ALLEGRO_PLAYMODE_ONCE , 0);
        menu --;
        if(menu < 1)
            menu = 1;
        tasto[UP] = false;
    }
    if(tasto[ENTER]){
        al_play_sample(a.ghost_eaten,1.0,0.0, 1, ALLEGRO_PLAYMODE_ONCE , 0);
        tasto[ENTER] = false;
        switch (menu){
        case 1:
            init_pacman(pg);
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
			   && m.mappa[posy][posx]!='Q'
			   && m.mappa[posy][posx]!= 0)
                return false;
		break;
		case SU:
		    posy --;
		    if(posy >= m.r || posy < 0)
                return false;

            if(m.mappa[posy][posx]!='P'
			   && m.mappa[posy][posx]!='0'
			   && m.mappa[posy][posx]!='Q'
			   && m.mappa[posy][posx]!= 0)
				return false;
		break;
		case SX:
		    posx --;
            if(posx >= m.c+1 || posx < 0)
                return false;
			if(m.mappa[posy][posx]!='P'
			   && m.mappa[posy][posx]!='0'
			   && m.mappa[posy][posx]!='Q'
			   && m.mappa[posy][posx]!= 0)
				return false;
		break;
		case DX:
		    posx ++;
            if(posx >= m.c+1 || posx < 0)
                return false;
			if(m.mappa[posy][posx]!='P'
			   && m.mappa[posy][posx]!='0'
			   && m.mappa[posy][posx]!='Q'
			   && m.mappa[posy][posx]!= 0)
				return false;
		break;
    }
    return true;
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

    /*
     * ho aggiunto questa condizione per evitare rallentamenti nel cambio direzione
     * nel caso si voglia tornare indietro dalla direzione dove si sta
     */
    if((pg.succdir != SU || pg.dir != GIU)
        && (pg.succdir != GIU || pg.dir != SU)
        && (pg.succdir != SX || pg.dir != DX)
        && (pg.succdir != DX || pg.dir != SX))
    {
        if (controllo_percorso(m,pg.succdir,mapx,mapy) && (succx == pg.x) && (succy == pg.y)){ //controlla che la direzione dove si vuole andare sia il percorso
            pg.dir = pg.succdir;
            pg.precdir = pg.dir;
        }
    }
    else{
        pg.dir = pg.succdir;
        pg.precdir = pg.dir;
    }

    switch (pg.dir){
        case FERMO:
        break;
        case SU:
            succy -= BLOCKSIZE;
            if ( controllo_percorso(m,pg.dir,mapx,mapy) || !collision(pg.dir, pg.x, pg.y, pgw, pgh, succx, succy, BLOCKSIZE, BLOCKSIZE)){
                if(pg.y > succy+BLOCKSIZE && pg.y-pg.movespeed < succy+BLOCKSIZE) //controllo per poter utilizzare diverse velocità
                    pg.y = succy+BLOCKSIZE;
                else
                    pg.y -= pg.movespeed;
            }
            else
                pg.dir = FERMO;
        break;
        case GIU:
            succy += BLOCKSIZE;
            if ( controllo_percorso(m,pg.dir,mapx,mapy) || !collision(pg.dir, pg.x, pg.y, pgw, pgh,succx, succy, BLOCKSIZE, BLOCKSIZE)){
                if(pg.y < succy && pg.y+pg.movespeed > succy)
                    pg.y = succy;
                else
                    pg.y += pg.movespeed;
            }
            else
                pg.dir = FERMO;
        break;
        case SX:
            succx -= BLOCKSIZE;
            if ( controllo_percorso(m,pg.dir,mapx,mapy) || !collision(pg.dir, pg.x, pg.y, pgw, pgh,succx, succy, BLOCKSIZE, BLOCKSIZE)){
                if(pg.x > succx+BLOCKSIZE && pg.x-pg.movespeed < succx+BLOCKSIZE)
                    pg.x = succx+BLOCKSIZE;
                else
                    pg.x -= pg.movespeed;
            }
            else
                pg.dir = FERMO;
        break;
        case DX:
            succx += BLOCKSIZE;
            if ( controllo_percorso(m,pg.dir,mapx,mapy) || !collision(pg.dir, pg.x, pg.y, pgw, pgh,succx, succy, BLOCKSIZE, BLOCKSIZE)){
                if(pg.x < succx && pg.x+pg.movespeed > succx)
                    pg.x = succx;
                else
                    pg.x += pg.movespeed;
            }
            else
                pg.dir = FERMO;
        break;
    }

    if (pg.x < OFFSETX + 1 && pg.dir == SX)
        pg.x = 27 * BLOCKSIZE + OFFSETX;

    if (pg.x > 27 * BLOCKSIZE + OFFSETX && pg.dir == DX)
        pg.x = OFFSETX;

    assert(pg.x <= (m.c*BLOCKSIZE)+OFFSETX || pg.x >= OFFSETX || pg.y <= (m.r*BLOCKSIZE)+OFFSETY || pg.y <= OFFSETY);
}

void cambia_stato(FANTASMA_t &b, FANTASMA_t &p, FANTASMA_t &i, FANTASMA_t &c, PLAYER_t &pg)
{
    if(b.stato != FUGA || p.stato != FUGA || i.stato != FUGA || c.stato != FUGA ){
        if(b.stato != ONDULA && b.stato != MANGIATO && b.stato != FUGA){
            b.stato = FUGA;
            b.movespeed = b.movespeed - 1;
        }
        if(p.stato != ONDULA && p.stato != MANGIATO && p.stato != FUGA){
            p.stato = FUGA;
            p.movespeed = p.movespeed - 1;
        }
        if(i.stato != ONDULA && i.stato != MANGIATO && i.stato != FUGA){
            i.stato = FUGA;
            i.movespeed = i.movespeed - 1;
        }
        if(c.stato != ONDULA && c.stato != MANGIATO && c.stato != FUGA){
            c.stato = FUGA;
            c.movespeed = c.movespeed - 1;
        }
    }
    else{
        if(b.stato != ONDULA && b.stato != INSEGUIMENTO && b.stato != SPARPAGLIAMENTO && b.stato != MANGIATO){
            b.stato = INSEGUIMENTO;
            b.movespeed= b.movespeed + 1;
        }

        if(p.stato != ONDULA && p.stato != INSEGUIMENTO && p.stato != SPARPAGLIAMENTO && p.stato != MANGIATO){
            p.stato = INSEGUIMENTO;
            p.movespeed = p.movespeed + 1;
        }

        if(i.stato != ONDULA && i.stato != INSEGUIMENTO && i.stato != SPARPAGLIAMENTO && i.stato != MANGIATO){
            i.stato = INSEGUIMENTO;
            i.movespeed = i.movespeed + 1;
        }

        if(c.stato != ONDULA && c.stato != INSEGUIMENTO && c.stato != SPARPAGLIAMENTO && c.stato != MANGIATO){
            c.stato = INSEGUIMENTO;
            c.movespeed = c.movespeed + 1;
        }
    }
}

void pac_mangia(MAPPA_t &m, PLAYER_t &pg, AUDIO_t &audio, FANTASMA_t &b, FANTASMA_t &p, FANTASMA_t &i, FANTASMA_t &c,
                ALLEGRO_TIMER *t, int &fuga_count, int livello)
{
	int mapx = (pg.x - OFFSETX)/BLOCKSIZE;
	int mapy = (pg.y - OFFSETY)/BLOCKSIZE;
    static bool p_eaten = false;
    static int punt_fant = 200; //punteggio attribuito ai fantasmi

    if (m.mappa[mapy][mapx] == 'P'){
        if((pg.punteggio <= 10000 && pg.punteggio + 10 > 10000) ||
           (pg.punteggio <= 20000 && pg.punteggio + 10 > 20000) ||
           (pg.punteggio <= 40000 && pg.punteggio + 10 > 40000)){
            al_play_sample(audio.pacman_extrapac, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE,0);
            pg.vita++;
        }
        pg.punteggio += 10;
    }

    if (m.mappa[mapy][mapx] == 'Q'){
        if((pg.punteggio <= 10000 && pg.punteggio + 50 > 10000) ||
           (pg.punteggio <= 20000 && pg.punteggio + 50 > 20000) ||
           (pg.punteggio <= 40000 && pg.punteggio + 50 > 40000)){
            al_play_sample(audio.pacman_extrapac, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE,0);
            pg.vita++;
        }
        pg.punteggio += 50;
        al_stop_sample(&audio.id);
        al_play_sample(audio.ghosts_scared, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP,&audio.id);
        fuga_count = al_get_timer_count(t)+11-livello;

        //controlli per i fantasmi per camgiarli di stato
        if(b.stato != ONDULA && b.stato != MANGIATO && b.stato != FUGA){
            b.stato = FUGA;
            b.movespeed = b.movespeed - 1;
        }
        if(p.stato != ONDULA && p.stato != MANGIATO && p.stato != FUGA){
            p.stato = FUGA;
            p.movespeed = p.movespeed - 1;
        }
        if(i.stato != ONDULA && i.stato != MANGIATO && i.stato != FUGA){
            i.stato = FUGA;
            i.movespeed = i.movespeed - 1;
        }
        if(c.stato != ONDULA && c.stato != MANGIATO && c.stato != FUGA){
            c.stato = FUGA;
            c.movespeed = c.movespeed - 1;
        }
    }

    if (m.mappa[mapy][mapx] == 'P' || m.mappa[mapy][mapx] == 'Q'){
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

    if(b.stato != FUGA && p.stato != FUGA && i.stato != FUGA && c.stato != FUGA)
        punt_fant = 200;

    if(collision_pacman(pg, b) && b.stato == FUGA){
        b.stato = MANGIATO;
        al_play_sample(audio.ghost_eaten,1.0,0.0, 1, ALLEGRO_PLAYMODE_ONCE , 0);
        if((pg.punteggio <= 10000 && pg.punteggio + punt_fant > 10000) ||
           (pg.punteggio <= 20000 && pg.punteggio + punt_fant > 20000) ||
           (pg.punteggio <= 40000 && pg.punteggio + punt_fant > 40000)){
            al_play_sample(audio.pacman_extrapac, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE,0);
            pg.vita++;
        }
        pg.punteggio += punt_fant;
        punt_fant += 200;
    }
    if(collision_pacman(pg, p) && p.stato == FUGA){
        p.stato = MANGIATO;
        al_play_sample(audio.ghost_eaten,1.0,0.0, 1, ALLEGRO_PLAYMODE_ONCE , 0);
        if((pg.punteggio <= 10000 && pg.punteggio + punt_fant > 10000) ||
           (pg.punteggio <= 20000 && pg.punteggio + punt_fant > 20000) ||
           (pg.punteggio <= 40000 && pg.punteggio + punt_fant > 40000)){
            al_play_sample(audio.pacman_extrapac, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE,0);
            pg.vita++;
        }
        pg.punteggio += punt_fant;
        punt_fant += 200;
    }
    if(collision_pacman(pg, i) && i.stato == FUGA){
        i.stato = MANGIATO;
        al_play_sample(audio.ghost_eaten,1.0,0.0, 1, ALLEGRO_PLAYMODE_ONCE , 0);
        if((pg.punteggio <= 10000 && pg.punteggio + punt_fant > 10000) ||
           (pg.punteggio <= 20000 && pg.punteggio + punt_fant > 20000) ||
           (pg.punteggio <= 40000 && pg.punteggio + punt_fant > 40000)){
            al_play_sample(audio.pacman_extrapac, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE,0);
            pg.vita++;
        }
        pg.punteggio += punt_fant;
        punt_fant += 200;
    }
    if(collision_pacman(pg, c) && c.stato == FUGA){
        c.stato = MANGIATO;
        al_play_sample(audio.ghost_eaten,1.0,0.0, 1, ALLEGRO_PLAYMODE_ONCE , 0);
        if((pg.punteggio <= 10000 && pg.punteggio + punt_fant > 10000) ||
           (pg.punteggio <= 20000 && pg.punteggio + punt_fant > 20000) ||
           (pg.punteggio <= 40000 && pg.punteggio + punt_fant > 40000)){
            al_play_sample(audio.pacman_extrapac, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE,0);
            pg.vita++;
        }
        pg.punteggio += punt_fant;
        punt_fant += 200;
    }

}

/** estrae in coda alla lista, la lista serve per la bfs */
static ELEM_t estrai(lista &testa)
{
    if(testa == NULL)
        return *testa;

    ELEM_t tmp;
    tmp.x = testa->x;
    tmp.y = testa->y;
    tmp.succ = NULL;

    ELEM_t *temp;
    temp = testa;
    testa = testa->succ;
    delete[] temp;

    return tmp;
}

/** inserisce in coda alla lista, la lista serve per la bfs */
static void inserisci(lista &testa, int x, int y)
{
    ELEM_t *temp = new ELEM_t;
    temp->x = x;
    temp->y = y;
    temp->succ = NULL;

    if(testa == NULL){ //lista nonvuota
        testa = temp;
        return;
    }
    ELEM_t * punt = testa;
    while(punt->succ != NULL){
        punt = punt->succ;
    }
    punt->succ = temp;
}

static DIREZ bfs(const MAPPA_t &m, const FANTASMA_t &f, int fx, int fy, int pgx, int pgy)
{
    DIREZ dir;
    int matt[m.r][m.c];

    if(pgy >= m.r-1){
        pgy = m.r - 2;
    }
    if(pgx >= m.c-1){
        pgx = m.c - 2;
    }
    if(pgy <= 0){
        pgy = 1;
    }
    if(pgx <= 0){
        pgx = 1;
    }

    assert(pgx <= m.c || pgx >= 0 || pgy <= m.r || pgy >= 0);

    //inizializzo la mappa a infinito (-1)
    for(int j = 0; j < m.c; j++){
        for(int i=0; i< m.r; i++){
            if(m.mappa[i][j] == 'P' || m.mappa[i][j] == 'Q' || m.mappa[i][j] == '0')
                matt[i][j] = -1;
            else
                matt[i][j] = -2;
        }
    }

    switch(f.dir){
        case FERMO:
        break;
        case SU:
            matt[fy + 1][fx] = -2;
            break;
        case DX:
            matt[fy][fx - 1] = -2;
            break;
        case SX:
            matt[fy][fx + 1] = -2;
            break;
        case GIU:
            matt[fy - 1][fx] = -2;
            break;
    }

    if(matt[pgy][pgx] == -2 &&
       matt[pgy+1][pgx] == -2 &&
       matt[pgy-1][pgx] == -2 &&
       matt[pgy][pgx+1] == -2 &&
       matt[pgy][pgx-1] == -2)
    {
        if(pgx < 13){
            pgx = pgx + 2;
        }
        if(pgx > 13){
            pgx = pgx - 2;
        }
    }


    ELEM_t *testa = NULL;

    inserisci(testa, pgx, pgy);

    while (testa != NULL){
        ELEM_t u = estrai(testa);

        if(matt[u.y - 1][u.x] == -1){
            matt[u.y - 1][u.x] = matt[u.y][u.x] + 1;
            inserisci(testa, u.x, u.y - 1);
        }
        if(matt[u.y][u.x + 1] == -1){
            matt[u.y][u.x + 1] = matt[u.y][u.x] + 1;
            inserisci(testa, u.x + 1, u.y);
        }
        if(matt[u.y + 1][u.x] == -1){
            matt[u.y + 1][u.x] = matt[u.y][u.x] + 1;
            inserisci(testa, u.x, u.y + 1);
        }
        if(matt[u.y][u.x - 1] == -1){
            matt[u.y][u.x - 1] = matt[u.y][u.x] + 1;
            inserisci(testa, u.x - 1, u.y);
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
    if(matt[fy][fx + 1] > -1 && matt[fy][fx + 1] < minore){
        minore = matt[fy][fx + 1];
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

//Questa funzione fa in modo che la bfs venga eseguita in prossimità di un incrocio
static bool do_bfs(const MAPPA_t &m, FANTASMA_t &f)
{
    int fx = (f.x - OFFSETX) / BLOCKSIZE; //coordinata x della casella nella quale risiede il fantasma
    int fy = (f.y - OFFSETY) / BLOCKSIZE; //coordinata y della casella nella quale risiede il fantasma

    switch(f.dir){
        case FERMO:
        break;
        case SU:
            if (controllo_percorso(m,SU,fx,fy) && !controllo_percorso(m,DX,fx,fy) && !controllo_percorso(m,SX,fx,fy))
                return false;
        break;
        case GIU:
            if(controllo_percorso(m,GIU,fx,fy) && !controllo_percorso(m,DX,fx,fy) && !controllo_percorso(m,SX,fx,fy))
                return false;
        break;
        case SX:
            if(controllo_percorso(m, SX, fx, fy) && !controllo_percorso(m,SU,fx,fy) && !controllo_percorso(m, GIU,fx,fy))
                return false;
        break;
        case DX:
            if(controllo_percorso(m,DX, fx, fy) && !controllo_percorso(m, SU,fx, fy) && !controllo_percorso(m, GIU,fx,fy))
                return false;
        break;
    }
    return true;
}

void ondula(const MAPPA_t &m, FANTASMA_t &f)
{
    int fy = (f.y - OFFSETY) / BLOCKSIZE; //coordinata y della casella nella quale risiede il fantasma

    switch(f.dir){
        case FERMO:
        break;
        case SU:
            if (fy <= 12)
                f.dir = GIU;
            else
                f.y -= f.movespeed;

        break;
        case GIU:
            if(fy >= 15)
                f.dir = SU;
            else
                f.y += f.movespeed;
        break;
        case SX:
        break;
        case DX:
        break;
    }
}

static void direziona_fantasma(FANTASMA_t &f, int check_x, int check_y){
    switch (f.dir){
        case FERMO:
        break;
        case SU:
            check_y -= BLOCKSIZE;
            if(f.y > check_y+BLOCKSIZE && f.y-f.movespeed < check_y+BLOCKSIZE) //controllo per poter utilizzare diverse velocità
                f.y = check_y+BLOCKSIZE;
            else
                f.y -= f.movespeed;

        break;
        case GIU:
            check_y += BLOCKSIZE;
            if(f.y < check_y && f.y+f.movespeed > check_y)
                f.y = check_y;
            else
                f.y += f.movespeed;
        break;
        case SX:
            check_x -= BLOCKSIZE;
            if(f.x > check_x+BLOCKSIZE && f.x-f.movespeed < check_x+BLOCKSIZE)
                f.x = check_x+BLOCKSIZE;
            else
                f.x -= f.movespeed;
        break;
        case DX:
            check_x += BLOCKSIZE;
            if(f.x < check_x && f.x+f.movespeed > check_x)
                f.x = check_x;
            else
                f.x += f.movespeed;
        break;
    }
}

void move_blinky(const MAPPA_t &m, const PLAYER_t &pg, FANTASMA_t &f)
{
    int fx = (f.x - OFFSETX) / BLOCKSIZE; //coordinata x della casella nella quale risiede il fantasma
    int fy = (f.y - OFFSETY) / BLOCKSIZE; //coordinata y della casella nella quale risiede il fantasma
    int px = (pg.x - OFFSETX) / BLOCKSIZE; //coordinata x della casella nella quale risiede pacman
    int py = (pg.y - OFFSETY) / BLOCKSIZE; //coordinata y della casella nella quale risiede pacman
    int check_x = fx * BLOCKSIZE + OFFSETX; //serve per controllare se la x del fantasma si trova in perfetta corrispondenza con la x della casella in cui risiede
    int check_y = fy * BLOCKSIZE + OFFSETY; //serve per controllare se la y del fantasma si trova in perfetta corrispondenza con la y della casella in cui risiede
    int x = px;
    int y = py;

    if (f.stato == SPARPAGLIAMENTO){
        x = 26;
        y = 1;
    }
    else if(f.stato == INSEGUIMENTO){
        x = px;
        y = py;
    }
    else if(f.stato == FUGA){
        srand(time(NULL));
        x = rand() % (m.c-1)+1;
        y = rand() % (m.r-1)+1;
    }
    else if(f.stato == MANGIATO){
        x = 14;
        y = 14;
        if (fx >= 11 && fx <= 16 && fy >= 13 && fy <= 15){
            f.stato = INSEGUIMENTO;
            f.movespeed = f.movespeed+1;
        }
    }

    if(check_x == f.x && check_y == f.y){
        if(do_bfs(m,f)){
            f.succdir = bfs(m, f, fx, fy, x, y);
        }
        f.dir = f.succdir;
    }

    direziona_fantasma(f, check_x, check_y);

    if (f.x < OFFSETX + 1 && f.dir == SX)
        f.x = 27 * BLOCKSIZE + OFFSETX;

    if (f.x > 27 * BLOCKSIZE + OFFSETX && f.dir == DX){
        f.x = OFFSETX;
    }
    assert(f.x <= (m.c*BLOCKSIZE)+OFFSETX || f.x >= OFFSETX || f.y <= (m.r*BLOCKSIZE)+OFFSETY || f.y <= OFFSETY);
}

void move_pinky(const MAPPA_t &m, const PLAYER_t &pg, FANTASMA_t &f)
{
    int fx = (f.x - OFFSETX) / BLOCKSIZE; //coordinata x della casella nella quale risiede il fantasma
    int fy = (f.y - OFFSETY) / BLOCKSIZE; //coordinata y della casella nella quale risiede il fantasma
    int px = (pg.x - OFFSETX) / BLOCKSIZE; //coordinata x della casella nella quale risiede pacman
    int py = (pg.y - OFFSETY) / BLOCKSIZE; //coordinata y della casella nella quale risiede pacman
    int check_x = fx * BLOCKSIZE + OFFSETX; //serve per controllare se la x del fantasma si trova in perfetta corrispondenza con la x della casella in cui risiede
    int check_y = fy * BLOCKSIZE + OFFSETY; //serve per controllare se la y del fantasma si trova in perfetta corrispondenza con la y della casella in cui risiede
    int x = px; //coordinata x della casella alla quale punterà il fantasma
    int y = py; //coordinata y della casella alla quale punterà il fantasma

    if (f.stato == SPARPAGLIAMENTO){
        x = 1;
        y = 1;
    }
    else if(f.stato == INSEGUIMENTO){
        switch(pg.precdir){
            case FERMO:
            break;
            case SU:
                x = px - 4;
                y = py - 4;
            break;
            case GIU:
                y = py + 4;
            break;
            case DX:
                x = px + 4;
            break;
            case SX:
                x = px - 4;
            break;
        }
    }
    else if(f.stato == FUGA){
        srand(time(NULL));
        x = rand() % (m.c-1)+1;
        y = rand() % (m.r-1)+1;
    }
    else if(f.stato == MANGIATO){
        x = 14;
        y = 14;
        if (fx >= 11 && fx <= 16 && fy >= 13 && fy <= 15){
            f.stato = INSEGUIMENTO;
            f.movespeed = f.movespeed+1;
        }
    }


    if(check_x == f.x && check_y == f.y){
        if(do_bfs(m,f)){
            f.succdir = bfs(m, f, fx, fy, x, y);
        }
        f.dir = f.succdir;
    }

    direziona_fantasma(f, check_x, check_y);

    if (f.x < OFFSETX + 1 && f.dir == SX)
        f.x = 27 * BLOCKSIZE + OFFSETX;

    if (f.x > 27 * BLOCKSIZE + OFFSETX && f.dir == DX){
        f.x = OFFSETX;
    }
    assert(f.x <= (m.c*BLOCKSIZE)+OFFSETX || f.x >= OFFSETX || f.y <= (m.r*BLOCKSIZE)+OFFSETY || f.y <= OFFSETY);
}

void move_inky(const MAPPA_t &m, const PLAYER_t &pg, FANTASMA_t &f, FANTASMA_t &b)
{
    int fx = (f.x - OFFSETX) / BLOCKSIZE; //coordinata x della casella nella quale risiede il fantasma
    int fy = (f.y - OFFSETY) / BLOCKSIZE; //coordinata y della casella nella quale risiede il fantasma
    int bx = (b.x - OFFSETX) / BLOCKSIZE; //coordinata x della casella nella quale risiede blinky
    int by = (b.y - OFFSETY) / BLOCKSIZE; //coordinata y della casella nella quale risiede blinky
    int px = (pg.x - OFFSETX) / BLOCKSIZE; //coordinata x della casella nella quale risiede pacman
    int py = (pg.y - OFFSETY) / BLOCKSIZE; //coordinata y della casella nella quale risiede pacman
    int check_x = fx * BLOCKSIZE + OFFSETX; //serve per controllare se la x del fantasma si trova in perfetta corrispondenza con la x della casella in cui risiede
    int check_y = fy * BLOCKSIZE + OFFSETY; //serve per controllare se la y del fantasma si trova in perfetta corrispondenza con la y della casella in cui risiede
    int x = px; //coordinata x della casella alla quale punterà il fantasma
    int y = py; //coordinata y della casella alla quale punterà il fantasma

    if (f.stato == SPARPAGLIAMENTO){
        x = 26;
        y = 29;
    }
    else if(f.stato == INSEGUIMENTO){
        switch(pg.precdir){
            case FERMO:
            break;
            case SU:
               x = (((px-bx)*2)+bx);
               y = (((py-2-by)*2)+by);
            break;
            case GIU:
               x = (((px-bx)*2)+bx);
               y = (((py+2-by)*2)+by);
            break;
            case DX:
               x = (((px+2-bx)*2)+bx);
               y = (((py-by)*2)+by);
            break;
            case SX:
               x = (((px-2-bx)*2)+bx);
               y = (((py-by)*2)+by);
            break;
        }
    }
    else if(f.stato == FUGA){
        srand(time(NULL));
        x = rand() % (m.c-1)+1;
        y = rand() % (m.r-1)+1;
    }
    else if(f.stato == MANGIATO){
        x = 14;
        y = 14;
        if (fx >= 11 && fx <= 16 && fy >= 13 && fy <= 15){
            f.stato = INSEGUIMENTO;
            f.movespeed = f.movespeed+1;
        }
    }
    #ifdef DEBUG_MODE
        al_draw_filled_rectangle(x*BLOCKSIZE+OFFSETX,y*BLOCKSIZE+OFFSETY,x*BLOCKSIZE+OFFSETX+BLOCKSIZE,y*BLOCKSIZE+OFFSETY+BLOCKSIZE,al_map_rgb(255,0,0) );
        al_flip_display();
    #endif // DEBUG_MODE

    if(check_x == f.x && check_y == f.y){
        if(do_bfs(m,f)){
            f.succdir = bfs(m, f, fx, fy, x, y);
        }
        f.dir = f.succdir;
    }

    direziona_fantasma(f, check_x, check_y);

    if (f.x < OFFSETX + 1 && f.dir == SX)
        f.x = 27 * BLOCKSIZE + OFFSETX;

    if (f.x > 27 * BLOCKSIZE + OFFSETX && f.dir == DX){
        f.x = OFFSETX;
    }
    assert(f.x <= (m.c*BLOCKSIZE)+OFFSETX || f.x >= OFFSETX || f.y <= (m.r*BLOCKSIZE)+OFFSETY || f.y <= OFFSETY);
}

void move_clyde(const MAPPA_t &m, const PLAYER_t &pg, FANTASMA_t &f)
{
    int fx = (f.x - OFFSETX) / BLOCKSIZE; //coordinata x della casella nella quale risiede il fantasma
    int fy = (f.y - OFFSETY) / BLOCKSIZE; //coordinata y della casella nella quale risiede il fantasma
    int px = (pg.x - OFFSETX) / BLOCKSIZE; //coordinata x della casella nella quale risiede pacman
    int py = (pg.y - OFFSETY) / BLOCKSIZE; //coordinata y della casella nella quale risiede pacman
    int check_x = fx * BLOCKSIZE + OFFSETX; //serve per controllare se la x del fantasma si trova in perfetta corrispondenza con la x della casella in cui risiede
    int check_y = fy * BLOCKSIZE + OFFSETY; //serve per controllare se la y del fantasma si trova in perfetta corrispondenza con la y della casella in cui risiede
    int x; //coordinata x della casella alla quale punterà il fantasma
    int y; //coordinata y della casella alla quale punterà il fantasma

    if (f.stato == SPARPAGLIAMENTO){
        x = 1;
        y = 29;
    }
    else if(f.stato == INSEGUIMENTO){
        if(fx >= px - 8 && fx <= px + 8 && fy >= py - 8 && fy <= py + 8 )
        {
            x = 1;
            y = m.r-1;
        }
        else{
            x = px;
            y = py;
        }
    }
    else if(f.stato == FUGA){
        srand(time(NULL));
        x = rand() % (m.c-1)+1;
        y = rand() % (m.r-1)+1;
    }
    else if(f.stato == MANGIATO){
        x = 14;
        y = 14;
        if (fx >= 11 && fx <= 16 && fy >= 13 && fy <= 15){
            f.stato = INSEGUIMENTO;
            f.movespeed = f.movespeed+1;
        }
    }

    if(check_x == f.x && check_y == f.y){
        if(do_bfs(m,f)){
            f.succdir = bfs(m, f, fx, fy, x, y);
        }
        f.dir = f.succdir;
    }

    direziona_fantasma(f, check_x, check_y);

    if (f.x < OFFSETX + 1 && f.dir == SX)
        f.x = 27 * BLOCKSIZE + OFFSETX;

    if (f.x > 27 * BLOCKSIZE + OFFSETX && f.dir == DX){
        f.x = OFFSETX;
    }
    assert(f.x <= (m.c*BLOCKSIZE)+OFFSETX || f.x >= OFFSETX || f.y <= (m.r*BLOCKSIZE)+OFFSETY || f.y <= OFFSETY);
}

void controlla_fantasmi(PLAYER_t &pacman, FANTASMA_t &blinky, FANTASMA_t &inky,
                        FANTASMA_t &clyde, FANTASMA_t &pinky, MAPPA_t &mappa,
                        ALLEGRO_TIMER *timer2){

    if(blinky.stato != ONDULA){
        if(blinky.stato != FUGA && blinky.stato != MANGIATO){
            if((al_get_timer_count(timer2) >= 0 && al_get_timer_count(timer2) <= 7) ||
               (al_get_timer_count(timer2) >= 27 && al_get_timer_count(timer2) <= 34) ||
               (al_get_timer_count(timer2) >= 54 && al_get_timer_count(timer2) <= 59) ||
               (al_get_timer_count(timer2) >= 79 && al_get_timer_count(timer2) <= 84)){
                blinky.stato = SPARPAGLIAMENTO;
            }
            else{
                blinky.stato = INSEGUIMENTO;
            }
        }
        move_blinky(mappa, pacman, blinky);
    }
    else if(blinky.stato == ONDULA)
        ondula(mappa, blinky);

    if(pinky.stato != ONDULA){
        if(pinky.stato != FUGA && pinky.stato != MANGIATO){
            if((al_get_timer_count(timer2) >= 0 && al_get_timer_count(timer2) <= 7) ||
              (al_get_timer_count(timer2) >= 27 && al_get_timer_count(timer2) <= 34) ||
              (al_get_timer_count(timer2) >= 54 && al_get_timer_count(timer2) <= 59) ||
              (al_get_timer_count(timer2) >= 79 && al_get_timer_count(timer2) <= 84)){
                pinky.stato = SPARPAGLIAMENTO;
            }
            else{
                pinky.stato = INSEGUIMENTO;
            }
        }
        move_pinky(mappa, pacman, pinky);
    }
    else{
        ondula(mappa, pinky);
        if(al_get_timer_count(timer2) > 2){
            pinky.stato = INSEGUIMENTO;
        }
    }

    if(inky.stato != ONDULA){
        if(inky.stato != FUGA && inky.stato != MANGIATO){
            if((al_get_timer_count(timer2) >= 0 && al_get_timer_count(timer2) <= 7) ||
              (al_get_timer_count(timer2) >= 27 && al_get_timer_count(timer2) <= 34) ||
              (al_get_timer_count(timer2) >= 54 && al_get_timer_count(timer2) <= 59) ||
              (al_get_timer_count(timer2) >= 79 && al_get_timer_count(timer2) <= 84)){
                inky.stato = SPARPAGLIAMENTO;
            }
            else{
                inky.stato = INSEGUIMENTO;
            }
        }
        move_inky(mappa, pacman, inky, blinky);
    }
    else{
        ondula(mappa, inky);
        if(al_get_timer_count(timer2) > 8){
            inky.stato = INSEGUIMENTO;
        }
    }

    if(clyde.stato != ONDULA){
        if(clyde.stato != FUGA && clyde.stato != MANGIATO){
            if((al_get_timer_count(timer2) >= 0 && al_get_timer_count(timer2) <= 7) ||
              (al_get_timer_count(timer2) >= 27 && al_get_timer_count(timer2) <= 34) ||
              (al_get_timer_count(timer2) >= 54 && al_get_timer_count(timer2) <= 59) ||
              (al_get_timer_count(timer2) >= 79 && al_get_timer_count(timer2) <= 84)){
                clyde.stato = SPARPAGLIAMENTO;
            }
            else{
                clyde.stato = INSEGUIMENTO;
            }
        }
        move_clyde(mappa, pacman, clyde);
    }
    else{
        ondula(mappa, clyde);
        if(al_get_timer_count(timer2) > 12 && pacman.punteggio > 600){
            clyde.stato = INSEGUIMENTO;
        }
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

    if (((fx>=px && fx<=pw) || (fw>=px && fw<=pw))&&
        ( (fy>=py && fy<=ph) || (fh>=py && fh<=ph) ))
       return true;
    else
        return false;
}

void death_pacman(PLAYER_t &pg, STATO_GIOCO &stato, bool &caricamappa)
{
    if (pg.vita > 0){
        pg.vita--;
        stato = CARICA;
        caricamappa = false;
    }
    else{
        stato = GAME_OVER;
        caricamappa = true;
    }
    pg.dir = FERMO;
    pg.precdir = SX;
    pg.succdir = FERMO;
    pg.movespeed = 4;
    pg.sourcex = 0;
    pg.sourcey = 0;
    pg.x = 13*BLOCKSIZE+OFFSETX;
    pg.y = 23*BLOCKSIZE+OFFSETY;
    pg.mangiato = false;
}

bool victory(const MAPPA_t &m, STATO_GIOCO &stato, bool &caricamappa, int &livello, PLAYER_t &pg)
{
    for (int i=0; i<m.r; i++)
        for (int j=0; j<m.c; j++)
            if (m.mappa[i][j] == 'P' || m.mappa[i][j]  == 'Q')
                return false;

    livello++;
    if(livello <= 10){
        caricamappa = true;
        stato = CARICA;
        pg.dir = FERMO;
        pg.precdir = SX;
        pg.succdir = FERMO;
        pg.movespeed = 4;
        pg.sourcex = 0;
        pg.sourcey = 0;
        pg.x = 13*BLOCKSIZE+OFFSETX;
        pg.y = 23*BLOCKSIZE+OFFSETY;
        pg.mangiato = false;
    }
    else
        stato = WIN;
    assert(livello <= 10 || livello >= 1 );
    return true;
}
