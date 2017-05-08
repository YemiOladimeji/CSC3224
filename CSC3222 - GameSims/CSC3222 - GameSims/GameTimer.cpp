#include "GameTimer.h"

//Function to return the startTime variable
float GameTimer::getTime()
{
	return startTime;
}

//Function to return the latestFrameTime variable
float GameTimer::getLFTime()
{
	return latestFrameTime;
}

//Function to return dt for the purposes of updating a physics loop
float GameTimer::getDeltaTime()
{
	return latestFrameTime - startTime;
}
