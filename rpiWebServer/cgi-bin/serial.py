#!/usr/bin/python

import serial
ser = serial.Serial("/dev/ttyUSB0")
ser.is_open
print(ser.name)
#red_var = 100
#green_var = 100
#blue_var = 100

ser.write("255x0x0x\n") #green colour should appear
ser.close()
