CC = g++
FLAG = -O2 -lwiringPi -lwiringPiDev

all: bin/main_example

bin/example:  ./src/example.cpp  ./obj/LED_strip.o ./obj/gamma_correction.o
	$(CC) $(FLAG) ./src/example.cpp ./obj/LED_strip.o ./obj/gamma_correction.o -o ./bin/example

bin/gamma_test: ./src/gamma_test.cpp  ./obj/LED_strip.o ./obj/gamma_correction.o
	$(CC) $(FLAG) ./src/gamma_test.cpp ./obj/LED_strip.o ./obj/gamma_correction.o -o ./bin/gamma_test

bin/main_example: ./src/main_example.cpp  ./obj/LED_strip.o ./obj/gamma_correction.o
	$(CC) $(FLAG) ./src/main_example.cpp ./obj/LED_strip.o ./obj/gamma_correction.o -o ./bin/main_example

./obj/LED_strip.o: ./src/LED_strip.cpp ./lib/LED_strip.h
	$(CC) $(FLAG) -c ./src/LED_strip.cpp -o ./obj/LED_strip.o

./obj/gamma_correction.o: ./src/gamma_correction.cpp ./lib/gamma_correction.h
	$(CC) $(FLAG) -c ./src/gamma_correction.cpp -o ./obj/gamma_correction.o

clean:
	rm -rf ./bin/*
	rm -rf ./obj/*.*
