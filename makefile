CC = gcc
xterm = xterm -geom 176x44 -name termcrate

run: clean termcrate
	$(xterm) ./termcrate

clean: 
	rm -rf build
	rm termcrate

termcrate: build build/termcrate.o build/graphics.o build/xterm_control.o build/keyboard.o
	$(CC) build/termcrate.o build/graphics.o build/xterm_control.o build/keyboard.o -o termcrate

build/termcrate.o: src/termcrate.c
	$(CC) -c src/termcrate.c -o build/termcrate.o

build/graphics.o: src/graphics.c
	$(CC) -c src/graphics.c -o build/graphics.o

build/xterm_control.o: xterm/xterm_control.c
	$(CC) -c xterm/xterm_control.c -o build/xterm_control.o 

build/keyboard.o: xterm/keyboard.c
	$(CC) -c xterm/keyboard.c -o build/keyboard.o

build:
	mkdir build
