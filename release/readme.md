## Installing WiringPi library

RPi 4 should contain WiringPi library itself, **but it is not up to date**.
Please follow the instructions below to install the lastest version of the library.
1. Run `gpio -v` to check what version you have.
2. If you receive `gpio: command not found`, please jump to step 6.
3. If you receive an output similar to the following with the `Unknown 17`, you need to update the library on your RPi. Please follow step 4 to 8.
    ```
    gpio version: 2.50
    Copyright (c) 2012-2018 Gordon Henderson
    This is free software with ABSOLUTELY NO WARRANTY.
    For details type: gpio -warranty　　　　　　　　　　　　　　　　　　　　
    Raspberry Pi Details:
        Type: Unknown17, Revision: 02, Memory: 0MB, Maker: Sony
            * Device tree is enabled.
            * --> Raspberry Pi 4 Model B Rev 1.2
            * This Raspberry Pi supports user-level GPIO access.
    ```
4. Run `sudo apt-get purge wiringpi` to remove wiringPi and configuration files.
5. Run `hash -r` to remove all locations that remember wiringPi.
6. Run `git clone https://github.com/WiringPi/WiringPi.git` to download.
7. Run 
    `cd WiringPi`
    `git pull origin`
    `./build`
8. Run `gpio -v` to check if the version has updated. The gpio version should be 2.61.

## LED
1. Declare the number of leds of every strip as a `vector<uint16_t>`, which is the vector `nLeds` in `example.cpp`.
2. Initialize and send the length of strips to stm32 by calling `LED_Strip strips(nLeds);`
3. Declare color data as `vector< vector<char> >`, which is `buf` in `example.cpp`. The size of the color data should be ∑ strip[i]×(number of leds of strip[i])×3.
5. Use for loop to set every color of every leds. The order is green, red, blue.
6. Send the color data to stm32 by calling `strips.sendToStrip(buf);`
7. Wait for stm32 to deal with the data by stopping the program, calling `usleep(27 * 1000);.`