#!/usr/bin/env python

import serial
import sys
import autopy

if len(sys.argv) < 2:
	raise Exception("need serial port name: ex. COM6")

com_name = sys.argv[1]

port = serial.Serial(com_name, 9600)

print "Connected"

def command_key(args):
	autopy.key.tap(args[1])

while True:
	line = port.readline().rstrip()
	print line
	args = line.split(" ")
	if args[0] == "key":
		command_key(args)
		
