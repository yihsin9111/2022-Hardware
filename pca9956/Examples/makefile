main:
	g++ -O2 -c ../src/pca9956.cpp -o ../obj/pca9956.o -lwiringPi -lwiringPiDev
	g++ -O2 -c ../src/pca9955.cpp -o ../obj/pca9955.o -lwiringPi -lwiringPiDev
	g++ -O2 -c example.cpp -o ../obj/example.o -lwiringPi -lwiringPiDev
	g++ -O2 -c color_test.cpp -o ../obj/color_test.o -lwiringPi -lwiringPiDev
	g++ -O2 ../obj/pca9956.o ../obj/pca9955.o ../obj/example.o ../obj/gamma_correction.o -o ../bin/example -lwiringPi -l wiringPiDev
	g++ -O2 ../obj/pca9956.o ../obj/pca9955.o ../obj/color_test.o ../obj/gamma_correction.o -o ../bin/color_test -lwiringPi -l wiringPiDev
clean:
	rm -rf ./*.o
