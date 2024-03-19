output:
	gcc src/main.c src/window.c src/snake.c -lSDL2 -lSDL2_ttf

clean:
	rm a.out
