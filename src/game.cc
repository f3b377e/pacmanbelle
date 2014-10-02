/**
 * @mainpage Pac-Man
 * Questo è un remake del classico gioco di Pac-Man, il quale deve fare più punti possibili mangiando i pallini e evitando di essere mangiato
 * dai fantasmi.
 *
 * Il loop del gioco è gestito dalla funzione ::main.
 * @author Francesco Bellei & Bruno Ghion
 */

//C++ header
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <cassert>

//Allegro header
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
#include "io.h"
#include "logic.h"
#include "gui.h"
#include "init.h"

//debug mode
#ifdef DEBUG_MODE
	#include "debug.h"
#endif

using namespace std;

int main(int argc, char *argv[]){
    int menu = 1;
    //int morte = -1;
    char fileliv[20];
    int fuga_count = -1;
    bool redraw = true;
    bool done = false;
    bool tasto[8] = {false, false, false, false, false, false, false, false};
    ALLEGRO_DISPLAY *display = NULL;
    ALLEGRO_EVENT_QUEUE *event_queue = NULL;
    ALLEGRO_TIMER *timer = NULL;
    ALLEGRO_TIMER *timer2 = NULL;
    //ALLEGRO_TIMER *timermov = NULL;

    /**Inizializzazioni: */

    //Inizializzazione Allegro
    if(!al_init())
        return -1;

    al_init_image_addon();
    al_init_font_addon();
    al_init_ttf_addon();
    al_init_acodec_addon();
    al_install_audio();
    al_reserve_samples(10);
    al_install_keyboard();

    //Creazione Display
    al_set_new_display_flags(0);
    al_set_new_window_position(200,40);
    display = al_create_display(SCREENWIDTH, SCREENHEIGHT);
    if(!display)
        return -2;
    al_set_window_title(display, "Pacman Project");

    //Eventi
    event_queue  = al_create_event_queue();

    //Timer
    timer = al_create_timer(1.0 / FPS);
    timer2 = al_create_timer(1.0 / FTIME);
    //timermov = al_create_timer(1.0 / FMOV);

    //Player
    PLAYER_t pacman;

    //Nemici
    FANTASMA_t blinky, pinky, inky, clyde;
    init_blinky(blinky);
    init_clyde(clyde);
    init_inky(inky);
    init_pinky(pinky);

    //Font
    FONT_t font;
    init_font(font);

    //Bitmap
    BITMAP_t bitmap;
    init_bitmap(bitmap);

    //Audio
    AUDIO_t audio;
    init_audio(audio);

    //Stato iniziale del gioco
    int livello = 1;
    bool caricamappa = true;
    STATO_GIOCO stato_gioco = MENU;

    //MAPPA
    MAPPA_t mappa;
    init_mappa(mappa);

    //Event Queue registries
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_timer_event_source(timer2));
    //al_register_event_source(event_queue, al_get_timer_event_source(timermov));
    al_register_event_source(event_queue, al_get_display_event_source(display));

    al_start_timer(timer);

    //Loop del Gioco;
    while(!done)
    {

        ALLEGRO_EVENT event;
        al_wait_for_event(event_queue, &event);

        if(event.type == ALLEGRO_EVENT_KEY_DOWN)
            agg_tasti(event, tasto, true);

        else if(event.type == ALLEGRO_EVENT_KEY_UP)
            agg_tasti(event, tasto, false);

        else if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
			stato_gioco = QUIT;

        else if(tasto[ESCAPE])
            stato_gioco = QUIT;

        else if(event.type == ALLEGRO_EVENT_TIMER)
        {
            #ifdef DEBUG_MODE
                if(tasto[D]){
                    al_stop_sample(&audio.id);
                    debug_console(timer,pacman,blinky,pinky,inky,clyde,mappa,audio,livello, caricamappa, stato_gioco);
                }
            #endif // DEBUG_MODE

            //Update
            switch(stato_gioco){
                case MENU:
                    anima_menu(menu, tasto, stato_gioco);
                break;

                case CARICA:
                    if(caricamappa){
                        load_map(mappa,fileliv,livello);
                        caricamappa = false;
                    }
                    init_pacman(pacman);
                    if (!al_play_sample(audio.pacman_beginning, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE,&audio.id))
                        cout<<"\n Audio Error! - non parte pacman_beginning";
                    al_stop_timer(timer);
                    draw_countdown(font, bitmap, mappa);
                    al_start_timer(timer);
                    if (!al_play_sample(audio.siren, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP,&audio.id))
                        cout<<"\n Audio Error! - non parte audio siren";
                    stato_gioco = PLAY;
                break;

                case PLAY:
                    al_start_timer(timer2);

                    if(tasto[SPACE]){
                        al_stop_timer(timer2);
                        stato_gioco = PAUSA;
                        tasto[SPACE] = false;
                    }

                    move_pacman(pacman, mappa, audio, tasto);
                    pac_mangia(mappa, pacman, audio, blinky, pinky, inky, clyde, timer2, fuga_count);

                    if(al_get_timer_count(timer2) == fuga_count){
                        fuga_count = -1;
                        al_stop_sample(&audio.id);
                        al_play_sample(audio.siren, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP,&audio.id);
                        cambia_stato(blinky,pinky,inky,clyde,pacman);
                    }

                    if(blinky.stato != ONDULA){
                        if(blinky.stato != FUGA){
                            if((al_get_timer_count(timer2) >= 0 && al_get_timer_count(timer2) <= 7) ||
                               (al_get_timer_count(timer2) >= 27 && al_get_timer_count(timer2) <= 34) ||
                               (al_get_timer_count(timer2) >= 54 && al_get_timer_count(timer2) <= 59) ||
                               (al_get_timer_count(timer2) >= 79 && al_get_timer_count(timer2) <= 84)){
                                blinky.stato = SPARPAGLIAMENTO;
                            }
                            else{
                                blinky.stato = INSEGUIMENTO;
                            }
                        }
                        move_blinky(mappa, pacman, blinky);
                    }
                    else if(blinky.stato == ONDULA)
                        ondula(mappa, blinky);



                    if(pinky.stato != ONDULA){
                        if(pinky.stato != FUGA){
                            if((al_get_timer_count(timer2) >= 0 && al_get_timer_count(timer2) <= 7) ||
                              (al_get_timer_count(timer2) >= 27 && al_get_timer_count(timer2) <= 34) ||
                              (al_get_timer_count(timer2) >= 54 && al_get_timer_count(timer2) <= 59) ||
                              (al_get_timer_count(timer2) >= 79 && al_get_timer_count(timer2) <= 84)){
                                pinky.stato = SPARPAGLIAMENTO;
                            }
                            else{
                                pinky.stato = INSEGUIMENTO;
                            }
                        }
                        move_pinky(mappa, pacman, pinky);
                    }
                    else{
                        ondula(mappa, pinky);
                        if(al_get_timer_count(timer2) > 2){
                            pinky.stato = INSEGUIMENTO;
                        }
                    }

                    if(inky.stato != ONDULA){
                        if(inky.stato != FUGA){
                            if((al_get_timer_count(timer2) >= 0 && al_get_timer_count(timer2) <= 7) ||
                              (al_get_timer_count(timer2) >= 27 && al_get_timer_count(timer2) <= 34) ||
                              (al_get_timer_count(timer2) >= 54 && al_get_timer_count(timer2) <= 59) ||
                              (al_get_timer_count(timer2) >= 79 && al_get_timer_count(timer2) <= 84)){
                                inky.stato = SPARPAGLIAMENTO;
                            }
                            else{
                                inky.stato = INSEGUIMENTO;
                            }
                        }
                        move_inky(mappa, pacman, inky, blinky);
                    }
                    else{
                        ondula(mappa, inky);
                        if(al_get_timer_count(timer2) > 8){
                            inky.stato = INSEGUIMENTO;
                        }
                    }

                    if(clyde.stato != ONDULA){
                        if(clyde.stato != FUGA){
                            if((al_get_timer_count(timer2) >= 0 && al_get_timer_count(timer2) <= 7) ||
                              (al_get_timer_count(timer2) >= 27 && al_get_timer_count(timer2) <= 34) ||
                              (al_get_timer_count(timer2) >= 54 && al_get_timer_count(timer2) <= 59) ||
                              (al_get_timer_count(timer2) >= 79 && al_get_timer_count(timer2) <= 84)){
                                clyde.stato = SPARPAGLIAMENTO;
                            }
                            else{
                                clyde.stato = INSEGUIMENTO;
                            }
                        }
                        move_clyde(mappa, pacman, clyde);
                    }
                    else{
                        ondula(mappa, clyde);
                        if(al_get_timer_count(timer2) > 12 && pacman.punteggio > 600){
                            clyde.stato = INSEGUIMENTO;
                        }
                    }

                break;

                case MORTE:
                break;

                case PAUSA:
                    al_stop_sample(&audio.id);
                    if (tasto[SPACE]){
                        al_start_timer(timer2);
                        stato_gioco = PLAY;
                        if(blinky.stato == FUGA || pinky.stato == FUGA || inky.stato == FUGA || clyde.stato == FUGA )
                            al_play_sample(audio.ghosts_scared, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP,&audio.id);
                        else
                            al_play_sample(audio.siren, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP,&audio.id);
                        tasto[SPACE] = false;
                    }
                break;

                case CONTROLS:
                break;

                case HIGH_SCORE:
                break;

                case GAME_OVER:
                break;

                case WIN:
                break;

                case QUIT:
                    done = true;
                break;
            }
            redraw = true;
        }

        if(redraw && al_is_event_queue_empty(event_queue))
        {
            redraw = false;
            //draw
            switch(stato_gioco){
                case MENU:
                    draw_screen_menu(menu, font, bitmap);
                break;

                case CARICA:
                    draw_path(bitmap, mappa);
                break;

                case PLAY:
                    al_clear_to_color(al_map_rgb(0,0,0));
                    draw_path(bitmap,mappa);
                    draw_pacman(pacman);

                    if(blinky.stato == FUGA)
                        draw_fant_fuga(bitmap, blinky);
                    else
                        draw_fantasma(blinky);

                    if(pinky.stato == FUGA)
                        draw_fant_fuga(bitmap, pinky);
                    else
                        draw_fantasma(pinky);

                    if(inky.stato == FUGA)
                        draw_fant_fuga(bitmap, inky);
                    else
                        draw_fantasma(inky);

                    if(clyde.stato == FUGA)
                        draw_fant_fuga(bitmap, clyde);
                    else
                        draw_fantasma(clyde);

                    al_draw_textf(font.h5, al_map_rgb(255,0,0), OFFSETX, 550, 0,
									"SCORE: %d",pacman.punteggio);
                    al_draw_textf(font.h5, al_map_rgb(255,0,0), OFFSETX+200, 550, 0,
									"LIVES: %d",pacman.vita);
                    al_draw_bitmap_region(bitmap.frutta, 0, 0, 16, 16, 550, OFFSETY, 0);
                    al_flip_display();
                break;

                case MORTE:
                break;

                case PAUSA:
                    draw_pause(font);
                break;

                case CONTROLS:
                    al_clear_to_color(al_map_rgb(0,0,0));
                    al_flip_display();
                break;

                case HIGH_SCORE:
                    al_clear_to_color(al_map_rgb(0,0,0));
                    al_flip_display();
                break;

                case GAME_OVER:
                break;

                case WIN:
                break;

                case QUIT:
                    al_clear_to_color(al_map_rgb(0,0,0));
                    al_flip_display();
                break;
            }
        }
    }


    dest_bitmap(bitmap);
    dest_font(font);
    dest_audio(audio);
    al_destroy_timer(timer);
    al_destroy_timer(timer2);
    al_destroy_event_queue(event_queue);
    al_destroy_display(display);
   return 0;
}
