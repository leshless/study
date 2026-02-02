.PHONY: default sample clean

default: sample

sample: main
	touch source.txt
	echo "SOME DATADATADATADATADATADATADATADATADATA" > source.txt
	chmod +x source.txt
	./main source.txt target.txt
	ls -l | grep .txt

clean:
	rm source.txt target.txt main

main: main.c
	gcc -o main main.c