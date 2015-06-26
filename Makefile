# Sous Linux, utiliser sdl-config --cflags et sdl-config --libs pour remplir
# les deux lignes ci dessous
CFLAGS=`sdl-config --cflags`

LDFLAGS=`sdl-config --libs`


# Sous MAC OS X
#CFLAGS=-g -Wall -I/Library/Frameworks/SDL.framework/Headers  -I/System/Library/Frameworks/OpenGL.framework/Headers
#LDFLAGS= -framework SDL -framework Cocoa -framework OpenGL

mario: game.o engine.o graphics.o timer.o
	gcc -Wall -o $@  $^ ${LDFLAGS} -lSDL_ttf -lSDL_mixer
game.o: game.c engine.h
	gcc -c ${CFLAGS} $<
timer.o: timer.c
	gcc -c ${CFLAGS} $<
engine.o: engine.c engine.h
	gcc -c ${CFLAGS} $<
graphics.o: graphics.c graphics.h engine.h
	gcc -c ${CFLAGS} $<

clean: 
	rm mario *.o
