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
static void alloca_mappa(MAPPA_t &m)
{
    m.mappa = new char*[m.c +1];
    for(int i=0; i<m.r; i++)
        m.mappa[i] = new char[m.c + 1];
}

/** Funzione che dealloca la matrice mappa in memoria*/
static void dealloca_mappa(MAPPA_t &m)
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
    for (int i = 0; i < m.r; i++){
        for (int j=0; j < m.c; j++){
            f >> m.mappa[i][j];
        }
    }
    for (int i = 0; i < m.r ; i++){ //colonna aggiuntiva a destra
        m.mappa[i][m.c] = '0';
    }
    cout<<"\nMap Loaded!";
}

void scrivi_mappa_su_file(const MAPPA_t &m, const char filename[])
{
    ofstream f(filename);

    if (m.mappa == NULL)
        cout<<"File Error (scrivi su file)!!";

    for (int i = 0; i < m.r; i++){
        f<<"\n";
        for (int j=0; j < m.c +1; j++){
            f << m.mappa[i][j]<<" ";
        }
    }
    cout<<"\n File Done!";

}
