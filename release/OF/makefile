main:
	g++ -O2 -c ./src/pca.cpp -I./include -o ./obj/pca.o -lwiringPi -lwiringPiDev
	g++ -O2 -c ./src/pca995X.cpp -I./include -o ./obj/pca995X.o -lwiringPi -lwiringPiDev
	g++ -O2 -c ./include/pcaDefinition.h -o ./obj/pcaDefinition.o
	g++ -O2 -c ./include/OFrgba_to_bgriref.h -o ./obj/OFrgba_to_bgriref.o
	g++ -O2 -c ./example/example.cpp -I./include -o ./obj/example.o -lwiringPi -lwiringPiDev
	g++ -O2 ./obj/pca.o ./obj/pca995X.o ./obj/example.o -I./include -o ./bin/example -lwiringPi -l wiringPiDev
