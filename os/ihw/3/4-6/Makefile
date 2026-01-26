.PHONY: default build sample clean

default: sample

build: judge

judge:
	gcc -o judge judge.c

sample: judge
	./judge 5

clean:
	rm -f judge