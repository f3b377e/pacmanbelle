/*
 * logic.h
 *
 *      Author: Belle & Bruce
 */
#ifndef LOGIC_H_
#define LOGIC_H_

/**La funzione gestisce l'animazione del menu in base al tasto premuto.
 * Gestisce i tasti premuti da tastiera, se per esempio se si preme il tasto ::GIU la funzione
 * farà scendere di uno il puntatore del menu e incrementerà il valore intero di menu passato per riferimento
 * e verrà eseguito un suono in output.
 * Nel caso in cui si scelga lo stato gi gioco ::PLAY verrà inizializzato pacman attraverso ::init_pacman.
 *
 * Funzione richiamata nel ::main nello stato di gioco ::MENU.
 * @param menu: indica quale campo si sta selezionando
 * @param tasto: array contenente lo stato dei tasti premuti o rilasciati
 * @param stato_gioco: indica lo stato del gioco di tipo STATO_GIOCO
 * @param pg: varibaile contenente i dati di pac-man di tipo PLAYER_T
 * @param a: variabile di tipo struttura AUDIO_T contenente i suoni del gioco
 * @return void
 */
void anima_menu(int &menu, bool tasto[],STATO_GIOCO &stato_gioco, PLAYER_t &pg, AUDIO_t &a);

/** Funzione che si occupa del movimento di pacman.
 * Si occupa del movimento di pacman modificando i valori della x e y di pacman, utilizza
 * tre variabili per le direzioni: succdir, dir, precdir dello stract ::PLAYER_T per avere
 * un controllo completo della direzione e posizione di pacman.
 *
 * Richiama le funzioni: ::controllo_percorso e ::collision
 * @param pg: varibaile contenente i dati di pac-man di tipo PLAYER_T
 * @param a: variabile di tipo struttura AUDIO_T contenente i suoni del gioco.
 * @param tasto: array contenente lo stato dei tasti premuti o rilasciati
 * @param m: variabile contenente le informazioni riguardanti la mappa di gioco di tipo MAPPA_T
 * @return void
*/
void move_pacman(PLAYER_t& pg, MAPPA_t &m, AUDIO_t &a, bool tasto[]);

/** Gestisce il metodo e da la possibilità a pacman di mangiare pallini piccoli, grandi e fantasmi.
 * Gestisce tutti gli effetti che provoca quando pacman mangia:
 * gestione dell'immagine dei pallini che devono scomparire quando vengono mangiati, riproduzione dell'audio quando mangia i pallini,
 * riproduzione dell'audio e dell'immagine quando pacman mangia un fantasma, incremento del punteggio.
 *
 * Richiama le funzioni: ::collision_pacman
 * @param m: variabile contenente le informazioni riguardanti la mappa di gioco di tipo MAPPA_T
 * @param pg: varibaile contenente i dati di pac-man di tipo PLAYER_T
 * @param a: variabile di tipo struttura AUDIO_T contenente i suoni del gioco.
 * @param b: variabile di tipo FANTASMA_T contenente le informazioni di blinky
 * @param p: variabile di tipo FANTASMA_T contenente le informazioni di pinky
 * @param i: variabile di tipo FANTASMA_T contenente le informazioni di inky
 * @param c: variabile di tipo FANTASMA_T contenente le informazioni di clyde
 * @param t: timer di gioco che controlla i secondi trascorsi dall'inizio della vita
 * @param fuga_count: contatore che gestisce la fine della modalità di fuga dei fantasmi
 * @param livello: livello corrente in gioco
 * @return void
 */
void pac_mangia(MAPPA_t &m, PLAYER_t &pg, AUDIO_t &audio, FANTASMA_t &b, FANTASMA_t &p, FANTASMA_t &i, FANTASMA_t &c,
                ALLEGRO_TIMER *t, int &fuga_count, int livello);

/**Serve per cambiare lo stato dei fantasmi in modalità spavento.
 * o quando pacman mangia il pallino grande o quando il tempo scade
 * @param b: variabile di tipo FANTASMA_T contenente le informazioni di blinky
 * @param p: variabile di tipo FANTASMA_T contenente le informazioni di pinky
 * @param i: variabile di tipo FANTASMA_T contenente le informazioni di inky
 * @param c: variabile di tipo FANTASMA_T contenente le informazioni di clyde
 * @param pg: varibaile contenente i dati di pac-man di tipo PLAYER_T
 * @return void
 */
void cambia_stato(FANTASMA_t &b, FANTASMA_t &p, FANTASMA_t &i, FANTASMA_t &c, PLAYER_t &pg);

/**Gestisce il movimento ondulatorio dei fantasmi all'inizio del gioco
 * i fantasmi in questo modo ondeggiano avanti e indietro nella loro base fino alla loro uscita.
 * Questa funzione viene invocata solo quando lo stato del fantasma è in modalità ::ONDULA
 * il tempo di uscita dei fantasmi è impostato in ::controlla_fantasmi
 *
 * @param m: variabile contenente le informazioni riguardanti la mappa di gioco di tipo MAPPA_T
 * @param f: variabile contenente le informazioni del fantasma
 * @return void
 */
void ondula(const MAPPA_t &m, FANTASMA_t &f);

/** Gestisce il Movimento di Blinky.
 * Il fantasmino rosso, Blinky, ha il compito di inseguire pacman.
 * Blinky è il primo a uscire dal box e l'unico che non ottiene lo stato di ondeggiamento.
 *
 * Quando è nello stato ::INSEGUIMENTO punta sempre a pacman prendendo la stada più veloce possibile.
 *
 * Quando il suo stato è in modalità ::SPARPAGLIAMENTO punta alla base, la casella in alto a destra.
 *
 * Quando è nello stato ::FUGA il suo movimento è "puramente" casuale.
 *
 * Richiama le funzioni: ::direziona_fantasma , ::do_bfs , ::bfs
 * @param m: variabile contenente le informazioni riguardanti la mappa di gioco di tipo MAPPA_T
 * @param pg: varibaile contenente i dati di pac-man di tipo PLAYER_T
 * @param f: variabile contenente le informazioni del fantasma
 * @return void
 */
void move_blinky(const MAPPA_t &m, const PLAYER_t &pg, FANTASMA_t &f);

/** Gestisce il Movimento di Pinky
 * Il fantasmino rosa, Pinky, ha il compito di intercettare pacman e prevenire le sue mosse.
 * Pinky è il secondo a uscire dal box.
 *
 * Quando è nello stato ::INSEGUIMENTO punta sempre alla posizione di pacman incrementata di 4 casella nella in cui sta andando pacman.
 * Esempio se pacman sta andando a destra punta 4 caselle più a destra rispetto pacman,
 * l'unica eccezzione è quando pacman è diretto verso l'alto dello schermo che punta 4 caselle più in altro e 4 caselle più a sinistra
 *
 * Quando il suo stato è in modalità ::SPARPAGLIAMENTO punta alla base, la casella in alto a sinistra.
 *
 * Quando è nello stato ::FUGA il suo movimento è "puramente" casuale.
 *
 * Richiama le funzioni: ::direziona_fantasma , ::do_bfs , ::bfs
 * @param m: variabile contenente le informazioni riguardanti la mappa di gioco di tipo MAPPA_T
 * @param pg: varibaile contenente i dati di pac-man di tipo PLAYER_T
 * @param f: variabile contenente le informazioni del fantasma
 * @return void
 */
void move_pinky(const MAPPA_t &m, const PLAYER_t &pg, FANTASMA_t &f);

/** Gestisce il Movimento di Inky
 * Il fantasmino Blu, Inky, è l'unione di Blinky e Pinky.
 * Inky è il Terzo a uscire dal box.
 *
 * Quando è nello stato ::INSEGUIMENTO la casella puntata dal fantasma inky
 * è data dalla differenza tra le x,y di pacman + 2 in base al verso di pacman stesso
 * e di blinky moltiplicate per due e sommate con le coordinate di blinky
 *
 * Quando il suo stato è in modalità ::SPARPAGLIAMENTO punta alla base, la casella in basso a destra.
 *
 * Quando è nello stato ::FUGA il suo movimento è "puramente" casuale.
 *
 * Richiama le funzioni: ::direziona_fantasma , ::do_bfs , ::bfs
 * @param m: variabile contenente le informazioni riguardanti la mappa di gioco di tipo MAPPA_T
 * @param pg: varibaile contenente i dati di pac-man di tipo PLAYER_T
 * @param f: variabile contenente le informazioni del fantasma
 * @return void
 */
void move_inky(const MAPPA_t &m, const PLAYER_t &pg, FANTASMA_t &f, FANTASMA_t &b);

/** Gestisce il Movimento di Clyde
 * Il fantasmino Arancione, Clyde, è lo scansafatiche di turno.
 * Clyde, infatti, è l'ultimo ad uscire dal box.
 *
 * Quando è nello stato ::INSEGUIMENTO clyde insegue pacman quando è fuori dall'area di pacman (8x8 caselle)
 * altrimenti punta alla sua base
 *
 * Quando il suo stato è in modalità ::SPARPAGLIAMENTO punta alla base, la casella in basso a sinistra.
 *
 * Quando è nello stato ::FUGA il suo movimento è "puramente" casuale.
 *
 * Richiama le funzioni: ::direziona_fantasma , ::do_bfs , ::bfs
 * @param m: variabile contenente le informazioni riguardanti la mappa di gioco di tipo MAPPA_T
 * @param pg: varibaile contenente i dati di pac-man di tipo PLAYER_T
 * @param f: variabile contenente le informazioni del fantasma
 * @return void
 */
void move_clyde(const MAPPA_t &m, const PLAYER_t &pg, FANTASMA_t &f);

/** Genstisce la collisione tra pacman e un fantasma.
 * @param p: varibaile contenente i dati di pac-man di tipo PLAYER_T
 * @param f: variabile contenente le informazioni del fantasma
 * @return vero se pacaman collide con un fantasma, falso se non collide
 */
bool collision_pacman(const PLAYER_t &p, const FANTASMA_t &f);

/** Gestisce la morte di pacman.
 * @param m: variabile contenente le informazioni riguardanti la mappa di gioco di tipo MAPPA_T
 * @param stato: indica lo stato del gioco di tipo STATO_GIOCO
 * @param caricamappa: indica se e' presente la mappa, true se e' caricata in memoria
 * @return void
 */
void death_pacman(PLAYER_t &pg, STATO_GIOCO &stato, bool &caricamappa);

/** Controlla la vittoria del giocatore.
 * incrementa il livello fino al decimo e nel caso in cui sia al decimo assegna lo stato ::WIN
 * @param m: variabile contenente le informazioni riguardanti la mappa di gioco di tipo MAPPA_T
 * @param stato: indica lo stato del gioco di tipo STATO_GIOCO
 * @param caricamappa: indica se e' presente la mappa, true se e' caricata in memoria
 * @param livello: livello corrente in gioco
 * @return vero se si è raggiunta la vittoria, falso altrimenti
 */
bool victory(const MAPPA_t &m, STATO_GIOCO &stato, bool &caricamappa, int &livello, PLAYER_t &pg);

/** Controlla la logica dei fantasmi
 * Decide in base al timer2 la modalità dei fantasmi definite nel ::STATO_FANT tra ::INSEGUIMENTO , ::ONDULA , ::SPARPAGLIAMENTO
 *
 * richiama le funzioni: ::move_blinky , ::move_pinky , ::move_inky , ::move_clyde , ::ondula
 * @param pacman: varibaile contenente i dati di pac-man di tipo PLAYER_T
 * @param blinky: variabile di tipo FANTASMA_T contenente le informazioni di blinky
 * @param pinky: variabile di tipo FANTASMA_T contenente le informazioni di pinky
 * @param inky: variabile di tipo FANTASMA_T contenente le informazioni di inky
 * @param clyde: variabile di tipo FANTASMA_T contenente le informazioni di clyde
 * @param m: variabile contenente le informazioni riguardanti la mappa di gioco di tipo MAPPA_T
 * @param timer2: timer di gioco che controlla i secondi trascorsi dall'inizio della vita
 * @return void
 */
void controlla_fantasmi(PLAYER_t &pacman, FANTASMA_t &blinky, FANTASMA_t &inky,
                        FANTASMA_t &clyde, FANTASMA_t &pinky, MAPPA_t &mappa,
                        ALLEGRO_TIMER *timer2);
#endif /* LOGIC_H_ */
