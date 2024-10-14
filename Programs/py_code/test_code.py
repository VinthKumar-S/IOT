import serial
import time


arduino = serial.Serial(port='COM4',baudrate=115200,timeout=.1)

time.sleep(2)

while True:
    data = arduino.readline().decode('utf-8').strip()
    if data:
        print("Received from Arduino",data)
    time.sleep(1)
