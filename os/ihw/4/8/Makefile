.PHONY: default build sample clean

default: sample

build:
	gcc -o judge judge.c

sample: judge
	./judge 5

judge:
	gcc -o judge judge.c

clean:
	rm -f judge