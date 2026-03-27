.PHONY: clean run

main: main.c
	gcc -Wall -Werror -Wpedantic main.c -o main

run: main
	./main ${filepath}

clean: main
	rm -rf main