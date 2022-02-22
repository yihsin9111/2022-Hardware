import serial
from time import sleep

COM_PORT = 'COM5'
BAUD_RATE = 9600
ser = serial.Serial(COM_PORT, BAUD_RATE)
LED_R = 0
LED_G = 0
LED_B = 0

while True :
    print('request LED RGB')
    ser.write(b'LED\n')
    
    while ser.in_waiting:
        RGB = ser.readline().decode().split(', ')
        LED_R = RGB[0]
        LED_G = RGB[1]
        LED_B = RGB[2]
        print("R : "+LED_R+", G : "+LED_G+", B : "+LED_B)
        