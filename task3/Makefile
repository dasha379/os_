.PHONY: clean run

run: main
	./main $(input) $(output) $(type)

main: main.c
	gcc -Wall -Wpedantic -Werror main.c -o main

clean:
	rm -rf main