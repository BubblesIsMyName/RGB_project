#!/usr/bin/python
# impert for correct debug and cgi
import cgi, cgitb 
cgitb.enable()
# PySerial module
import serial
# Time module
import time

form = cgi.FieldStorage()

# Get data from fields
red_colour_val = form.getvalue('red')
green_colour_val = form.getvalue('green')
blue_colour_val = form.getvalue('blue')

# Create a string to print
# String structured as follows "GREENxREDxBLUEx\n" e.g. "255x255x255x\n"
colour_string = green_colour_val+'x'+red_colour_val+'x'+blue_colour_val+'x\n'

# Establish serial connection
ser = serial.Serial("/dev/ttyUSB0")
# print(ser.is_open)
time.sleep(1) #pause
# Write to Arduino
ser.write(colour_string)
time.sleep(2) #pause
ser.close()

print "Content-type:text/html\r\n\r\n"
print "<html>"
print "<head>"
print "<title>Is it the right colour?</title>"
print "</head>"
print "<body>"
print "<h2>colour codes red = %s green = %s blue = %s </h2>" % (red_colour_val, green_colour_val, blue_colour_val)
print "</body>"
print "</html>"