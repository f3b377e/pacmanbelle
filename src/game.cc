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

//debug mode
#ifdef DEBUG_MODE
	#include "debug.h"
#endif

using namespace std;
//Prototipi

/** Funzione principale.
 *
 * Si occupa di inizializzare le strutture dati del gioco e gestisce il ciclo
 * principale.
 *
 */
int main(int argc, char *argv[]){

// Inizializzazione degli addons di Allegro 5.
    al_init();
    al_init_image_addon();
    al_init_font_addon();
    al_init_ttf_addon();
    al_init_acodec_addon();
    al_install_mouse();
    al_install_audio();
    al_install_keyboard();

/**Inizializzazioni: */

//Display
   al_set_new_display_flags(0);
   al_set_new_window_position(200,40);
   ALLEGRO_DISPLAY *display = al_create_display(SCREENWIDTH, SCREENHEIGHT);
   if (display == NULL)
        cout<<"Display Error!";
   al_set_window_title(display, "Pacman Project");
   al_hide_mouse_cursor(display);

//Eventi
   ALLEGRO_EVENT_QUEUE *event_queue  = al_create_event_queue();
   ALLEGRO_EVENT events;

//Timer
   ALLEGRO_TIMER *timer = al_create_timer(1.0 / FPS);

//Player
   FANTASMA_t blinky, pinky, inky, clyde;
   PLAYER_t pacman;
   ///Pac-Man
    init_pacman(pacman);
   ///Blinky
    init_blinky(blinky);
   ///Pinky
    init_pinky(pinky);
   ///Inki
    init_inky(inky);
   ///Clyde
    init_clyde(clyde);
//Font
    FONT_t font;
    init_font(font);

//Bitmap
    BITMAP_t bitmap;
    init_bitmap(bitmap);

//Audio
    AUDIO_t audio;
    init_audio(audio);

//MAPPA
    MAPPA_t mappa;
    init_mappa(mappa);

//Altre variabili
   int menu = 1;
   int livello = 1;
   STATO_GIOCO stato_gioco = MENU;

//Event Queue registries
   al_register_event_source(event_queue, al_get_keyboard_event_source());
   al_register_event_source(event_queue, al_get_timer_event_source(timer));
   al_register_event_source(event_queue, al_get_display_event_source(display));
   al_register_event_source(event_queue, al_get_mouse_event_source());

//Menu Screen
   draw_screen_menu(menu, font, bitmap);
   while(stato_gioco == MENU){
        al_wait_for_event(event_queue, &events);
	if (events.type == ALLEGRO_EVENT_KEY_DOWN){
		switch(events.keyboard.keycode){
			case ALLEGRO_KEY_DOWN:
				menu += 1;
				if (menu > 3)
					menu = 3;
				if (menu < 1)
					menu = 1;
                              draw_screen_menu(menu,font,bitmap);
			break;
			case ALLEGRO_KEY_UP:
				menu -= 1;
				if (menu > 3)
					menu = 3;
				if (menu < 1)
					menu = 1;
                              draw_screen_menu(menu,font,bitmap);
			break;
			case ALLEGRO_KEY_ENTER:
                		switch (menu){
                		case 1:
                    			stato_gioco = PLAY;
                		break;
                		case 2:
                    			stato_gioco = CONTROLS;
                		break;
                		case 3:
                    			stato_gioco = HIGH_SCORE;
                		break;
                		}
            		break;
			case ALLEGRO_KEY_ESCAPE:
                		stato_gioco = QUIT;
            		break;
            }
	}else if(events.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
        stato_gioco = QUIT;
    }
   }
   switch (stato_gioco){
	case PLAY :
        load_map(mappa, filenamelv1);
        draw_path(bitmap, mappa);
        al_reserve_samples(2);
        if (!al_play_sample(audio.pacman_beginning, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE,&audio.id))
            cout<<"\n Audio Error! - non parte pacman_beginning";
        draw_countdown(font, bitmap, mappa);

        if (!al_play_sample(audio.siren, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP,&audio.id))
            cout<<"\n Audio Error! - non parte pacman_beginning";
        al_start_timer(timer);
        while(stato_gioco == PLAY){
                al_wait_for_event(event_queue, &events);
            if (events.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
                stato_gioco = QUIT;
            if (events.type == ALLEGRO_EVENT_KEY_DOWN)
            {
               #ifdef DEBUG_MODE
                if(events.keyboard.keycode == ALLEGRO_KEY_D) {
                    DEBUG_CONSOLE;
                 }
               #endif
               switch (events.keyboard.keycode){
               case ALLEGRO_KEY_UP:
                pacman.succdir = SU;
               break;
               case ALLEGRO_KEY_DOWN:
                pacman.succdir = GIU;
               break;
               case ALLEGRO_KEY_LEFT:
                pacman.succdir = SX;
               break;
               case ALLEGRO_KEY_RIGHT:
                pacman.succdir= DX;
               break;
               case ALLEGRO_KEY_ESCAPE:
                stato_gioco = QUIT;
               break;
               case ALLEGRO_KEY_SPACE:
                stato_gioco = PAUSA;
               while(stato_gioco == PAUSA){
                        al_stop_sample(&audio.id);
                        al_wait_for_event(event_queue, &events);
                        draw_pause(font);
                        if (events.type == ALLEGRO_EVENT_KEY_DOWN){
                            if (events.keyboard.keycode == ALLEGRO_KEY_SPACE)
                                stato_gioco = PLAY;
                                al_play_sample(audio.siren, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP,&audio.id);
                                if (events.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
                                        stato_gioco = QUIT;
                            }
                            if (events.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
                                stato_gioco = QUIT;
                            }
                       break;
              }
              }
              if(events.type == ALLEGRO_EVENT_TIMER){
                move_pacman(pacman,mappa,audio);
                draw_pacman(pacman,bitmap);
                draw_blinky(blinky,bitmap);
                draw_clyde(clyde,bitmap);
                draw_pinky(pinky,bitmap);
                draw_inky(inky,bitmap);
                move_bliky(mappa, pacman, blinky);
                al_flip_display();
                al_clear_to_color(al_map_rgb(0,0,0));
                draw_path(bitmap, mappa);
                }
        }
	break;

	case CONTROLS:
       		al_clear_to_color(al_map_rgb(0,0,0));
		al_flip_display();
        break;
	case HIGH_SCORE:
        al_clear_to_color(al_map_rgb(0,0,0));
        al_flip_display();
    	break;
	case QUIT:
		al_clear_to_color(al_map_rgb(0,0,0));
		al_flip_display();
	break;
   }

   dest_bitmap(bitmap);
   dest_font(font);
   dest_audio(audio);
   al_destroy_timer(timer);
   al_destroy_event_queue(event_queue);
   al_destroy_display(display);
   return 0;
}
