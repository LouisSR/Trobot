/*
 Serial communication:
 message: Start byte, data length, data
 RX: pin 0
 TX: pin 1
 Use Serial to communicate through USB
 Use Serial1 to communicate through pins 0-1
 */

char start_byte = 'S';

void Send2Raspberry(unsigned int* data, unsigned int data_length)
{
	unsigned int message_length = 2+data_length;
  	byte message[message_length];
    
 	message[0]=byte(start_byte);
 	message[1]=byte(data_length);
	for(int i=0;i<data_length;i++)//fill the buffer with the message
	{
	    message[i+2]=byte(data[i]);
	}
	Serial1.write(message, message_length);
	Serial.print("Message: "); // print for control on computer
	Serial.write(message, message_length);
	Serial.println();
}

boolean ReceiveFromRaspberry(unsigned int* distance, int* angle, unsigned int* color)
{
	unsigned int length = 6;
	byte buffer[length];
	boolean good_transmission=false;
    
	if (SerialReceive(buffer, length))
	{
		*distance = word(buffer[0],buffer[1]);
		*angle = word(buffer[2],buffer[3]);
		*color = word(buffer[4],buffer[5]);
		good_transmission = true;
	}
	
	return good_transmission;
	
}

boolean SerialReceive(byte* buffer, unsigned int length)
{
	boolean data_ready = false; //True if start byte is detected
	boolean data_read = false; // True if correct string has been read
	unsigned int timeout = 100; // Number of while loop before timeout
    
	//Serial or Serial1 ???????
	while(Serial1.available()!= 0 && data_ready==false && timeout) //search for the start byte
	{
		if (Serial1.read()== start_byte )
		{
			data_ready = true;
		}
		else
		{
			data_ready = false;
		}
		timeout--;
	}
    
	if(data_ready==true)
	{
		delay(10);
		if (Serial1.available()>0)
		{
			Serial1.read(); //discard length byte
            
			if (Serial1.available() >= length)
			{
				for (int i=0; i<length; i++)
				{
					buffer[i] = Serial1.read();
				}
				data_read = true;
			}
		}
	}
    
	Serial1.flush();
	return(data_read);
}