.PHONY: default run clean

default: run

run: main
	./main

clean:
	rm -f main

main: main.c
	gcc -o main main.c