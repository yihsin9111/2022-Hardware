main:
	g++ -O2 -c ./src/pca9956.cpp -o ./obj/pca9956.o -lwiringPi -lwiringPiDev
	g++ -O2 -c ./src/pca9955.cpp -o ./obj/pca9955.o -lwiringPi -lwiringPiDev
	g++ -O2 -c ./src/pca2022.cpp -o ./obj/pca2022.o -lwiringPi -lwiringPiDev
	g++ -O2 -c ./src/rgba_to_rgb.h -o ./obj/rgba_to_rgb.o

	g++ -O2 -c 30fps_example.cpp -o ./obj/30fps_example.o -lwiringPi -lwiringPiDev
	g++ -O2 -c off_example.cpp -o ./obj/off_example.o -lwiringPi -lwiringPiDev
	g++ -O2 -c part_example.cpp -o ./obj/part_example.o -lwiringPi -lwiringPiDev
	g++ -O2 -c test_example.cpp -o ./obj/test_example.o -lwiringPi -lwiringPiDev

	g++ -O2 ./obj/pca2022.o ./obj/pca9956.o ./obj/pca9955.o ./obj/30fps_example.o -o ./bin/30fps_example -lwiringPi -l wiringPiDev
	g++ -O2 ./obj/pca2022.o ./obj/pca9956.o ./obj/pca9955.o ./obj/off_example.o -o ./bin/off_example -lwiringPi -l wiringPiDev
	g++ -O2 ./obj/pca2022.o ./obj/pca9956.o ./obj/pca9955.o ./obj/part_example.o -o ./bin/part_example -lwiringPi -l wiringPiDev
	g++ -O2 ./obj/pca2022.o ./obj/pca9956.o ./obj/pca9955.o ./obj/rgba_to_rgb.o ./obj/test_example.o -o ./bin/test_example -lwiringPi -l wiringPiDev
clean:
	rm -rf ./obj/*.o
	rm -rf ./bin/30fps_example
	rm -rf ./bin/part_example
	rm -rf ./bin/off_example
	rm -rf ./bin/test_example

