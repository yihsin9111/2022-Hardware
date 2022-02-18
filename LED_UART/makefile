CC = g++
FLAG = -O2 -lwiringPi -lwiringPiDev

main: 
	$(CC) $(FLAG) -c ./src/LED_strip.cpp -o ./obj/LED_strip.o
	$(CC) $(FLAG) -c ./src/main_example.cpp -o ./obj/main_example.o
	$(CC) $(FLAG) ./obj/LED_strip.o ./obj/main_example.o -o ./bin/main_example
clean:
	rm -rf ./bin/*.*
	rm -rf ./obj/*.*
