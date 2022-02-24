#include <iostream>
#include "SerialClass.h"

int main(int argc, char* argv[]){
    Serial* arduino = new Serial("\\\\.\\COM5");
}