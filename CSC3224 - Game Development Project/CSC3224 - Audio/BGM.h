#pragma once
#ifndef AUDIO_H
#define AUDIO_H

#include "SFML\Audio.hpp"

using namespace std;

class BGM{

private:
	sf::Music bgm; //Object for holding music streaming data

public:
	BGM(); //Default constructor
	~BGM() {}; //Destructor
	int loadBGM(string filepath); //Function to load and play background music	
};

#endif //Audio.h