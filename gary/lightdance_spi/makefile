main:
	g++ -O2 -c LED_strip.cpp -o LED_strip.o -lbcm2835
	g++ -O2 -c main_example.cpp -o main_example.o -lbcm2835
	g++ -O2 LED_strip.o main_example.o -o main_example -lbcm2835
	
clean:
	rm -rf ./main_example
	rm -rf ./*.o
