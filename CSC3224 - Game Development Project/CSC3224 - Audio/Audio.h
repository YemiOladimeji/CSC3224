#pragma once
#ifndef AUDIO_H
#define AUDIO_H

#include "SFML\Audio.hpp"

using namespace std;

class Audio{

private:
	sf::Music music; //Object for holding music streaming data
	sf::SoundBuffer buffer; //Buffer for loading in audio data
	sf::Sound sound; //Object for holding non-BGM audio data

public:
	int loadBGM(string filepath); //Function to load and play background music
	int loadSound(string filepath); //Function to load audio data into a buffer
};

#endif //Audio.h