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
#define DEBUG_CONSOLE								    		                                            \
	al_stop_timer(timer);							 		                                                \
	cout<<"*******DEBUG_CONSOLE********"<<endl;	  			 		                                        \
	bool menu = true;                                               	    	                            \
        while(menu) {                                         		            	                        \
    		cout<<"\n>>MENU:\n";                                                	                        \
    		cout<<"\t1) Informazioni Pac-Man\n";                                	                        \
    		cout<<"\t2) Informazioni mappa\n";                                  	                        \
    		cout<<"\t3) Informazioni fantasmi\n";                               	                        \
    		cout<<"\t4) Salta al livello desiderato\n";                         	                        \
    		cout<<"\t5) torna al gioco\n";                                      	                        \
    		cout<<"Scelta: ";                                                   	                        \
    		int scelta; cin>>scelta;                                            	                        \
    		switch(scelta) {                                                    	                        \
    		case 1:{                                                             	                        \
                int mapx = (pacman.x - OFFSETX)/BLOCKSIZE;                                                  \
                int mapy = (pacman.y - OFFSETY)/BLOCKSIZE;                                                  \
        		cout<<"\nPac-Man:\n";                                                                       \
        		cout<<"\tx = "<<pacman.x<<endl;                                                             \
        		cout<<"\ty = "<<pacman.y<<endl;                                                             \
                cout<<"\tchar casella: "<<mappa.mappa[mapx][mapy]<<endl;                                    \
                cout<<"\tcoordinata:("<<mapx<<","<<mapy<<")"<<endl;                                         \
        		cout<<"\tvelocità attuale "<<pacman.movespeed<<endl;                                        \
        	break;}                                                                                         \
    		case 2:                         	                                                            \
        		cout<<"\nMappa:\n"; 		                                                                \
       			for(int i = 0; i < mappa.r; i++)		                                                    \
                	{                                                                                       \
                    		for(int j = 0; j < mappa.c; j++)                                                \
                    		{                                                                               \
                        		cout<<mappa.mappa[j][i]<<" ";                                               \
                                                                                            				\
                    		}                                                                       		\
                    		cout<<endl;                                                             		\
                	}                                                                           			\
                cout<<endl;	                                                                                \
                cout<<"righe mappa: "<<mappa.r<<endl;                                                       \
                cout<<"colonne mappa: "<<mappa.c<<endl;                                                     \
        		break;                                                                      		    	\
            case 3:                                                                             			\
        		cout<<"\nFantasmi:\n";                                                      			    \
       			cout<<"\t Blinky:"<<endl;			                                    		            \
       			\
       			cout<<"\t Pinky:"<<endl;			                                    		            \
       			cout<<"\t Inky:"<<endl;			                                    		                \
       			cout<<"\t Clyde: "<<endl;                                                                   \
\
        		break;                                                                      			    \
    		case 4:                                                                         			    \
        		cout<<"Codice livello";			                                            		        \
        		int scelta_liv;                                                                             \
        		cin >> scelta_liv;   	                                    		                        \
                if(scelta_liv > 0 && scelta_liv < 20 )                                                      \
                {                                                                                           \
                     livello = scelta_liv;                                                                  \
                }                                                                                           \
                else                                                                                        \
                {                                                                                           \
                    cout<<"Scelta errata!\n";                                                             \
                }                                                                                           \
       			break;                                                                                      \
            case 5:                                                                                         \
                menu = false;                                                                               \
                al_start_timer(timer);                                                                      \
                break;                                                                                      \
    		}                                                                               	            \
    }


