//Declaration in IR-sensor.h

void readDistanceIR(unsigned int range[NB_IR_DISTANCE_SENSOR])
{
  unsigned int value;
   
   digitalWrite(ENABLE_MUX, HIGH);//Enable Multiplexers
   digitalWrite(VDD_IRLED, HIGH);//Turn on VDD of IR sensors

  for(int i=0; i<NB_IR_DISTANCE_SENSOR; i++)
  {
    selectMultiplexer(i); //Select the sensor to read
    //Wait during capacitor charging ?
    value = analogRead(IR_SENSOR_OUTPUT);     // read the value from the sensors
    range[i] = multiMap(value, 0);            // interpolate to find the distance
  } 
  digitalWrite(VDD_IRLED, LOW);//Turn off VDD of IR sensors
  digitalWrite(ENABLE_MUX, LOW);//Disable multiplexer
}

unsigned int readGroundColor(void)
{
  unsigned int color;
  unsigned int value;

  digitalWrite(ENABLE_MUX, HIGH);//Enable Multiplexers
  digitalWrite(VDD_IRLED, HIGH);//Turn on VDD of IR sensors
  selectMultiplexer(GROUND_COLOR_SENSOR); //Select the sensor to read
  //Wait during capacitor charging ?
  value = analogRead(IR_SENSOR_OUTPUT);     // read the value from the sensors
  digitalWrite(VDD_IRLED, LOW);//Turn off VDD of IR sensors
  digitalWrite(ENABLE_MUX, LOW);//Disable multiplexer
  
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
  
  return(color);
} 

unsigned int readStartLED(void)
{
  unsigned int status;
  unsigned int value;

  digitalWrite(ENABLE_MUX, HIGH);//Enable Multiplexers
  digitalWrite(VDD_IRLED, LOW);//Optional: should already be off. Turn off VDD of IR sensors
  selectMultiplexer(START_LED); //Select the sensor to read
  //Wait during capacitor charging ?
  value = analogRead(IR_SENSOR_OUTPUT);  // read the value from the sensors
  digitalWrite(ENABLE_MUX, LOW);//Disable multiplexer
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

void selectMultiplexer(byte channel)
/*Select channel: 0-15*/
{
  digitalWrite( S0, (channel & 0001) );
  digitalWrite( S1, (channel & 0010) );
  digitalWrite( S2, (channel & 0100) );
  digitalWrite( S3, (channel & 1000) );
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