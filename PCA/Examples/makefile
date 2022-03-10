main:
	g++ -O2 -c ../src/pca9956.cpp -o ../obj/pca9956.o -lwiringPi -lwiringPiDev
	g++ -O2 -c ../src/pca9955.cpp -o ../obj/pca9955.o -lwiringPi -lwiringPiDev
	g++ -O2 -c ../src/pca2022.cpp -o ../obj/pca2022.o -lwiringPi -lwiringPiDev
	g++ -O2 -c ../include/definition.h -o ../obj/definition.o
	g++ -O2 -c ../include/rgba_to_rgb.h -o ../obj/rgba_to_rgb.o
	g++ -O2 -c ../src/gamma_correction.cpp -o ../obj/gamma_correction.o
	g++ -O2 -c 30fps_example.cpp -o ../obj/30fps_example.o -lwiringPi -lwiringPiDev
	g++ -O2 ../obj/pca2022.o ../obj/pca9956.o ../obj/pca9955.o ../obj/30fps_example.o -o ../bin/30fps_example -lwiringPi -l wiringPiDev
	
clean:
	rm -rf ../obj/*.o
	rm -rf ../bin/color_test
	rm -rf ../bin/test
	rm -rf ../bin/example
	rm -rf ../bin/30fps_example
	rm -rf ../bin/part_example
	rm -rf ../bin/off_example
	rm -rf ../bin/test_example

