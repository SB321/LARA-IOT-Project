#libraries for cloud connection
import httplib
import urllib

#libraries for stepper motor
import RPi.GPIO as GPIO
from time import sleep
import sys

#library for moisture sensor
import spidev 			# To communicate with SPI devices
from numpy import interp 	# To scale values
from time import sleep  	# To add delay

#define a API key
myAPI = "EMQV6MK21W3F4MHJ"
baseURL = 'https://api.thingspeak.com/update?api_key=%s' % myAPI 

#assign GPIO pins for motor
motor_channel = (29,31,33,35)  
GPIO.setwarnings(False)
GPIO.setmode(GPIO.BOARD)
#for defining more than 1 GPIO channel as input/output use
GPIO.setup(motor_channel, GPIO.OUT)



# Start SPI connection
spi = spidev.SpiDev() # Created an object
spi.open(0,0) 

channel=0
# Read MCP3008 data
def analogInput(channel):
  spi.max_speed_hz = 1350000
  adc = spi.xfer2([1,(8+channel)<<4,0])
  data = ((adc[1]&3) << 8) + adc[2]
  return data

#set flag for motor status
flag=0
#Initially read the output from CH0
output = analogInput(0) 

#method for uploading data 
def thingspeak():

         f = urllib.urlopen(baseURL + "&field1=%s&field2=%s" % (Moisture, flag))
         sleep(0.1)

        
        
while True:
        
        output = analogInput(0) # Reading from CH0
	#convert it into percentage
        Moisture = interp(output, [0, 1023], [100, 0])
        Moisture = int(Moisture)
	#print moisture
        print("Moistue : "+str(Moisture) )
        
	#if moisture is less than 35 % then start the motor 
        if Moisture < 35:
            flag=1
            GPIO.output(motor_channel, (GPIO.HIGH,GPIO.LOW,GPIO.LOW,GPIO.HIGH))
            sleep(0.01)
            GPIO.output(motor_channel, (GPIO.HIGH,GPIO.HIGH,GPIO.LOW,GPIO.LOW))
            sleep(0.01)
            GPIO.output(motor_channel, (GPIO.LOW,GPIO.HIGH,GPIO.HIGH,GPIO.LOW))
            sleep(0.01)
            GPIO.output(motor_channel, (GPIO.LOW,GPIO.LOW,GPIO.HIGH,GPIO.HIGH))
            sleep(0.01)          
        else:
            flag=0
	#upload on thingspeak
        thingspeak()
        


    
