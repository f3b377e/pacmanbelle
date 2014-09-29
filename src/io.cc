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

//header interni
#include "data_struct.h"
#include "logic.h"

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
        delete m.mappa[i];
    }
    delete m.mappa;
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

void scrivi_mappa_su_file(const MAPPA_t &m, const char filename[])
{
}


