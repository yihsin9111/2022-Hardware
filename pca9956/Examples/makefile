main:
	g++ -O2 -c ../pca9956.cpp -o ../pca9956.o -lwiringPi -lwiringPiDev
	g++ -O2 -c ../pca9956_LED.cpp -o ../pca9956_LED.o -lwiringPi -lwiringPiDev
	g++ -O2 -c ALL_SAME_COLOR.cpp -o ALL_SAME_COLOR.o -lwiringPi -lwiringPiDev
	g++ -O2 ../pca9956.o ../pca9956_LED.o ALL_SAME_COLOR.o -o ALL_SAME_COLOR -lwiringPi -l wiringPiDev

clean:
	rm -rf ./ALL_SAME_COLOR
	rm -rf ./*.o
