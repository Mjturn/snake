output:
	gcc src/main.c src/window.c -lSDL2 -lSDL2_ttf

clean:
	rm a.out
