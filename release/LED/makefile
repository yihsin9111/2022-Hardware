CC = g++
FLAG = -O2 -lwiringPi -lwiringPiDev

all: bin/example

bin/example:  ./src/example.cpp  ./obj/LED_strip.o 
	$(CC) $(FLAG) ./src/example.cpp ./obj/LED_strip.o  -o ./bin/example

./obj/LED_strip.o: ./src/LED_strip.cpp ./lib/LED_strip.h
	$(CC) $(FLAG) -c ./src/LED_strip.cpp -o ./obj/LED_strip.o

clean:
	rm -rf ./bin/*
	rm -rf ./obj/*.*
