#import 
import time

#Initialization
#ser = serial.Serial("/dev/ttyAMA0",115200)
time.sleep(1)
#ser.write("UART started")
print 'UART started'

start = 'S'



def Send2Arduino(data):
#Message = start,length,data
	length = len(data)
	message = [start, length]
	message = message + data
	print 'Message : ', message
	#ser.write(message)

def ReadFromArduino():
	if ser.inWaiting():
		time.sleep(0.05) #Wait for incoming data
		incomingData = ser.read(ser.inWaiting())
		print incomingData
	else:
		return None

	incomingData = decode(incomingData) #check if incomming data are correct

	return incomingData

def decode(string):
#Check if start byte and length are correct and return data without start and length bytes
	if string(0) != start: #test if start byte is expected
		return None
	if string(1) != len(string)-2: #test if length byte is corresponding to data length
		return None
	return string(2:) #return data (string without start and length)


#ser.close()