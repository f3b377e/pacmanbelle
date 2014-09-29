
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
#include "debug.h"

using namespace std;


void debug_console(ALLEGRO_TIMER *timer
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
                    <<"   attuale:"<<pacman.succdir
                    <<endl;

        	break;
    		case 2:
        		cout<<"\n Mappa \n";
       			for(int i = 0; i < mappa.r; i++)
                	{
                    		for(int j = 0; j <= mappa.c; j++)
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
            case 5:

                break;
            case 6:
                menu = false;
                al_play_sample(audio.siren, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP,&audio.id);
                al_start_timer(timer);
                break;
    		}
    }

}
