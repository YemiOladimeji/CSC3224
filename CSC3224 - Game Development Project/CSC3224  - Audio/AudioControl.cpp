//Include statements
#include "AudioControl.h"
#include <SFML\Audio.hpp>
#include <iostream>
#include <string>

using namespace std;

int AudioControl::loadBGM(string filepath)
{
	if (!music.openFromFile(filepath)) {
		cout << "Music file could not be located.";
	}
	else {
		music.openFromFile(filepath);
		music.play();
	}
	return 0;
}
