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
#include <cassert>

//Allegro header
#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>

//header interni
#include "logic.h"
#include "io.h"
#include "data_struct.h"
#include "gui.h"
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
    al_init_primitives_addon();
    al_init_font_addon();
    al_init_ttf_addon();
    al_install_mouse();
    al_install_keyboard();

  if(!al_init())
      return -1;

//Variabili Allegro

   ////Display
   al_set_new_display_flags(0);
   al_set_new_window_position(200,40);
   ALLEGRO_DISPLAY *display = al_create_display(SCREENWIDTH, SCREENHEIGHT);
   al_set_window_title(display, "Pacman Project");
   al_hide_mouse_cursor(display);

   ////Eventi
   ALLEGRO_EVENT_QUEUE *event_queue  = al_create_event_queue();
   ALLEGRO_EVENT events;

   ////timer
   ALLEGRO_TIMER *timer = al_create_timer(1.0 / FPS);

//Player
   ////Pac-Man
   PLAYER_t pacman;
   init_pacman(pacman);

//Font
    FONT_t font;
    init_font(font);

//Bitmap
    BITMAP_t bitmap;
    init_bitmap(bitmap);

//Audio
    AUDIO_t audio;
    init_audio(audio);

//Menu
   bool selected = false, done = false;
   int menu = 0;
   draw_screen_menu(menu, font, bitmap);

//Game
    bool pause = false;

//Event Queue registries
   al_register_event_source(event_queue, al_get_keyboard_event_source());
   al_register_event_source(event_queue, al_get_timer_event_source(timer));
   al_register_event_source(event_queue, al_get_display_event_source(display));
   al_register_event_source(event_queue, al_get_mouse_event_source());

//Menu Screen
   while(!selected){
	al_wait_for_event(event_queue, &events);
	if (events.type == ALLEGRO_EVENT_KEY_DOWN){
		switch(events.keyboard.keycode){
			case ALLEGRO_KEY_DOWN:
				menu = menu + 1;
				if (menu > 3)
					menu = 3;
				if (menu < 1)
					menu = 1;
                              draw_screen_menu(menu,font,bitmap);
			break;
			case ALLEGRO_KEY_UP:
				menu = menu - 1;
				if (menu > 3)
					menu = 3;
				if (menu < 1)
					menu = 1;
                              draw_screen_menu(menu,font,bitmap);
			break;
			case ALLEGRO_KEY_ENTER:
				selected = true;
			break;
			case ALLEGRO_KEY_ESCAPE:
                return 0;
            break;
        	}
	}else if(events.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
		return 0 ;
   	}
   }
   switch (menu){
	case 1 :
		al_start_timer(timer);
		while(!done){
		al_wait_for_event(event_queue, &events);

			if (events.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
			   return 0;
			}
			if (events.type == ALLEGRO_EVENT_KEY_DOWN)
			{
			   #ifdef DEBUG_MODE
			   	if(events.keyboard.keycode == ALLEGRO_KEY_D) {
					DEBUG_CONSOLE;
			  	 }
			   #endif
			   switch (events.keyboard.keycode){
				   case ALLEGRO_KEY_UP:
					pacman.dir = SU;
				   break;
				   case ALLEGRO_KEY_DOWN:
					pacman.dir = GIU;
				   break;
				   case ALLEGRO_KEY_LEFT:
					pacman.dir = SX;
				   break;
				   case ALLEGRO_KEY_RIGHT:
					pacman.dir = DX;
				   break;
                   case ALLEGRO_KEY_ESCAPE:
                    done = true;
                    return 0;
				   break;
                    case ALLEGRO_KEY_SPACE:
                    	pause = true;
                    while(pause)
                   			{
                        			al_wait_for_event(event_queue, &events);
                        			draw_pause(font);
                        			if (events.type == ALLEGRO_EVENT_KEY_DOWN)
                        			{
                            				if (events.keyboard.keycode == ALLEGRO_KEY_SPACE)
                                			pause = false;
                        			}
                    			}
				   	break;
			   }
			}
			if(events.type == ALLEGRO_EVENT_TIMER)
			{
                move_pacman(pacman,bitmap);
			}
		}
	break;
	case 2:
	    done = false;
        al_start_timer(timer);

		while (!done){

            al_wait_for_event(event_queue, &events);
            if (events.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
                done = true;
            }

            if (events.type == ALLEGRO_EVENT_KEY_DOWN){
                if(events.keyboard.keycode == ALLEGRO_KEY_ENTER){
                    draw_path(bitmap);
                    al_flip_display();
                }
                if(events.keyboard.keycode == ALLEGRO_KEY_ESCAPE){
                    done = true;
                }
            }
		}

        break;
	case 3:
		al_clear_to_color(al_map_rgb(0,0,0));
		al_flip_display();
		al_rest(2.0);
	break;
   }

   dest_bitmap(bitmap);
   dest_font(font);
   al_destroy_timer(timer);
   al_destroy_event_queue(event_queue);
   al_destroy_display(display);
return 0;
}
