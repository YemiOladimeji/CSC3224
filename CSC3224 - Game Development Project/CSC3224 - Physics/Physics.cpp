#include "Physics.h"


Physics::Physics() { //Default constructor

}

void Physics::createPlayerBody(b2World & world, float x, float y, float scale, float radius) //Function to create a circle body in the physics system (for the player character)
{
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position = b2Vec2(x/scale, y/scale);
	bodyDef.userData = "Player";
	b2Body* body = world.CreateBody(&bodyDef);

	b2CircleShape player;
	player.m_radius = radius/scale;

	b2FixtureDef fixtureDef;
	fixtureDef.density = 10.0f;
	fixtureDef.friction = 0.4f;
	fixtureDef.restitution = 0.0f;
	fixtureDef.shape = &player;

	body->CreateFixture(&fixtureDef);
}

void Physics::createEnemyBody(b2World & world, float x, float y, float scale, float radius) //Function to create a circle body in the physics system (for the player character)
{
	b2BodyDef bodyDef;
	bodyDef.type = b2_kinematicBody;
	bodyDef.position = b2Vec2(x/scale, y/scale);
	bodyDef.userData = "Enemy";
	b2Body* body = world.CreateBody(&bodyDef);

	b2CircleShape enemy;
	enemy.m_radius = radius/scale;

	b2FixtureDef fixtureDef;
	fixtureDef.density = 5.0f;
	fixtureDef.friction = 0.4f;
	fixtureDef.restitution = 0.0f;
	fixtureDef.shape = &enemy;

	body->CreateFixture(&fixtureDef);
}


void Physics::createGround(b2World & world, float x, float y, float scale, float height, float width) //Function to create a polygon body for the static platforms
{
	b2BodyDef bodyDef;
	bodyDef.type = b2_staticBody;
	bodyDef.position = b2Vec2(x/scale, y/scale);
	bodyDef.userData = "Platform";
	b2Body* body = world.CreateBody(&bodyDef);

	b2PolygonShape platform;
	platform.SetAsBox((width/2)/scale, (height/2)/scale);

	b2FixtureDef fixtureDef;
	fixtureDef.density = 1.f;
	fixtureDef.friction = 1.f;
	fixtureDef.restitution = 0.0f;
	fixtureDef.shape = &platform;

	body->CreateFixture(&fixtureDef);
}
