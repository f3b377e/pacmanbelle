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
    int morte = -1;
    char fileliv[20];
    int fuga_count = -1;
    bool nuovo_record = false;
    bool redraw = true;
    bool done = false;
    bool tasto[8] = {false, false, false, false, false, false, false, false};
    ALLEGRO_DISPLAY *display = NULL;
    ALLEGRO_EVENT_QUEUE *event_queue = NULL;
    ALLEGRO_TIMER *timer = NULL;
    ALLEGRO_TIMER *timer2 = NULL;
    ALLEGRO_TIMER *timermov = NULL;

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
    timermov = al_create_timer(1.0 / FMOV);

    //Player
    PLAYER_t pacman;

    //Nemici
    FANTASMA_t blinky, pinky, inky, clyde;

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
    al_register_event_source(event_queue, al_get_timer_event_source(timermov));
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
                    if(tasto[ESCAPE]){
                        stato_gioco = QUIT;
                        tasto[ESCAPE] = false;
                    }
                    init_pacman(pacman);
                    anima_menu(menu, tasto, stato_gioco);
                break;

                case CARICA:
                    if(caricamappa){
                        load_map(mappa,fileliv,livello);
                        caricamappa = false;
                    }
                    init_blinky(blinky);
                    init_clyde(clyde);
                    init_inky(inky);
                    init_pinky(pinky);
                    if (!al_play_sample(audio.pacman_beginning, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE,&audio.id))
                        cout<<"\n Audio Error! - non parte pacman_beginning";
                    al_stop_timer(timer);
                    draw_countdown(font, bitmap, mappa);
                    al_start_timer(timer);
                    if (!al_play_sample(audio.siren, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP,&audio.id))
                        cout<<"\n Audio Error! - non parte audio siren";
                    stato_gioco = PLAY;
                    al_start_timer(timer2);
                break;

                case PLAY:

                    if(tasto[ESCAPE]){
                        stato_gioco = MENU;
                        caricamappa = true;
                        livello = 1;
                        al_stop_timer(timer2);
                        al_stop_sample(&audio.id);
                        al_set_timer_count(timer2, 0);
                        tasto[ESCAPE] = false;
                    }


                    if(tasto[SPACE]){
                        al_stop_timer(timer2);
                        stato_gioco = PAUSA;
                        tasto[SPACE] = false;
                    }

                    move_pacman(pacman, mappa, audio, tasto);
                    pac_mangia(mappa, pacman, audio, blinky, pinky, inky, clyde, timer2, fuga_count, font);

                    if(al_get_timer_count(timer2) == fuga_count){
                        fuga_count = -1;
                        al_stop_sample(&audio.id);
                        al_play_sample(audio.siren, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP,&audio.id);
                        if(blinky.stato == FUGA || pinky.stato == FUGA || inky.stato == FUGA || clyde.stato == FUGA ){
                            if(blinky.stato != ONDULA && blinky.stato != INSEGUIMENTO && blinky.stato != SPARPAGLIAMENTO && blinky.stato != MANGIATO){
                                blinky.stato = INSEGUIMENTO;
                                blinky.movespeed= blinky.movespeed + 1;
                            }

                            if(pinky.stato != ONDULA && pinky.stato != INSEGUIMENTO && pinky.stato != SPARPAGLIAMENTO && pinky.stato != MANGIATO){
                                pinky.stato = INSEGUIMENTO;
                                pinky.movespeed = pinky.movespeed + 1;
                            }

                            if(inky.stato != ONDULA && inky.stato != INSEGUIMENTO && inky.stato != SPARPAGLIAMENTO && inky.stato != MANGIATO){
                                inky.stato = INSEGUIMENTO;
                                inky.movespeed = inky.movespeed + 1;
                            }

                            if(clyde.stato != ONDULA && clyde.stato != INSEGUIMENTO && clyde.stato != SPARPAGLIAMENTO && clyde.stato != MANGIATO){
                                clyde.stato = INSEGUIMENTO;
                                clyde.movespeed = clyde.movespeed + 1;
                            }
                        }
                    }

                    if(blinky.stato != ONDULA){
                        if(blinky.stato != FUGA && blinky.stato != MANGIATO){
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
                        if(pinky.stato != FUGA && pinky.stato != MANGIATO){
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
                        if(inky.stato != FUGA && inky.stato != MANGIATO){
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
                        if(clyde.stato != FUGA && clyde.stato != MANGIATO){
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

                    if(blinky.stato != FUGA && blinky.stato != MANGIATO && collision_pacman(pacman,blinky)){
                       stato_gioco = MORTE;
                       al_stop_sample(&audio.id);
                       al_start_timer(timermov);
                       al_play_sample(audio.pacman_eaten, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE,0);
                    }
                    if(pinky.stato != FUGA && pinky.stato != MANGIATO && collision_pacman(pacman,pinky)){
                        stato_gioco = MORTE;
                        al_stop_sample(&audio.id);
                        al_start_timer(timermov);
                        al_play_sample(audio.pacman_eaten, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE,0);
                    }

                    if(inky.stato != FUGA && inky.stato != MANGIATO && collision_pacman(pacman,inky)){
                        stato_gioco = MORTE;
                        al_stop_sample(&audio.id);
                        al_start_timer(timermov);
                        al_play_sample(audio.pacman_eaten, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE,0);
                    }

                    if(clyde.stato != FUGA && clyde.stato != MANGIATO && collision_pacman(pacman,clyde)){
                        stato_gioco = MORTE;
                        al_stop_sample(&audio.id);
                        al_start_timer(timermov);
                        al_play_sample(audio.pacman_eaten, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE,0);
                    }

                    if (victory(mappa,stato_gioco, caricamappa, livello, pacman)){
                        al_stop_sample(&audio.id);
                        al_stop_timer(timer2);
                        al_set_timer_count(timer2, 0);
                    }

                break;

                case MORTE:
                   if(event.timer.source == timermov){
                        morte++;
                        if(morte >= 11){
                            morte = 0;
                            death_pacman(pacman, stato_gioco, caricamappa);
                            al_stop_timer(timer2);
                            al_stop_timer(timermov);
                            al_set_timer_count(timer2, 0);
                        }
                    }
                break;

                case PAUSA:
                    if(tasto[ESCAPE]){
                        stato_gioco = MENU;
                        caricamappa = true;
                        livello = 1;
                        al_stop_timer(timer2);
                        al_stop_sample(&audio.id);
                        tasto[ESCAPE] = false;
                    }

                    if(tasto[ESCAPE]){
                        stato_gioco = MENU;
                        caricamappa = true;
                        tasto[ESCAPE] = false;
                    }
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
                    if(tasto[ESCAPE]){
                        stato_gioco = MENU;
                        tasto[ESCAPE] = false;
                    }
                break;

                case HIGH_SCORE:
                    if(tasto[ESCAPE]){
                        stato_gioco = MENU;
                        tasto[ESCAPE] = false;
                    }
                break;

                case GAME_OVER:
                    if (tasto[ENTER]){
                        stato_gioco = MENU;
                        caricamappa = true;
                        nuovo_record = false;
                        tasto[ENTER] = false;
                    }
                break;

                case WIN:
                    if (tasto[ENTER]){
                        stato_gioco = MENU;
                        caricamappa = true;
                        nuovo_record = false;
                        al_set_timer_count(timer2, 0);
                        tasto[ENTER] = false;
                    }
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

                    if(blinky.stato == FUGA){
                        if(fuga_count - al_get_timer_count(timer2) <= 3)
                            draw_fant_fuga(bitmap, blinky, 1);
                        else
                            draw_fant_fuga(bitmap, blinky, 0);
                    }
                    else if(blinky.stato == MANGIATO)
                        draw_fant_mangiato(bitmap, blinky);
                    else if(blinky.stato == INSEGUIMENTO || blinky.stato == SPARPAGLIAMENTO || blinky.stato == ONDULA)
                        draw_fantasma(blinky);

                    if(pinky.stato == FUGA){
                        if(fuga_count - al_get_timer_count(timer2) <= 3)
                            draw_fant_fuga(bitmap, pinky, 1);
                        else
                            draw_fant_fuga(bitmap, pinky, 0);
                    }
                    else if(pinky.stato == MANGIATO)
                        draw_fant_mangiato(bitmap, pinky);
                    else if(pinky.stato == INSEGUIMENTO || pinky.stato == SPARPAGLIAMENTO || pinky.stato == ONDULA)
                        draw_fantasma(pinky);

                    if(inky.stato == FUGA){
                        if(fuga_count - al_get_timer_count(timer2) <= 3)
                            draw_fant_fuga(bitmap, inky, 1);
                        else
                            draw_fant_fuga(bitmap, inky, 0);
                    }
                    else if(inky.stato == MANGIATO)
                        draw_fant_mangiato(bitmap, inky);
                    else if(inky.stato == INSEGUIMENTO || inky.stato == SPARPAGLIAMENTO || inky.stato == ONDULA)
                        draw_fantasma(inky);


                    if(clyde.stato == FUGA){
                        if(fuga_count - al_get_timer_count(timer2) <= 3)
                            draw_fant_fuga(bitmap, clyde, 1);
                        else
                            draw_fant_fuga(bitmap, clyde, 0);
                    }
                    else if(clyde.stato == MANGIATO)
                        draw_fant_mangiato(bitmap, clyde);
                    else if(clyde.stato == INSEGUIMENTO || clyde.stato == SPARPAGLIAMENTO || clyde.stato == ONDULA)
                        draw_fantasma(clyde);

                    al_draw_textf(font.h5, al_map_rgb(255,0,0), OFFSETX, 550, 0,
									"SCORE: %d",pacman.punteggio);

                    for(int i = 0; i < pacman.vita; i++){
                        al_draw_bitmap_region(pacman.img, 0, 2 * al_get_bitmap_height(pacman.img)/4
                                              , al_get_bitmap_width(pacman.img)/3
                                              , al_get_bitmap_height(pacman.img)/4
                                              , ((al_get_bitmap_width(pacman.img)/3)*i)+OFFSETX+200, 550, 0);
                    }
                    al_draw_textf(font.h5, al_map_rgb(255,0,0), OFFSETX+350, 550, 0,
									"LEVEL: %d",livello);
                    al_flip_display();
                break;

                case MORTE:
                    al_clear_to_color(al_map_rgb(0,0,0));
                    draw_path(bitmap, mappa);
                    al_draw_bitmap_region(bitmap.morte, 17*morte, 0, 17, 17, pacman.x, pacman.y,0);
                    al_draw_textf(font.h5, al_map_rgb(255,0,0), OFFSETX, 550, 0,
									"SCORE: %d",pacman.punteggio);
                    al_draw_textf(font.h5, al_map_rgb(255,0,0), OFFSETX+350, 550, 0,
									"LEVEL: %d",livello);
                    al_flip_display();
                break;

                case PAUSA:
                    draw_pause(font);
                break;

                case CONTROLS:
                    al_clear_to_color(al_map_rgb(0,0,0));
                    draw_controls(font, bitmap);
                    al_flip_display();
                break;

                case HIGH_SCORE:{
                    int record;
                    record = preleva_record();
                    al_clear_to_color(al_map_rgb(0,0,0));
                    draw_high_score(font, record);
                    al_flip_display();
                break;
                }
                case GAME_OVER:{
                    int record;
                    record = preleva_record();
                    if(record < pacman.punteggio){
                        salva_record(pacman.punteggio);
                        al_flip_display();
                        nuovo_record = true;
                   }
                    draw_gameover(font,bitmap,nuovo_record);
                break;
                }

                case WIN:{
                    int record;
                    record = preleva_record();
                    if(record < pacman.punteggio){
                        salva_record(pacman.punteggio);
                        nuovo_record = true;
                        al_flip_display();
                    }
                    draw_win(font, bitmap, nuovo_record);

                break;
                }

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
