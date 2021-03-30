main:
	g++ pca9956.cpp -l wiringPi
	g++ pca9956_LED.cpp -l wiringPi

test:
	g++ test1239.cpp -l wiringPi -o test1239
clean:
	rm -rf ./pca9956
	rm -rf ./pca9956_LED
	rm -rf ./test1239
	rm -rf ./*.o
