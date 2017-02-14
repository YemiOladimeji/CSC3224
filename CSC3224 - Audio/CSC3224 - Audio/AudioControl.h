//Document management
#pragma once
#ifndef AUDIOCONTROL_H
#define AUDIOCONTROL_H

//Include statements
#include <SFML\Audio.hpp>
#include <string>
#include <iostream>

using namespace std;

class AudioControl {

private:
	sf::Music music;

public:
	int loadBGM(string filepath);
};


#endif //AudioControl