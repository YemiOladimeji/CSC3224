#pragma once
#ifndef GAMETIMER_H
#define GAMETIMER_H

#include <Windows.h>

class GameTimer 
{

public:
	void initialise();

private:
	LARGE_INTEGER freq;

public:
	GameTimer(); //Default constructor
	virtual ~GameTimer() {}; //Destructor

	void start(); //Function to start the timer
	void stop(); //Function to stop the timer

	float absTime();
	float latestFrameTime();
	float getFrameTime();

private:
	LARGE_INTEGER startTime;
	float lFT;
	bool running;
};

#endif GAMETIMER_H