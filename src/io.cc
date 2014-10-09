/*
 * io.cc
 *
 *      Author: Belle & Bruce
 */

//C++ header
#include <iostream>
#include <fstream>
#include <cstring>

//allgro header
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

//header interni
#include "data_struct.h"
#include "logic.h"
#include "gui.h"
#include "init.h"

//direttive
using namespace std;

void agg_tasti(ALLEGRO_EVENT &event, bool tasto[], bool setting)
{
    switch(event.keyboard.keycode)
	{
		case ALLEGRO_KEY_UP:
			tasto[UP] = setting;
			break;
		case ALLEGRO_KEY_DOWN:
			tasto[DOWN] = setting;
			break;
		case ALLEGRO_KEY_RIGHT:
			tasto[RIGHT] = setting;
			break;
		case ALLEGRO_KEY_LEFT:
			tasto[LEFT] = setting;
			break;
		case ALLEGRO_KEY_ENTER:
			tasto[ENTER] = setting;
			break;
		case ALLEGRO_KEY_D:
			tasto[D] = setting;
			break;
		case ALLEGRO_KEY_ESCAPE:
			tasto[ESCAPE] = setting;
            break;
        case ALLEGRO_KEY_SPACE:
            tasto[SPACE] = setting;
			break;
        case ALLEGRO_KEY_P:
            tasto[P] = setting;
			break;
        case ALLEGRO_KEY_S:
            tasto[S] = setting;
			break;
	}
}
/** Funzione che alloca la memoria necessaria al caricamento della mappa da file */
static void alloca_mappa(MAPPA_t &m)
{
    m.mappa = new char *[m.r];
    for(int i = 0; i<m.r; i++)
        m.mappa[i] = new char[m.c +1];
}

/** Funzione che dealloca la matrice mappa in memoria*/
static void dealloca_mappa(MAPPA_t &m)
{
    for(int i = 0; i < m.r; i++){
        delete [] m.mappa[i];
    }
    delete [] m.mappa;
    m.mappa = NULL;
}



void load_map(MAPPA_t& m, char fileliv[], int livello)
{
    //trovo il nome del file per la mappa del determinato livello
    strcpy(fileliv,"data/map/map");
    char buff[20];
    snprintf(buff, sizeof(buff), "%d", livello);
    strcat(fileliv,buff);
    strcat(fileliv,".txt");

    ifstream f(fileliv);

    if(!f)
        cout<<"file Error!";

    if(m.mappa != NULL)
        dealloca_mappa(m);

    f>>m.r>>m.c;

    alloca_mappa(m);

    for(int i = 0; i < m.r; i++){
        for(int j = 0; j <= m.c; j++){
            if(j == m.c)
                m.mappa[i][j] = 0;
            else
                f>>m.mappa[i][j];
        }
    }
}

int preleva_record(){
    int punt_sav;
    ifstream f(FILE_SAV);

    if(!f)
        cout<<"file Error!";
    f>>punt_sav;
    return punt_sav;
}

void salva_record(int new_record){
    ofstream f(FILE_SAV);
    f<<new_record;
}

static char* file_string()
{
    char buff[20];
    char buff2[20];
    int livello = 0;
    bool file_exist = true;
    while (file_exist){
        livello ++;
        strcpy(buff,"data/map/map");
        buff2[20] = snprintf(buff2, sizeof(buff2), "%d", livello);
        strcat(buff,buff2);
        strcat(buff,".txt");
        ifstream f(buff);
        if(f){
            file_exist = true;
            f.close();
        }else
            file_exist = false;
    }
    return buff;
}

static char conversione_char(int sourcex, int sourcey, bool sp1, bool sp2)
{
    if (sourcex == 0 && sourcey == 0)
        return 'B';
    else if (sourcex == 16 && sourcey == 0)
        return 'C';
    else if (sourcex == 32 && sourcey == 0)
        return '0';
    else if (sourcex == 48 && sourcey == 0)
        return 'D';
    else if (sourcex == 0 && sourcey == 16)
        return 'E';
    else if (sourcex == 16 && sourcey == 16)
        return 'F';
    else if (sourcex == 32 && sourcey == 16)
        return 'G';
    else if (sourcex == 48 && sourcey == 16)
        return 'H';
    else if (sourcex == 0 && sourcey == 32)
        return 'I';
    else if (sourcex == 16 && sourcey == 32)
        return 'L';
    else if (sourcex == 32 && sourcey == 32)
        return 'M';
    else if (sourcex == 48 && sourcey == 32)
        return 'N';
    else if (sourcex == 0 && sourcey == 48)
        return 'P';
    else if (sourcex == 16 && sourcey == 48)
        return 'Q';
    else if (sourcex == 32 && sourcey == 48)
        return 'R';
    else if (sourcex == 48 && sourcey == 48)
        return 'S';
    else if (sourcex == 0 && sourcey == 64)
        return 'J';
    else if (sourcex == 16 && sourcey == 64)
        return 'K';
    else if (sourcex == 32 && sourcey == 64)
        return 'W';
    else if (sourcex == 48 && sourcey == 64)
        return 'X';
    else if (sourcex == 0 && sourcey == 80)
        return 'T';
    else if (sourcex == 16 && sourcey == 80)
        return 'U';
    else if (sourcex == 32 && sourcey == 80)
        return 'V';
    else if (sourcex == 48 && sourcey == 80)
        return 'Z';

    if (sp1)
        return 'Y';
    if (sp2)
        return 'A';

}

void editor_map(const BITMAP_t &b, bool tasto[], STATO_GIOCO &stato_gioco, const FONT_t &f){
    static char map_file[20];
    int r = 31;
    int c = 28;
    static bool take_file_string = true;
    static bool alloca = true;
    static MAPPA_t m;
    if (alloca){
        init_mappa(m);
        m.c = c;
        m.r = r;
        alloca_mappa(m);
        for(int i = 0; i < m.r; i++){
            for(int j = 0; j <= m.c; j++){

                if(j == m.c)
                    m.mappa[i][j] = 0;
                else
                    m.mappa[i][j] = '0';

                if (i==12 && j==10)
                    m.mappa[i][j] = 'T';
                else if (i==12 && j==17)
                    m.mappa[i][j] = 'U';
                else if (i==12 && j==15)
                    m.mappa[i][j] = 'W';
                else if ((j==10 || j==17) && (i>=13 && i<=15))
                    m.mappa[i][j] = 'J';
                else if ((i==12 && j==11) || (i==12 && j==16) || (i==16 && (j>=11 && j<=16)))
                    m.mappa[i][j] = 'K';
                else if (i==12 && j==12)
                    m.mappa[i][j] = 'Y';
                else if (i==16 && j==10)
                    m.mappa[i][j] = 'Z';
                else if (i==16 && j==17)
                    m.mappa[i][j] = 'V';
                }
        }
        alloca = false;
    }

    float xi = OFFSETX;
    float yi = OFFSETY;
    float xf = c * BLOCKSIZE + OFFSETX;
    float yf = r * BLOCKSIZE + OFFSETY;
    static float x = OFFSETX;
    static float y = OFFSETY;
    static float sourcex = 0;
    static float sourcey = 0;
    static bool special1 = false;
    static bool special2 = false;
    int mapx = (x - OFFSETX)/BLOCKSIZE;
    int mapy = (y - OFFSETY)/BLOCKSIZE;


    if (tasto[LEFT]){
        x -=BLOCKSIZE;
        if(x < OFFSETX)
            x = (c-1)*BLOCKSIZE + OFFSETX;
        tasto[LEFT]=false;
    }
    if (tasto[UP]){
        y -=BLOCKSIZE;
        if(y < OFFSETY)
            y = (r-1)*BLOCKSIZE + OFFSETY;
        tasto[UP]=false;
    }
    if (tasto[DOWN]){
        y +=BLOCKSIZE;
        if(y >= (r*BLOCKSIZE + OFFSETY))
            y = OFFSETY;
        tasto[DOWN]=false;
    }
    if (tasto[RIGHT]){
        x +=BLOCKSIZE;
        if(x >= (c*BLOCKSIZE + OFFSETX))
            x = OFFSETX;
        tasto[RIGHT]=false;
    }
    if (tasto[S]){
        if (sourcex == 32 && sourcey == 64){
            special1 = !special1;
        }
        if (sourcex == 48 && sourcey == 64 ){
            special2 = !special2;
        }
        if (!special1 && !special2)
            sourcex += BLOCKSIZE;

        if (sourcex >= al_get_bitmap_width(b.autotile)){
            sourcex = 0;
            sourcey += BLOCKSIZE;
        }
        if (sourcey >= al_get_bitmap_height(b.autotile)){
            sourcey = 0;
        }
        tasto[S]=false;
    }
    if (tasto[P]){
        if (!special1 && !special2)
            sourcex -= BLOCKSIZE;

        if (sourcex < 0){
            sourcex = al_get_bitmap_width(b.autotile) - BLOCKSIZE;
            sourcey -= BLOCKSIZE;
        }
        if (sourcey < 0){
            sourcey = al_get_bitmap_height(b.autotile) - BLOCKSIZE;
        }
        if (sourcex == 32 && sourcey == 64){
            special1 = !special1;
        }
        if (sourcex == 48 && sourcey == 64 ){
            special2 = !special2;
        }
        tasto[P]=false;
    }
    if (tasto[SPACE]){
        if (take_file_string){
            strcpy(map_file,file_string());
            take_file_string = false;
        }
        ofstream f(map_file);
        f<<31<<" "<<28<<"\n";
        m.mappa[mapy][mapx] = conversione_char(sourcex, sourcey, special1, special2);
        for(int i = 0; i < m.r; i++){
            for(int j = 0; j <= m.c; j++){

                if (i==12 && j==10)
                    m.mappa[i][j] = 'T';
                else if (i==12 && j==17)
                    m.mappa[i][j] = 'U';
                else if (i==12 && j==15)
                    m.mappa[i][j] = 'W';
                else if ((j==10 || j==17) && (i>=13 && i<=15))
                    m.mappa[i][j] = 'J';
                else if ((i==12 && j==11) || (i==12 && j==16) || (i==16 && (j>=11 && j<=16)))
                    m.mappa[i][j] = 'K';
                else if (i==12 && j==12)
                    m.mappa[i][j] = 'Y';
                else if (i==16 && j==10)
                    m.mappa[i][j] = 'Z';
                else if (i==16 && j==17)
                    m.mappa[i][j] = 'V';

                if (m.mappa[i][j] == 'D')
                    f<<'O'<<" ";
                else
                    f<<m.mappa[i][j]<<" ";

                }
            f<<"\n";
        }

        f.close();
        tasto[SPACE] = false;
    }
    if (tasto[ENTER]){
        stato_gioco = MENU;
        tasto[ENTER] = false;
    }
   if (tasto[ESCAPE]){
        stato_gioco = MENU;
        tasto[ESCAPE] = false;
    }
    if(m.mappa != NULL)
        draw_path(b, m);

    if (special1)
        al_draw_bitmap_region(b.autotile, 32, 64, BLOCKSIZE, BLOCKSIZE, x, y, 1);
    else if (special2)
        al_draw_bitmap_region(b.autotile, 48, 64, BLOCKSIZE, BLOCKSIZE, x, y, 2);
    else
        al_draw_bitmap_region(b.autotile, sourcex, sourcey, BLOCKSIZE, BLOCKSIZE, x, y, 0);

    al_draw_rectangle(xi, yi, xf, yf, al_map_rgb(215,0,0), 0);
    for ( int i = 1; i < r; i++)
        al_draw_line(xi+1, yi  + i * BLOCKSIZE, xf-1, yi + i * BLOCKSIZE, al_map_rgb(73,72,72), 0);
    for ( int j = 1; j < c; j++)
        al_draw_line(xi + j * BLOCKSIZE, yi+1, xi  + j * BLOCKSIZE, yf-1, al_map_rgb(73,72,72), 0);


    float dx,dy;
    dx = SCREENWIDTH*0.5;
    dy = 5;
    al_draw_textf(f.h4, al_map_rgb(105,253,105), dx, dy, ALLEGRO_ALIGN_CENTER, "%s",map_file);
    dx = OFFSETX;
    dy = BLOCKSIZE * r + OFFSETY;
    al_draw_text(f.h4, al_map_rgb(105,253,105), dx, dy, ALLEGRO_ALIGN_LEFT,"s: pezzo successivo");
    dx = SCREENWIDTH*0.5;
    al_draw_text(f.h4, al_map_rgb(105,253,105), dx , dy, ALLEGRO_ALIGN_CENTER, "p: pezzo successivo");
    dx = BLOCKSIZE * c + OFFSETX;
    al_draw_text(f.h4, al_map_rgb(105,253,105), dx, dy, ALLEGRO_ALIGN_RIGHT, "spazio: piazza");
    dx = SCREENWIDTH*0.5;
    dy = BLOCKSIZE * (r+2) + OFFSETY;
    al_draw_text(f.h4, al_map_rgb(105,253,105), dx, dy, ALLEGRO_ALIGN_CENTER, "esc: salva e torna al menu");






}


