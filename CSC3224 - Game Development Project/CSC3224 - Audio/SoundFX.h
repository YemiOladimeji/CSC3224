#pragma once
#ifndef SOUNDBYTE_H
#define SOUNDBYTE_H

#include <SFML\Audio.hpp>
#include <map>

using namespace std;

class SoundFX 
{
public:
public:
	SoundFX(); //Default constructor
	virtual ~SoundFX() {}; //Deconstructor

	void loadSound(const string &name, const string &filepath); //Function to load a music file for usage as background music
	sf::SoundBuffer &getSoundRef(const string &audio); //Function to fetch the specified music file

private:
	sf::SoundBuffer sfx; //SFML music object	
	map<string, sf::SoundBuffer> audio; //Map of audio files

};
#endif // !SOUNDBYTE_H
