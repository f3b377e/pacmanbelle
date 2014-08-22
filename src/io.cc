/*
 * io.cc
 *
 *      Author: Belle & Bruce
 */

//C++ header
#include <iostream>
#include <fstream>

//allgro header
#include <allegro5/allegro.h>

//header interni
#include "data_struct.h"
#include "logic.h"

//direttive
using namespace std;

/** Funzione che alloca la memoria necessaria al caricamento della mappa da file*/
void alloca_mappa(MAPPA_t &m)
{
    m.mappa = new char*[m.r];
    for(int i=0; i<m.r; i++)
        m.mappa[i] = new char[m.c];
}

/** Funzione che dealloca la matrice mappa in memoria*/
void dealloca_mappa(MAPPA_t &m)
{
    for(int i=0;i<m.r;i++)
    delete m.mappa[i];
    delete m.mappa;
    m.mappa = NULL;
}


/**Carica la mappa da file in Memoria*/
void load_map(MAPPA_t& m,const char filename[])
{
    ifstream f(filename);
    if (!f)
        cout<<"File Error!";

    if (m.mappa != NULL)
            dealloca_mappa(m);

    f>>m.r>>m.c;
    alloca_mappa(m);
    for (int j = 0; j < m.r; j++){
        for (int i=0; i < m.c; i++){
            f >> m.mappa[i][j];
        }
    }
    cout<<"\nMap Loaded!";
}
