output:
	gcc src/main.c src/window.c src/snake.c -lSDL2

clean:
	rm a.out
