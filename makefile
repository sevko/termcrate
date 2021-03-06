CC = gcc
xterm = xterm -geom 176x44 -bg black -name termcrate

all: build build/termcrate.o build/utils.o build/graphics.o build/audio.o build/menu.o build/xterm_control.o build/keyboard.o
	$(CC) build/termcrate.o build/utils.o build/graphics.o build/audio.o build/menu.o build/xterm_control.o build/keyboard.o -o termcrate -lm

build/termcrate.o: src/termcrate.c
	$(CC) -c src/termcrate.c -o build/termcrate.o

build/utils.o: src/utils.c
	$(CC) -c src/utils.c -o build/utils.o

build/graphics.o: src/graphics.c
	$(CC) -c src/graphics.c -o build/graphics.o -lm

build/audio.o: src/audio.c
	$(CC) -c src/audio.c -o build/audio.o

build/menu.o: src/menu.c
	$(CC) -c src/menu.c -o build/menu.o

build/xterm_control.o: xterm/xterm_control.c
	$(CC) -c xterm/xterm_control.c -o build/xterm_control.o 

build/keyboard.o: xterm/keyboard.c
	$(CC) -c xterm/keyboard.c -o build/keyboard.o

run: termcrate
	$(xterm) ./termcrate

clean: 
	rm -rf build
	rm termcrate

build:
	mkdir build
