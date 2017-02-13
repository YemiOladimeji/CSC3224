#pragma once
#include <iostream>
#include "SUVAT.h"
#include "Vector3D.h"

int main() {
	float ux, uy, uz, ax, ay, az;
	Vector3D u;
	Vector3D a;
	Vector3D v;
	float t, ab;
	SUVAT calc;

	cout << "SUVAT Calculator\n";
	cout << "Enter the x, y and z values for the first vector: ";
	cin >> ux >> uy >> uz;
	u.setX(ux);
	u.setY(uy);
	u.setZ(uz);

	cout << "\nEnter the x, y and z values for the second vector: ";
	cin >> ax >> ay >> az;
	a.setX(ax);
	a.setY(ay);
	a.setZ(az);

	cout << "\nSet the time: ";
	cin >> t;
	calc.setTime(t);

	cout << "First Vector: ";
	cout << "<" << u.getX() << "," << u.getY() << "," << u.getX() << ">";

	cout << "Second Vector: ";
	cout << "<" << a.getX() << "," << a.getY() << "," << a.getX() << ">";

	cout << "Calculating...";
	v = calc.calculate(u, a, t);
	cout << "<" << v.getX() << "," << v.getY() << "," << v.getX() << ">";

	cin >> ab;

	return 0;
}