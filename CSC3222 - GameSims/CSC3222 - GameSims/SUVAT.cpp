#include "SUVAT.h"

float SUVAT::getV(float u, float a, float t) {
	return u + (a * t);
}

float SUVAT::getS(float u, float a, float t) {
	return (u * t) + ((a * t * t) * 0.5f);
}

float SUVAT::getSFromUAT(float u, float v, float t) {
	return (u + v) * t * 0.5f;
}

float SUVAT::getVFromUAS(float u, float a, float s) {
	return (u * u) + (2.0f * a * s);
}

float SUVAT::getSFromVTA(float v, float t, float a) {
	return (v * t) - ((a * t * t) * 0.5f);
}

Vector3 SUVAT::getV(Vector3 &u, Vector3 a, Vector3 &t) {
	return u + (a * t);
}

Vector3 SUVAT::getS(Vector3 &u, Vector3 &a, Vector3 &t) {
	return (u * t) + ((a * t * t) * 0.5f);
}

Vector3 SUVAT::getSFromUVT(Vector3 &u, Vector3 &v, Vector3 &t) {
	return (u + v) * t * 0.5f;
}

Vector3 SUVAT::getVFromUAS(Vector3 &u, Vector3 &a, Vector3 &s) {
	return (u * u) + (a * s * 2.0f);
}

Vector3 SUVAT::getSFromVTA(Vector3 &v, Vector3 &t, Vector3 &a) {
	return (v * t) - ((a * t * t) * 0.5f);
}

