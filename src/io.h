/*
 * io.h
 *
 *      Author: Belle & Bruce
 */

#ifndef IO_H_
#define IO_H_

/** La funzione setta i valori booleani dell'array tasto inizializzato nel ::main, a seconda se
 *  il tasto è stato premuto o rilasciato;
 *  Parametri: event evento Allegro
 *  Parametri: tasto array contenente lo stato dei tasti premuti o rilasciati
 *  Parametri: setting valore da attribuire al campo booleano dell'array
 */
void agg_tasti(ALLEGRO_EVENT &event, bool tasto[], bool setting);

/**Carica la mappa da file in Memoria*/
void load_map(MAPPA_t&, const char []);

void scrivi_mappa_su_file(const MAPPA_t &, const char []);


#endif // IO_H_
