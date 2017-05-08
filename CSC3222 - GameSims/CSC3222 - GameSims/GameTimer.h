#pragma once
#ifndef GAMETIMER_H
#define GAMETIMER_H

class GameTimer 
{
private:
	float startTime, latestFrameTime;

public:
	float getTime(); //Function to return the startTime variable
	float getLFTime(); //Function to return the latestFrameTime variable
	float getDeltaTime(); //Function to return dt for the purposes of updating a physics loop
};

#endif GAMETIMER_H