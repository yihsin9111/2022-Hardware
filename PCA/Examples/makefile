main:
	g++ -O2 -c ../src/pca995X.cpp -o ../obj/pca995X.o -lwiringPi -lwiringPiDev
	g++ -O2 -c ../src/pca.cpp -o ../obj/pca.o -lwiringPi -lwiringPiDev
	g++ -O2 -c ../include/pcaDefinition.h -o ../obj/pcaDefinition.o
	g++ -O2 -c ../include/OFrgba_to_rgbiref.h -o ../obj/OFrgba_to_rgbiref.o
	g++ -O2 -c ../src/gamma_correction.cpp -o ../obj/gamma_correction.o
	g++ -O2 -c 30fps_example.cpp -o ../obj/30fps_example.o -lwiringPi -lwiringPiDev
	g++ -O2 -c part_example.cpp -o ../obj/part_example.o -lwiringPi -lwiringPiDev
	g++ -O2 -c off_example.cpp -o ../obj/off_example.o -lwiringPi -lwiringPiDev
	g++ -O2 -c test_example.cpp -o ../obj/test_example.o -lwiringPi -lwiringPiDev
	g++ -O2 ../obj/pca.o ../obj/pca995X.o  ../obj/30fps_example.o -o ../bin/30fps_example -lwiringPi -l wiringPiDev
	g++ -O2 ../obj/pca.o ../obj/pca995X.o  ../obj/part_example.o -o ../bin/part_example -lwiringPi -l wiringPiDev
	g++ -O2 ../obj/pca.o ../obj/pca995X.o  ../obj/off_example.o -o ../bin/off_example -lwiringPi -l wiringPiDev
	g++ -O2 ../obj/pca.o ../obj/pca995X.o  ../obj/test_example.o -o ../bin/test_example -lwiringPi -l wiringPiDev
	
clean:
	rm -rf ../obj/*.o
	rm -rf ../bin/color_test
	rm -rf ../bin/test
	rm -rf ../bin/example
	rm -rf ../bin/30fps_example
	rm -rf ../bin/part_example
	rm -rf ../bin/off_example
	rm -rf ../bin/test_example

