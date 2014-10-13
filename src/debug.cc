
//C++ header
#include <iostream>
#include <fstream>

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
#include "debug.h"
#include "io.h"

using namespace std;

/**Funzione utilizzabile solo in fase di debug.
 * Eseguita solo nello stato ::PLAY nella funzione ::main, non appena si preme il tasto D.
 * In questa funzione è possibile controllare da terminale le informazioni di pacman, dei fantasmi e della mappa,
 * al momento dell'attivazione della debugconsole, la quale fermera' i timer di gioco per poi riattivarli appena si rientra in gioco.
 * Inoltre in questa modalità si può passare da un livello ad un altro per eventuali controlli.
 * @param timer: Frame del movimento delle animazioni.
 * @param timer2: Timer di gioco che controlla i secondi trascorsi dall'inizio della vita.
 * @param pacman: varibaile contenente i dati di pac-man di tipo PLAYER_T.
 * @param blinky: variabile di tipo FANTASMA_T contenente le informazioni di blinky.
 * @param pinky: variabile di tipo FANTASMA_T contenente le informazioni di pinky.
 * @param inky: variabile di tipo FANTASMA_T contenente le informazioni di inky.
 * @param clyde: variabile di tipo FANTASMA_T contenente le informazioni di clyde.
 * @param mappa: variabile contenente le informazioni riguardanti la mappa di gioco di tipo MAPPA_T.
 * @param audio: variabile di tipo struttura AUDIO_T contenente i suoni del gioco.
 * @param livello: livello corrente in gioco.
 * @param caricamappa: indica se è presente la mappa, true se è caricata in memoria.
 * @param stato: indica lo stato del gioco di tipo STATO_GIOCO.
 * @return void.
 */

void debug_console(ALLEGRO_TIMER *timer
                   , ALLEGRO_TIMER *timer2
                   , PLAYER_t &pacman
                   , FANTASMA_t &blinky
                   , FANTASMA_t &pinky
                   , FANTASMA_t &inky
                   , FANTASMA_t &clyde
                   , MAPPA_t &mappa
                   , AUDIO_t &audio
                   , int &livello
                   , bool &caricamappa
                   , STATO_GIOCO &stato_gioco){

    bool menu = true;
    int scelta;
    int mapx, mapy, liv;
    al_stop_timer(timer2);
	al_stop_timer(timer);
	cout<<"*******DEBUG_CONSOLE********"<<endl;

        while(menu) {
    		cout<<"\n MENU:";
    		cout<<"\n\t 1) Informazioni Pac-Man";
    		cout<<"\n\t 2) Informazioni mappa di gioco";
    		cout<<"\n\t 3) Informazioni fantasmi";
    		cout<<"\n\t 4) Salta al livello desiderato";
            cout<<"\n\t 6) torna al gioco";
    		cout<<"\n Scelta: ";
    		cin>>scelta;
    		switch(scelta) {
    		case 1:
                mapx = (pacman.x - OFFSETX)/BLOCKSIZE;
                mapy = (pacman.y - OFFSETY)/BLOCKSIZE;
        		cout<<"\n Pac-Man";
        		cout<<"\n\t x = "<<pacman.x;
        		cout<<"\n\t y = "<<pacman.y;
                cout<<"\n\t char casella: "<<mappa.mappa[mapx][mapy];
                cout<<"\n\t coordinata:("<<mapx<<","<<mapy<<")";
        		cout<<"\n\t velocità attuale "<<pacman.movespeed;
                cout<<"\n\t Direzione:   precedente:"<<pacman.precdir
                    <<"   attuale:"<<pacman.dir
                    <<"   successiva:"<<pacman.succdir;
                cout<<"\n\t Punteggio"<<pacman.punteggio;
                cout<<"\n\t Vita: "<<pacman.vita;

        	break;
    		case 2:
        		cout<<"\n Mappa \n";
       			for(int i = 0; i < mappa.r; i++)
                	{
                    		for(int j = 0; j < mappa.c; j++)
                    		{
                                if(mappa.mappa[i][j] != 0)
                                    cout<<mappa.mappa[i][j]<<" ";
                                else
                                    cout<<"null";
                    		}
                    		cout<<endl;
                	}
                cout<<endl;
                cout<<"\n righe mappa: "<<mappa.r;
                cout<<"\n colonne mappa: "<<mappa.c;
                cout<<endl;
        		break;
            case 3:{
                int s=0;
                do{
                    cout<<"\n Fantasmi: \n";
                    cout<<"\t 0) Esci"<<endl;
                    cout<<"\t 1) Blinky"<<endl;
                    cout<<"\t 2) Pinky"<<endl;
                    cout<<"\t 3) Inky"<<endl;
                    cout<<"\t 4) Clyde "<<endl;
                    cin>>s;
                    if (s==0)
                        s = (-1);
                    else if (s==1){
                        cout<<"\n Blinky: \n";
                        cout<<"\n\t x = "<<blinky.x;
                        cout<<"\n\t y = "<<blinky.y;
                        mapx = (blinky.x - OFFSETX)/BLOCKSIZE;
                        mapy = (blinky.y - OFFSETY)/BLOCKSIZE;
                        cout<<"\n\t char casella: "<<mappa.mappa[mapy][mapx];
                        cout<<"\n\t coordinata:("<<mapx<<","<<mapy<<")";
                        cout<<"\n\t velocità attuale "<<blinky.movespeed;
                        cout<<"\n\t Direzione: 0: GIU 1:SU 2:SX 3:DX 4:FERMO "<<"   attuale:"<<blinky.dir
                            <<"   successiva:"<<blinky.succdir
                            <<endl;
                    }
                    else if (s==2){
                        cout<<"\n Pinky: \n";
                        cout<<"\n\t x = "<<pinky.x;
                        cout<<"\n\t y = "<<pinky.y;
                        mapx = (pinky.x - OFFSETX)/BLOCKSIZE;
                        mapy = (pinky.y - OFFSETY)/BLOCKSIZE;
                        cout<<"\n\t char casella: "<<mappa.mappa[mapy][mapx];
                        cout<<"\n\t coordinata:("<<mapx<<","<<mapy<<")";
                        cout<<"\n\t velocità attuale "<<pinky.movespeed;
                        cout<<"\n\t Direzione: 0: GIU 1:SU 2:SX 3:DX 4:FERMO "<<"   attuale:"<<pinky.dir
                            <<"   successiva:"<<pinky.succdir
                            <<endl;
                    }
                    else if (s==3){
                        cout<<"\n Inky: \n";
                        cout<<"\n\t x = "<<inky.x;
                        cout<<"\n\t y = "<<inky.y;
                        mapx = (inky.x - OFFSETX)/BLOCKSIZE;
                        mapy = (inky.y - OFFSETY)/BLOCKSIZE;
                        cout<<"\n\t char casella: "<<mappa.mappa[mapy][mapx];
                        cout<<"\n\t coordinata:("<<mapx<<","<<mapy<<")";
                        cout<<"\n\t velocità attuale "<<inky.movespeed;
                        cout<<"\n\t Direzione: 0: GIU 1:SU 2:SX 3:DX 4:FERMO "<<"   attuale:"<<inky.dir
                            <<"   successiva:"<<inky.succdir
                            <<endl;
                    }
                    else if (s==4){
                        cout<<"\n Clyde: \n";
                        cout<<"\n\t x = "<<clyde.x;
                        cout<<"\n\t y = "<<clyde.y;
                        mapx = (clyde.x - OFFSETX)/BLOCKSIZE;
                        mapy = (clyde.y - OFFSETY)/BLOCKSIZE;
                        cout<<"\n\t char casella: "<<mappa.mappa[mapy][mapx];
                        cout<<"\n\t coordinata:("<<mapx<<","<<mapy<<")";
                        cout<<"\n\t velocità attuale "<<clyde.movespeed;
                        cout<<"\n\t Direzione: 0: GIU 1:SU 2:SX 3:DX 4:FERMO "<<"   attuale:"<<clyde.dir
                            <<"   successiva:"<<clyde.succdir
                            <<endl;
                    }
                }while (s>=0);
        		break;
    		}
    		case 4:
                cout<<"Livello: ";
                cin>>liv;
                if(liv < 0 || liv > 10)
                    cout<<"Livello inesistente!\n";
                else{
                    livello = liv;
                    stato_gioco = CARICA;
                    caricamappa = true;
                    menu = false;
                }
            break;
            case 6:
                menu = false;
                al_play_sample(audio.siren, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP,&audio.id);
                al_start_timer(timer);
                al_start_timer(timer2);
                break;
    		}
    }

}
