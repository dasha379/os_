.PHONY: clean

run:
	./main $(num_threads)

main: main.c -lpthread
	gcc -Wall -Wpedantic -Werror main.c -o main -lpthread

clean:
	rm -f main