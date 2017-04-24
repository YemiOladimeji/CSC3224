#include "BGM.h"

BGM::BGM() { //Default constructor

}

int BGM::loadBGM(string filepath)
{
	if (!bgm.openFromFile(filepath)) {
		return -1; //Return an error
	}
	else {
		bgm.openFromFile(filepath);
		bgm.play();
	}
	return 0;
}