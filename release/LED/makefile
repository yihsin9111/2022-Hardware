CC = g++
FLAG = -O2 -lwiringPi -lwiringPiDev
all:bin/example bin/off_example

./obj/LED_strip.o: ./src/LED_strip.cpp ./lib/LED_strip.h
	$(CC) $(FLAG) -c ./src/LED_strip.cpp -o ./obj/LED_strip.o

./obj/gamma_correction.o: ./src/gamma_correction.cpp ./lib/gamma_correction.h
	$(CC) $(FLAG) -c ./src/gamma_correction.cpp -o ./obj/gamma_correction.o

bin/example:  ./src/example.cpp  ./obj/LED_strip.o ./obj/gamma_correction.o
	$(CC) $(FLAG) ./src/example.cpp ./obj/LED_strip.o  -o ./bin/example

bin/part_example: ./lib/LED_strip.o
	$(CC) $(FLAG) ./src/part_example.cpp ./obj/LED_strip.o -o ./bin/part_example

bin/off_example:./lib/LED_strip.o
	$(CC) $(FLAG) ./src/off_example.cpp ./obj/LED_strip.o -o ./bin/off_example


	
clean:
	rm -rf ./bin/*
	rm -rf ./obj/*.*
