main: 
	g++ -O2 -c LED_strip.cpp -o LED_strip.o -lwiringPi -lwiringPiDev
	g++ -O2 -c main_example.cpp -o main_example.o -lwiringPi -lwiringPiDev
	g++ -O2 LED_strip.o main_example.o -o main_example -lwiringPi -lwiringPiDev
clean:
	rm -rf ./main_example
	rm -rf ./*.o
