#include "Audio.h"
#include <iostream>
#include <string>

using namespace std;

int Audio::loadBGM(string filepath) {
	if (!music.openFromFile(filepath)) {
		cout << "Music file could not be located.";
	}
	else {
		music.openFromFile(filepath);
		music.play();
	}
	return 0;
}