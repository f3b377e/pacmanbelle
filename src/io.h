/*
 * io.h
 *
 *      Author: Belle & Bruce
 */

#ifndef IO_H_
#define IO_H_

/** La funzione setta i valori booleani dell'array tasto inizializzato nel ::main, a seconda se
 * il tasto è stato premuto o rilasciato.
 * Viene eseguito nella funzione ::main, una volta per assegnare a setting true, se un tasto (tra quelli predefiniti)
 * viene premuti,un'altra volta per assegnare a setting false, quando questo tasto viene rilasciato.
 * @param event: variabile utilizzata contenente l'evento dei tasti
 * @param tasto: array contenente lo stato dei tasti premuti o rilasciati
 * @param setting: valore da attribuire al campo booleano dell'array ::tasto
 * @return void.
 */
void agg_tasti(ALLEGRO_EVENT &event, bool tasto[], bool setting);

/**Carica la mappa da un file contenuto nella cartella data/map/.
 * A fileliv viene assegnata la prima parte della stringa del percorso dove risiede il file contenente
 * la mappa, successivamente gli viene assegnato il valore del livello convertito in una stringa, scritto prima su una
 * stringa provvisoria (buff), in fine a fileliv viene assegnata l'ultima parte del percorso.
 * Dopo di che viene aperto il file di nome fileliv per leggere una matrice che sarà poi la mappa del gioco.
 *
 * La funzione viene eseguita dalla funzione ::main, ogni volta che si attiva la variabile booleana caricamappa nello stato
 * stato di gioco ::CARICA.
 * @param m: variabile contenente le informazioni riguardanti la mappa di gioco di tipo MAPPA_T
 * @param fileliv: variabile che viene modificata per contenere il nome del file in base al livello
 * @param livello: livello corrente in gioco.
 * @return void.
 */
void load_map(MAPPA_t& m, char fileliv[], int livello);

/**Prende in ingresso da un file di salvataggio (sav.txt) il record fatto in precedenza.
 * Viene eseguita nel ::main, negli stati di gioco ::WIN e ::GAME_OVER nel caso in cui il giocatore ha fatto un nuovo punteggio record,
 * oppure nello stato ::HIGH_SCORE quando un giocatore vuole vedere qual'e' stato il miglior punteggio.
 * @param . nessun parametro in ingresso.
 * @return ritorna un valore intero che rappresenta il record.
 */
int preleva_record();

/**Scrive sul file di salvataggio (sav.txt) il record.
 * Viene eseguita nel ::main, negli stati di gioco ::WIN e ::GAME_OVER nel caso in cui il giocatore ha fatto un nuovo punteggio record.
 * @param new_record: variabile contenente il valore del record
 * @return void.
 */
void salva_record(int new_record);

#endif // IO_H_
