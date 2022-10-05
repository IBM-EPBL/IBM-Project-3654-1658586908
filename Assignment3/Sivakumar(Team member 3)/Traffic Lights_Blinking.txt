import RPI.GPIO as GPIO
from time import sleep

GPIO.setmode(GPIO.BOARD)   //setting RPi in BOARD mode

north_dir = (16,18,22)     //initializing board pins to represent NSEW direction LED's
south_dir = (11,13,15)
east_dir = (29,31,33)
west_dir = (36,38,40)

GPIO.setup(north_dir,GPIO.OUT)     // setting all pins in output mode
GPIO.setup(soth_dir,GPIO.OUT)
GPIO.setup(east_dir,GPIO.OUT)
GPIO.setup(west_dir,GPIO.OUT)

while True:
	GPIO.output(north_dir,(1,0,0))    //Setting RED LEDs ON in north and south directions and GREEN LEDs ON in east and west directions...
	GPIO.output(south_dir,(1,0,0))
	GPIO.output(east_dir,(0,0,1))
	GPIO.output(west_dir,(0,0,1))

	sleep(10)

	GPIO.output(north_dir,(0,1,0))    // Setting YELLOW LEDs ON in all directions
	GPIO.output(south_dir,(0,1,0))
	GPIO.output(east_dir,(0,1,0))
	GPIO.output(west_dir,(0,1,0))

	sleep(10)

	
	GPIO.output(north_dir,(0,0,1))    //Setting GREEN LEDs ON in north and south directions and RED LEDs ON in east and west directions...
	GPIO.output(south_dir,(0,0,1))
	GPIO.output(east_dir,(1,0,0))
	GPIO.output(west_dir,(1,0,0))

	sleep(10)