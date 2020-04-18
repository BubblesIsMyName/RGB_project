#!/usr/bin/python
# impert for correct debug and cgi
# import cgitb; cgitb.enable()
# PySerial module
# import serial
# Time module
# import time

# form = cgi.FieldStorage()

# Get data from fields
# red_colour_val = form.getvalue('red')
# green_colour_val = form.getvalue('green')
# blue_colour_val = form.getvalue('blue')
red_colour_val = "255"
green_colour_val = "60"
blue_colour_val = "100"

# Create a string to print
# String structured as follows "GREENxREDxBLUEx\n" e.g. "255x255x255x\n"
colour_string = green_colour_val+'x'+red_colour_val+'x'+blue_colour_val+'x\n'

print(colour_string)
