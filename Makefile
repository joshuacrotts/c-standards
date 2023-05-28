CC = gcc
EMCC = emcc
EXES = main
OBJS = src/*.c tests/basic_test/src/*.c tests/scroller_test/src/*.c lib/structures/src/*.c
CFLAGS = -Wall -Werror -Wno-unused-variable -Wno-uninitialized -Wno-unused-function -g3 -O3

ifeq ($(OS), Windows_NT)
	INCLUDE_PATHS = -IC:\MinGW\include\SDL2 -Iinclude
	LIBRARY_PATHS = -LC:\MinGW\lib
else
	INCLUDE_PATHS = -I/opt/homebrew/include -Iinclude
endif 

ifeq ($(OS), Windows_NT)
	LDFLAGS = -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf
else
	LDFLAGS = -lm -L/opt/homebrew/lib -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf
endif

#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = Game.o

all: $(EXES)

main: $(OBJS)
		$(CC) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(CFLAGS) -o $(OBJ_NAME) $(OBJS) $(LDFLAGS)

web: $(OBJS) 
		$(EMCC) $(OBJS) -o app.html --preload-file tests/scroller_test/res -lm -s USE_SDL=2 -s USE_SDL_IMAGE=2 -s SDL2_IMAGE_FORMATS='["png"]' -s USE_SDL_TTF=2 -s USE_SDL_MIXER=2

.PHONY clean:
		rm -rf Game.o *.dSYM