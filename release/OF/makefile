main:
	g++ -O2 -c ./src/pca9956.cpp -o ./obj/pca9956.o -lwiringPi -lwiringPiDev
	g++ -O2 -c ./src/pca9955.cpp -o ./obj/pca9955.o -lwiringPi -lwiringPiDev
	g++ -O2 -c ./src/pca.cpp -o ./obj/pca.o -lwiringPi -lwiringPiDev
	g++ -O2 -c ./include/pcaDefinition.h -o ./obj/pcaDefinition.o
	g++ -O2 -c ./include/OFrgba_to_rgbiref.h -o ./obj/OFrgba_to_rgbiref.o
	g++ -O2 -c ./example/example.cpp -o ./obj/example.o -lwiringPi -lwiringPiDev
	g++ -O2 ./obj/pca.o ./obj/pca9956.o ./obj/pca9955.o ./obj/example.o -o ./bin/example -lwiringPi -l wiringPiDev
