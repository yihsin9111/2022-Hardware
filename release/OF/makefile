main:
	g++ -O2 -c ./src/pca9956.cpp -o ./obj/pca9956.o -lwiringPi -lwiringPiDev
	g++ -O2 -c ./src/pca9955.cpp -o ./obj/pca9955.o -lwiringPi -lwiringPiDev
	g++ -O2 -c ./src/pca2022.cpp -o ./obj/pca2022.o -lwiringPi -lwiringPiDev
	g++ -O2 -c ./src/example.cpp -o ./obj/example.o -lwiringPi -lwiringPiDev
	g++ -O2 ./obj/pca2022.o ./obj/pca9956.o ./obj/pca9955.o ./obj/example.o -o ./bin/example -lwiringPi -l wiringPiDev
