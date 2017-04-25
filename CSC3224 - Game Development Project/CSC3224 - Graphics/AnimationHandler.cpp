#include "AnimationHandler.h"
#include <SFML\Graphics.hpp>

AnimationHandler::AnimationHandler() 
{
	this->time = 0.0f;
	this->currentAnimation = -1;
}

AnimationHandler::AnimationHandler(const sf::IntRect &frameSize) 
{
	this->frameSize = frameSize;

	this->time = 0.0f;
	this->currentAnimation = -1;
}

void AnimationHandler::update(const float deltaTime) 
{
	if (currentAnimation >= this->animations.size() || currentAnimation < 0) 
	{
		return;
	}

	float duration = this->animations[currentAnimation].duration;

	if (int((time + deltaTime)/duration) > int(time/duration)) 
	{
		int frame = int((time + deltaTime)/duration);

		frame %= this->animations[currentAnimation].getLength();

		sf::IntRect rect = this->frameSize;
		rect.left = rect.width * frame;
		rect.top = rect.height * this->currentAnimation;
		this->bounds = rect;
	}

	this->time += deltaTime;
	if (this->time > duration * this->animations[currentAnimation].getLength()) {
		this->time = 0.0f;
	}
	return;
}

void AnimationHandler::addAnimation(Animation &anim) 
{
	this->animations.push_back(anim);
	return;
}

void AnimationHandler::changeAnimation(unsigned int animID) 
{
	if (this->currentAnimation == animID || animID >= this->animations.size() || animID < 0) {
		return;
	}
	else {
		this->currentAnimation = animID;
		sf::IntRect rect = this->frameSize;
		rect.top = rect.height * animID;
		this->bounds = rect;
		this->time = 0.0;
		return;
	}
	return;
}