/*
 * init.h
 *
 *      Author: Belle & Bruce
 */
#ifndef INIT_H_
#define INIT_H_
/**Caricamento dei file audio.
 * Eseguita nel ::main nella fase di inizializzazione delle componenti del gioco.
 * @param a: variabile di tipo struttura AUDIO_T contenente i suoni del gioco.
 * @return void.
*/
void init_audio(AUDIO_t& a);

/**Caricamento delle immagini.
 * Eseguita nel ::main nella fase di inizializzazione delle componenti del gioco.
 * @param b: variabile di tipo struttura BITMAP_t contenente le immagini del gioco.
 * @return void.
 */
void init_bitmap(BITMAP_t& b);

/**Caricamento dei font.
 * Eseguita nel ::main nella fase di inizializzazione delle componenti del gioco.
 * @param f: variabile di tipo struttura FONT_t contenente i font del gioco.
 * @return void.
 */
void init_font(FONT_t& f);

/**Inizializzazione della mappa.
 * Eseguita nel ::main nella fase di inizializzazione delle componenti del gioco.
 * @param m: variabile contenente le informazioni riguardanti la mappa di gioco di tipo MAPPA_T.
 * @return void.
 */
void init_mappa(MAPPA_t &m);

/**Inizializzazione di Pacman.
 * Eseguita nella funzione ::anima_menu, durante lo stato del gioco ::MENU, quando il giocatore preme il tasto ::ENTER
 * per far partire la partita.
 * @param pacman: varibaile contenente i dati di pac-man di tipo PLAYER_T.
 * @return void.
 */
void init_pacman(PLAYER_t& pacman);

/**Inizializzazione di Blinky.
 * Eseguita nella funzione ::main, durante lo stato del gioco ::CARICA.
 * @param b: variabile di tipo FANTASMA_T contenente le informazioni di blinky.
 * @param livello: livello corrente in gioco.
 * @return void.
 */
void init_blinky(FANTASMA_t &b, int livello);

/**Inizializzazione di Pinky.
 * Eseguita nella funzione ::main, durante lo stato del gioco ::CARICA.
 * @param p: variabile di tipo FANTASMA_T contenente le informazioni di pinky.
 * @param livello: livello corrente in gioco.
 * @return void.
 */
void init_pinky(FANTASMA_t &p, int livello);

/**Inizializzazione di Inky.
 * Eseguita nella funzione ::main, durante lo stato del gioco ::CARICA.
 * @param i: variabile di tipo FANTASMA_T contenente le informazioni di inky.
 * @param livello: livello corrente in gioco.
 * @return void.
 */
void init_inky(FANTASMA_t &i, int livello);

/**Inizializzazione di Clyde.
 * Eseguita nella funzione ::main, durante lo stato del gioco ::CARICA.
 * @param c: variabile di tipo FANTASMA_T contenente le informazioni di clyde.
 * @param livello: livello corrente in gioco.
 * @return void.
 */
void init_clyde(FANTASMA_t &c, int livello);

/**Funzione che dealloca le immagini caricate.
 * Eseguita nella funzione ::main appena il giocatore chiude il gioco.
 * @param b: variabile di tipo struttura BITMAP_t contenente le immagini del gioco.
 * @return void.
 */
void dest_bitmap(BITMAP_t &b);

/**Funzione che dealloca i font caricati.
 * Eseguita nella funzione ::main appena il giocatore chiude il gioco.
 * @param f: variabile di tipo struttura FONT_t contenente i font del gioco.
 * @return void.
 */
void dest_font(FONT_t &f);

/**Funzione che dealloca l'audio.
 * Eseguita nella funzione ::main appena il giocatore chiude il gioco.
 * @param a: variabile di tipo struttura AUDIO_T contenente i suoni del gioco.
 * @return void.
 */
void dest_audio(AUDIO_t &a);


#endif // INIT_H_
