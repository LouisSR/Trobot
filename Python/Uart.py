import serial
import time

#Initialization
ser = serial.Serial("/dev/ttyAMA0",115200)
time.sleep(1)
ser.write("UART started")
print 'UART started'

start = 'S'



def Send2Arduino(data):
#Message = start,length,data
	length = len(data)
	message = bytes(start) + bytes(length*2) + ToBytes(data)
	#print 'Message : ', message
	ser.write(message)

def ReadFromArduino():
	print "Serial:", ser.inWaiting()
	if ser.inWaiting():
		time.sleep(0.05) #Wait for incoming data
		incomingData = ser.read(ser.inWaiting())
		print incomingData
	else:
		return None

	incomingData = decode(incomingData)#check if incomming data are correct
        print "incomingDat = ", incomingData
	#ser.flushInput()
	return incomingData

def decode(string):
#Check if start byte and length are correct and return data without start and length bytes
	#print "start ",ord(string[0])
	if string[0] != start: #test if start byte is expected
		print "Start mauvais"
		return None
		
	#if ord(string[1]) != len(string)-2: #test if length byte is corresponding to data length
	#	print "Length mauvais"
	#       return None

        length = ord(string[1])
        #print "Length = ", length
        #print "Data", ord(string[2:2+length])
        data = ord(string[2])
        print "Data", string[2], data
	return data #return data (string without start and length)

def ToBytes(data):
	bytes2 = bytes(0);
	print "Data", data
	for d in data:
		high_byte = chr((d>>8) & 0xFF) # use chr() to send a binary value
		low_byte = chr(d & 0xFF)
		bytes2 = bytes2 + bytes(high_byte) + bytes(low_byte)
	return bytes2[1:] #remove the first 0

#ser.close()
