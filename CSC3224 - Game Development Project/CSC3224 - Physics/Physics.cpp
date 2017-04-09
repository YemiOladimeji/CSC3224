#include "Physics.h"

void Physics::createCircle(b2World & world, float x, float y, float scale)
{
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position = b2Vec2(x/scale, y/scale);
	bodyDef.userData = "Circle";
	b2Body* body = world.CreateBody(&bodyDef);

	b2CircleShape circle;
	circle.m_radius = 0.5f / scale;

	b2FixtureDef fixtureDef;
	fixtureDef.density = 10.0f;
	fixtureDef.friction = 0.4f;
	fixtureDef.restitution = 0.2f;
	fixtureDef.shape = &circle;

	body->CreateFixture(&fixtureDef);
}

void Physics::createGround(b2World & world, float x, float y, float scale)
{
	b2BodyDef bodyDef;
	bodyDef.type = b2_staticBody;
	bodyDef.position = b2Vec2(x/scale, y/scale);
	bodyDef.userData = "Platform";
	b2Body* body = world.CreateBody(&bodyDef);

	b2PolygonShape platform;
	platform.SetAsBox((32.f/2)/scale, (32.f/2)/scale);
	b2FixtureDef fixtureDef;
	fixtureDef.density = 5.f;
	fixtureDef.friction - 5.0f;
	fixtureDef.restitution = 0.0f;
	fixtureDef.shape = &platform;

	body->CreateFixture(&fixtureDef);
}
