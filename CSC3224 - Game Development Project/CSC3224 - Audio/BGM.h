#pragma once
#ifndef AUDIO_H
#define AUDIO_H

#include "SFML\Audio.hpp"

using namespace std;

class BGM
{
public:
	BGM(); //Default constructor
	virtual ~BGM() {}; //Destructor
	int loadBGM(string filepath); //Function to load and play background music	

private:
	sf::Music bgm; //Object for holding music streaming data
};

#endif //Audio.h