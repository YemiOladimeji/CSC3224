#pragma once
#ifndef AUDIO_H
#define AUDIO_H

#include <SFML\Audio.hpp>
#include <string>
#include <iostream>

using namespace std;

class Audio {

private:
	sf::Music music;

public:
	int loadBGM(string filepath);
};

#endif //Audio
