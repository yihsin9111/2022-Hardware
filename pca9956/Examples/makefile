main:
	g++ -O2 -c ../src/pca9956.cpp -o ../pca9956.o -lwiringPi -lwiringPiDev
	g++ -O2 -c ../src/pca9955.cpp -o ../pca9955.o -lwiringPi -lwiringPiDev
	g++ -O2 -c example.cpp -o example.o -lwiringPi -lwiringPiDev
	g++ -O2 ../pca9956.o ../pca9955.o example.o -o example -lwiringPi -l wiringPiDev

clean:
	rm -rf ./*.o
