/******************************************************************************
Class:Mesh
Implements:
Author:Rich Davison	<richard.davison4@newcastle.ac.uk>
Description: Class to represent the geometric data that makes up the meshes
we render on screen.

-_-_-_-_-_-_-_,------,   
_-_-_-_-_-_-_-|   /\_/\   NYANYANYAN
-_-_-_-_-_-_-~|__( ^ .^) /
_-_-_-_-_-_-_-""  ""   

*//////////////////////////////////////////////////////////////////////////////

#pragma once

#include "Vector4.h"
#include "Colour.h"
#include "Vector3.h"
#include "Vector2.h"
#include "Common.h"

#include <string>
#include <fstream>
#include <vector>
#include <ctime>

using std::ifstream;
using std::string;

enum PrimitiveType {
	PRIMITIVE_POINTS,
	PRIMITIVE_LINES,
	PRIMITIVE_LINESTRIP,
	PRIMITIVE_TRIANGLES
};

class Mesh	{
	friend class SoftwareRasteriser;
public:
	Mesh(void);
	~Mesh(void);


	static Mesh* GeneratePoints() {
		Mesh* m = new Mesh();
		float x, y;
		m->type = PRIMITIVE_POINTS;
		srand((unsigned)time(NULL));

		m->numVertices = (uint)1000;
		m->vertices = new Vector4[m->numVertices];
		m->colours = new Colour[m->numVertices];

		for (int i = 0; i < m->numVertices; ++i) {
			x = -1+2*((float)rand()) / RAND_MAX;
			y = -1+2*((float)rand()) / RAND_MAX;

			m->vertices[i] = Vector4(x, y, 0, 1.0f);
			m->colours[i] = Colour(255, 255, 255, 255);
		}

		return m;
	}


	static Mesh*	GenerateLine(const Vector3 &from, const Vector3 &to) {
		Mesh* m = new Mesh();

		m->numVertices = 2;

		m->vertices = new Vector4[m->numVertices];
		m->colours = new Colour[m->numVertices];

		m->vertices[0] = Vector4(from.x, from.y, from.z, 1.0f);
		m->vertices[1] = Vector4(to.x, to.y, to.z, 1.0f);

		m->colours[0] = Colour(255, 0, 0, 255);
		m->colours[1] = Colour(0, 0, 255, 255);

		m->type = PRIMITIVE_LINES;

		return m;
	}

	static Mesh*	GenerateTriangle() {
		Mesh* m = new Mesh();
		m->type = PRIMITIVE_TRIANGLES;

		m->numVertices = 3;

		m->vertices = new Vector4[m->numVertices];
		m->colours = new Colour[m->numVertices];
		m->textureCoords = new Vector2[m->numVertices];

		m->vertices[0] = Vector4(0.5f, -0.5f, 0, 1.0f);
		m->vertices[1] = Vector4(0.0f, 0.5f, 0, 1.0f);
		m->vertices[2] = Vector4(-0.5f, -0.5f, 0, 1.0f);

		m->colours[0] = Colour(255, 0, 0, 255);
		m->colours[1] = Colour(0, 255, 0, 255);
		m->colours[2] = Colour(0, 0, 255, 255);

		m->textureCoords[0] = Vector2(0.0f, 0.0f); 
		m->textureCoords[1] = Vector2(0.5f, 1.0f);
		m->textureCoords[2] = Vector2(0.5f, 0.0f);

		return m;
	}

	static Mesh*	GenerateStarTriangle() {
		Mesh* m = new Mesh();
		m->type = PRIMITIVE_TRIANGLES;

		m->numVertices = 3;

		m->vertices = new Vector4[m->numVertices];
		m->colours = new Colour[m->numVertices];
		m->textureCoords = new Vector2[m->numVertices];

		m->vertices[0] = Vector4(0.5f, -0.5f, 0, 1.0f);
		m->vertices[1] = Vector4(0.0f, 0.5f, 0, 1.0f);
		m->vertices[2] = Vector4(-0.5f, -0.5f, 0, 1.0f);

		m->colours[0] = Colour(255, 255, 0, 127);
		m->colours[1] = Colour(255, 255, 0, 255);
		m->colours[2] = Colour(255, 255, 0, 127);

		m->textureCoords[0] = Vector2(0.0f, 0.0f);
		m->textureCoords[1] = Vector2(0.5f, 1.0f);
		m->textureCoords[2] = Vector2(0.5f, 0.0f);

		return m;
	}

	static Mesh*	GenerateBlueTriangle() {
		Mesh* m = new Mesh();
		m->type = PRIMITIVE_TRIANGLES;

		m->numVertices = 3;

		m->vertices = new Vector4[m->numVertices];
		m->colours = new Colour[m->numVertices];
		m->textureCoords = new Vector2[m->numVertices];

		m->vertices[0] = Vector4(0.5f, -0.5f, 0, 1.0f);
		m->vertices[1] = Vector4(0.0f, 0.5f, 0, 1.0f);
		m->vertices[2] = Vector4(-0.5f, -0.5f, 0, 1.0f);

		m->colours[0] = Colour(0, 0, 255, 255);
		m->colours[1] = Colour(0, 0, 255, 255);
		m->colours[2] = Colour(0, 0, 255, 255);

		m->textureCoords[0] = Vector2(0.0f, 0.0f);
		m->textureCoords[1] = Vector2(0.5f, 1.0f);
		m->textureCoords[2] = Vector2(0.5f, 0.0f);

		return m;
	}

	PrimitiveType	GetType() { return type;}

protected:
	PrimitiveType	type;
	uint			numVertices;
	Vector4*		vertices;
	Colour*			colours;
	Vector2*		textureCoords;	//We get onto what to do with these later on...
};

