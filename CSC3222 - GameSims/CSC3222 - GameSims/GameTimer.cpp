#include "GameTimer.h"

//Creates an instance of a stopped timer
GameTimer::GameTimer() : running(false)
{
}

//Initialises the timer
void GameTimer::initialise()
{
	QueryPerformanceFrequency(&freq);
}

//Function to start the timer
void GameTimer::start()
{
	running = true;
	QueryPerformanceCounter(&startTime);
}

//Function to stop the timer
void GameTimer::stop()
{
	running = false;
}

//Function which gets the time since the timer srtarted
float GameTimer::absTime()
{
	LARGE_INTEGER t;
	QueryPerformanceCounter(&t);
	return (float)((t.QuadPart - startTime.QuadPart) * 1000.0f / freq.QuadPart);
}

//Function which returns the latest frame time
float GameTimer::latestFrameTime()
{
	return absTime() - lFT;
}

//Function which returns the time since the last frame
float GameTimer::getFrameTime()
{
	float t = absTime();
	float dt = t - lFT;
	lFT = absTime();
	return dt;
}


