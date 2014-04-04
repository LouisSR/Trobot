//Declaration in IR-sensor.h

void readDistanceIR(unsigned int range[NB_IR_DISTANCE_SENSOR])
{
    unsigned int value;
    unsigned int i;
    
    digitalWrite(ENABLE_MUX, LOW);//Enable Multiplexers
    digitalWrite(VDD_IRLED, HIGH);//Turn on VDD of IR sensors
    
    for( i=0; i<NB_IR_DISTANCE_SENSOR; i++)
    {
        selectMultiplexer(IR_sensor[i]); //Select the sensor to read
        //Wait during capacitor charging ?
        delay(1);
        value = analogRead(IR_SENSOR_OUTPUT);     // read the value from the sensors
        //myPrint(i);
        //myPrint(IR_sensor[i]);
        //myPrint(value);
        range[i] = multiMap(value, 0);            // interpolate to find the distance
    }
    
    //digitalWrite(VDD_IRLED, LOW);//Turn off VDD of IR sensors
    // digitalWrite(ENABLE_MUX, HIGH);//Disable multiplexer
}

unsigned int readGroundColor(void)
{
    unsigned int color;
    unsigned int value;
    
    digitalWrite(ENABLE_MUX, LOW);//Enable Multiplexers
    digitalWrite(VDD_IRLED, HIGH);//Turn on VDD of IR sensors
    selectMultiplexer(GROUND_COLOR_SENSOR); //Select the sensor to read
    //Wait during capacitor charging ?
    delay(1);
    value = analogRead(IR_SENSOR_OUTPUT);     // read the value from the sensors
    digitalWrite(VDD_IRLED, LOW);//Turn off VDD of IR sensors
    digitalWrite(ENABLE_MUX, HIGH);//Disable multiplexer
    
    if(value < BLACK_GROUND)
    {
        color = BLACK;
    }
    else if (value>WHITE_GROUND)
    {
        color = WHITE;
    }
    else
    {
        color = GREY;
    }
    //return(value);
    return(color);
}

unsigned int readStartLED(void)
{
    unsigned int status;
    unsigned int value;
    
    digitalWrite(ENABLE_MUX, LOW);//Enable Multiplexers
    digitalWrite(VDD_IRLED, LOW);//Optional: should already be off. Turn off VDD of IR sensors
    selectMultiplexer(START_LED); //Select the sensor to read
    //Wait during capacitor charging ?
    delay(1);
    value = analogRead(IR_SENSOR_OUTPUT);  // read the value from the sensors
    digitalWrite(ENABLE_MUX, HIGH);//Disable multiplexer
    //Serial.println(value);
    if(value < START_LED_OFF)
    {
        status = 0; //OFF
    }
    else if (value>START_LED_ON)
    {
        status = 1; //ON
    }
    else
    {
        status = 2; //Not sure
    }
    return(status);
}

boolean CubeDetect(void)
{
    unsigned int status;
    unsigned int value_low, value_high;
    
    digitalWrite(ENABLE_MUX, LOW);//Enable Multiplexers
    digitalWrite(VDD_IRLED, HIGH);//Optional: should already be off. Turn off VDD of IR sensors
    selectMultiplexer(CUBE_DETECTION_LOW); //Select the sensor to read
    //Wait during capacitor charging ?
    delay(1);
    value_low = analogRead(IR_SENSOR_OUTPUT);  // read the value from the sensors
    
    selectMultiplexer(CUBE_DETECTION_HIGH); //Select the sensor to read
    delay(1);
    value_high = analogRead(IR_SENSOR_OUTPUT);  // read the value from the sensors
    
    digitalWrite(VDD_IRLED, LOW);//Optional: should already be off. Turn off VDD of IR sensors
    digitalWrite(ENABLE_MUX, HIGH);//Disable multiplexer
    
    //myPrint( value_low );
    //myPrint( value_high);
    
    if(value_high > CUBE_DETECTED || value_low > CUBE_DETECTED)
    {
        status = 1; //cube in gripper
    }
    else
    {
        status = 0; //no cube
    }
    
    //myPrint(status);
    //Serial.println();
    return(status);
}

void selectMultiplexer(byte channel)
/*Select channel: 0-15*/
{
    // digitalWrite( MUX_S0, HIGH );
    // digitalWrite( MUX_S1, LOW);
    // digitalWrite( MUX_S2, HIGH );
    // digitalWrite( MUX_S3, HIGH );
    // myPrint(234234);
    
    digitalWrite( MUX_S0, (channel & B00001) );
    //myPrint(channel & B00001);
    digitalWrite( MUX_S1, (channel & B00010) );
    //myPrint(channel & B00010);
    digitalWrite( MUX_S2, (channel & B00100) );
    //myPrint(channel & B00100);
    digitalWrite( MUX_S3, (channel & B01000) );
    //myPrint(channel & B01000);
}

unsigned int multiMap(unsigned int val, int sensor)
{
    // take care the value is within range
    // val = constrain(val, _in[0], _in[size-1]);
    int column = sensor+1;
    if (val <= tab[0][column]) return tab[0][0];
    if (val >= tab[tab_size-1][column]) return tab[tab_size-1][0];
    
    // search right interval
    uint8_t pos = 1;  // _in[0] allready tested
    while(val > tab[pos][column]) pos++;
    
    // this will handle all exact "points" in the _in array
    if (val == tab[pos][column]) return tab[pos][0];
    
    // interpolate in the right segment for the rest
    return map(val, tab[pos-1][column], tab[pos][column], tab[pos-1][0], tab[pos][0]);
} 
