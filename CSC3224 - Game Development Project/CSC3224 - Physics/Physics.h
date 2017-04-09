#pragma once
#ifndef PHYSICS_H
#define PHYSICS_H

#include <Box2D\Box2D.h>

using namespace std;

class Physics {

private:

public:

	void createCircle(b2World& world, float x, float y, float scale);
	void createGround(b2World& world, float x, float y, float scale);

};

#endif //PHYSICS_H
