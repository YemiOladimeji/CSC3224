#pragma once
#ifndef ANIMATION_HANDLER_H
#define ANIMATION_HANDLER_H

#include "Animation.h"

class AnimationHandler 
{
public:

	AnimationHandler(); //Default constructor
	AnimationHandler(const sf::IntRect &frameSize); //Parameterised constructor
	virtual ~AnimationHandler() {}; //Destructor

	sf::IntRect bounds, frameSize; //IntRect objects for handling the current section of the texture to display and the pixel dimensions of each frame

	void update(const float deltaTime); //Function to update the current frame of animation
	void addAnimation(Animation &anim); //Method to add a new animation
	void changeAnimation(unsigned int animNum); //Method to change the animation, resetting the timer as a result

private:
	std::vector<Animation> animations; //Vector data structure used to hold animations
	float time; //Float to hold the current time since the animation started
	int currentAnimation; //Integer which holds the current frame of the animation playing
};

#endif // ANIMATION_HANDLER_H
