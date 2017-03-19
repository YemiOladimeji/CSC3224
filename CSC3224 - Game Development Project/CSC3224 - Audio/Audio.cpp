#include "SFML\Audio.hpp"
#include "Audio.h"

Audio::Audio() { //Default constructor

}

int Audio::loadBGM(string filepath)
{
	if (!music.openFromFile(filepath)) {
		return -1; //Return an error
	}
	else {
		music.openFromFile(filepath);
		music.play();
	}
	return 0;
}

int Audio::loadSound(string filepath)
{
	if (!buffer.loadFromFile(filepath)) {
		return -1;
	}
	else {
		sound.setBuffer(buffer);
		sound.play();
	}
	return 0;
}
