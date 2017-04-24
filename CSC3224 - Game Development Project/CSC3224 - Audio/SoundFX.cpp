#include "SoundFX.h"

using namespace std;
#include <iostream>

SoundFX::SoundFX() //Default constructor
{

}

void SoundFX::loadSound(const string &name, const string &filepath) { //Function to load SFX files to be played by a SoundBuffer object
	if (!sfx.loadFromFile(filepath)) {
		cout << "Error: Could not open file."; //Output an error message when the file fails to load
	}
	else {
		sfx.loadFromFile(filepath); //Load the sound file into the buffer
		this->audio[name] = sfx; //Add the loaded sound buffer into the map
		return;
	}
	return;
}

sf::SoundBuffer &SoundFX::getSoundRef(const string &sound) {
	return this->audio.at(sound); //Return a reference to the sound buffer with matching name
}