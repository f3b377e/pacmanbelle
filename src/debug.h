/*
 * debug.h
 *
 *      Author: Belle & Bruce
 */

/**
 * Questo file contiene la debug console, un'interfaccia che viene usata solo in modalità
 * di debug che consente di ricevere in tempo reale le informazioni riguardanti il pacman
 * la mappa e i fantasmi, oltretutto si può scegliere a quale livello/mappa giocare.
 *
 * Per attivare questa modalità, bisogna compilare il progetto con il "make debug" e una volta in gioco
 * basta premere il tasto "d".
 */
#define DEBUG_CONSOLE								    		\
	al_stop_timer(timer);							 		\
	cout<<"*******DEBUG_CONSOLE********"<<endl;	  			 		\
	bool menu = true;                                               	    	        \
        while(menu) {                                         		            	        \
    		cout<<"\n>>MENU:\n";                                                	        \
    		cout<<"\t1) Informazioni Pac-Man\n";                                	        \
    		cout<<"\t2) Informazioni mappa\n";                                  	        \
    		cout<<"\t3) Informazioni fantasmi\n";                               	        \
    		cout<<"\t4) Salta al livello desiderato\n";                         	        \
    		cout<<"\t5) torna al gioco\n";                                      	        \
    		cout<<"Scelta: ";                                                   	        \
    		int scelta; cin>>scelta;                                            	        \
    		switch(scelta) {                                                    	        \
    		case 1:                                                             	        \
        		cout<<"\nPac-Man:\n";                                                   \
        		cout<<"\tx "<<pacman.x<<"\ty "<<pacman.y<<endl;                         \
        		cout<<"\tvelocità attuale "<<pacman.movespeed<<endl;                    \
        		break;                                                                  \
    		case 2:                         	                                        \
        		cout<<"\nMappa:\n"; 		                                        \
       			cout<<"\tda definire"<<endl;			                        \
        		break;                                                                  \
   		case 3:                                                                         \
        		cout<<"\nFantasmi:\n";                                                  \
       			cout<<"\tda definire"<<endl;			                        \
        		break;                                                                  \
    		case 4:                                                                         \
        		cout<<"Codice livello";			                                \
       			cout<<"\tda definire"<<endl;			                        \
        		break;                                                                  \
    		case 5:                                                                         \
        		menu = false;                                                           \
        		al_start_timer(timer);                                                  \
        		break;                                                                  \
    		}                                                                               \
    }

