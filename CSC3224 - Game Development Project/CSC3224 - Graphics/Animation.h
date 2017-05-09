#pragma once
#ifndef ANIMATION_H
#define ANIMATION_H

#include <SFML\Graphics.hpp>
#include <vector>

class Animation{
public:
	unsigned int startFrame, endFrame;
	float duration;

	Animation(unsigned int startFrame, unsigned int endFrame, float duration);
	virtual ~Animation() {};

	inline unsigned int getLength() 
	{
		return endFrame - startFrame + 1;
	}


};

#endif