allegrolib = `pkg-config --cflags --libs allegro-5.0 allegro_acodec-5.0 allegro_audio-5.0 allegro_color-5.0 allegro_dialog-5.0 allegro_font-5.0 allegro_image-5.0 allegro_main-5.0 allegro_memfile-5.0 allegro_physfs-5.0 allegro_primitives-5.0 allegro_ttf-5.0`

OBJ = game.o gui.o io.o logic.o
CC = game.cc gui.cc io.cc logic.cc
CXXFLAGS = -Wall

Pacman: $(OBJ)
	g++ -Wall -o Pacman $(OBJ) $(allegrolib)

-include dipendenze

.PHONY: depend clean cleanall Debug Release

depend:
	g++ -MM *.cc > dipendenze
clean:
	rm *.o
cleanall:
	rm *.o *~ Pacman *~ Pacman_debug

Debug: 	
	g++ -Wall -g -D DEBUG_MODE $(CC) $(allegrolib) -o bin/Debug/pacman

Release:
	g++ -Wall -g $(CC) $(allegrolib) -o bin/Release/pacman
