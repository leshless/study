.PHONY: default build sample clean

default: sample

build: judge player

judge:
	gcc -o judge judge.c

player:
	gcc -o player player.c

sample: judge
	./launch_players.sh
	./judge

clean:
	rm -f judge
	rm -f player