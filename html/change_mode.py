#-*- coding: utf-8 -*-
#lisbp.py

import sys, serial, time

data = ""
portUSB = "/dev/ttyUSB0"
ser = serial.Serial(portUSB,baudrate=115200, dsrdtr=False)
time.sleep(2)

for arg in sys.argv:

    if arg == "auto":
        data = "auto"
    
    elif arg == "manual":
        data = "manual"

encoded_data = data.encode("utf-8")
ser.write(encoded_data)
ligne = ser.readline()
strlignes = ligne.decode("utf-8")
print(strlignes)
"""va falloir mettre ça dans une db"""