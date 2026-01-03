all:
	gcc src/main.c src/mechs.c src/settings.c src/audio.c -o main -I/usr/include/SDL2 -lSDL2 -lSDL2_ttf -lSDL2_mixer -fsanitize=address -static-libasan -g
