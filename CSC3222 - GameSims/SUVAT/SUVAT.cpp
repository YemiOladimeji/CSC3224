#include "SUVAT.h"

Vector3 SUVAT::calculate(Vector3 u, Vector3 a, float t) {
	Vector3 v = u + (a * t);
	return v;
}