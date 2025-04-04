#-*- coding: utf-8 -*-
#lisbp.py

import sys, serial, time

data = ""
portUSB = "/dev/ttyUSB0"
ser = serial.Serial(portUSB,baudrate=115200, dsrdtr=False)
time.sleep(1.5)

for arg in sys.argv:

    if arg == "auto":
        data = "auto\r\n"
    
    elif arg == "manual":
        data = "manual\r\n"

encoded_data = data.encode("utf-8")
ser.write(encoded_data)
