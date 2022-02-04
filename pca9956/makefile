main:
	g++ -O2 -c pca9956.cpp -o pca9956.o -lwiringPi -lwiringPiDev
	g++ -O2 -c pca9956_LED.cpp -o pca9956_LED.o -lwiringPi -lwiringPiDev
	g++ -O2 -c ALL_SAME_COLOR.cpp -o ALL_SAME_COLOR.o -lwiringPi -lwiringPiDev
	g++ -O2 pca9956.o pca9956_LED.o ALL_SAME_COLOR.o -o ALL_SAME_COLOR -lwiringPi -lwiringPiDev

test:
	g++ test1239.cpp -l wiringPi -o test1239
clean:
	rm -rf ./pca9956
	rm -rf ./pca9956_LED
	rm -rf ./test1239
	rm -rf ./*.o
