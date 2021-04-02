main:
	g++ -O2 -c ../src/pca9956.cpp -o ../pca9956.o -lwiringPi -lwiringPiDev
	g++ -O2 -c test0216.cpp -o test0216.o -lwiringPi -lwiringPiDev
	g++ -O2 ../pca9956.o test0216.o -o test0216 -lwiringPi -l wiringPiDev

clean:
	rm -rf ./ALL_SAME_COLOR
	rm -rf ./CHOOSE_ONE
	rm -rf ./ALTO
	rm -rf ./*.o
