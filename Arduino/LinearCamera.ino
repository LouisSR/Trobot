int LinearCam(void)
{
	int LinCamPeak = 0;
	// must be called to fetch data from the linear camera
  	LinCam.getPixels();
  	// this will process the local linear camera data and find the peak position between 0 and 101
	// if the value is 51 it means the peak is straight ahead
	LinCamPeak = LinCam.getPeak();
	LinCamPeak = map(LinCamPeak, 0,101,-100,100);
	return (LinCamPeak);
}
