int LinearCam(void)
{
    //Return negative value when light comes from the top of the board
	static int LinCamPeak_previous=-100, LinCamPeak=-100;
	int LinCamPeak_after = 0;
	// must be called to fetch data from the linear camera
  	LinCam.getPixels();
  	// this will process the local linear camera data and find the peak position between 0 and 101
	// if the value is 51 it means the peak is straight ahead
	//Serial.print( LinCam.getMax()-LinCam.getAverage() );
    //Serial.print( LinCam.getMax() );
    
	LinCamPeak_after = LinCam.getPeak();
	LinCamPeak_after = map(LinCamPeak_after, 0,101,-100,100);
    
	if( LinCamPeak != -100)
	{
		if(LinCamPeak_after == -100 && LinCamPeak_previous == -100)
		{
			LinCamPeak = -100;
			//Serial.print("Valeur modifiee ");
		}
        
	}
	//Serial.print( LinCamPeak_previous );
	//Serial.print("    ");
	//Serial.println( LinCamPeak );
	//Serial.print("    ");
	//Serial.println( LinCamPeak_after );
    
	LinCamPeak_previous = LinCamPeak;
	LinCamPeak = LinCamPeak_after;
    
	return (LinCamPeak);
}

void FollowLight(void)
{
	int CamPeak, PeakValue;
    
	CamPeak = LinearCam();
    //PeakValue=(LinCam.getMax()-LinCam.getAverage());
    PeakValue=(LinCam.getMax());
    //Serial.println(LinCam.getMax());
	if(CamPeak != -100 && PeakValue > 100)
	{
		//Move(25,CamPeak/4);
		//Serial.println(CamPeak);
        
		
        Move(80,CamPeak);
        //Serial.println("Tout droit");
        
		
		
	}
	else
	{
		Move(0, 30);
		//(Serial.println("No Peak");
        //penser a faire en sorte qu'il tourne tout seul du bon côté en fonction de l'erreur systématique qu'il fait
	}
}