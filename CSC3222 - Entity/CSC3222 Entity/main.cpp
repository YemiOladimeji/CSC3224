#include "Entity.h"
#include "Vector3D.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

int main() {

	vector<Entity> entities;
	int entNo, ab;
	srand(time(NULL));


	cout << "Enter the number of entities you would like to generate: ";
	cin >> entNo;

	for (int i = 0; i < entNo; i++) {
		float x = rand() % 10 + 1;
		float y = rand() % 10 + 1;
		float z = rand() % 10 + 1;
		float agg = rand() % 10 + 1;

		Vector3D pos(x, y, z);
		Entity e(pos, agg);

		entities.push_back(e);
	}

	for (std::vector<Entity>::size_type j = 0; j != entities.size(); j++) {
		cout << "\nCurrent entities in range for entity " << j << ": " << entities[j].getEntitiesInRange();
		entities[j].updateEntitiesInRange(entities);
		cout << "\nUpdated entities in range for entity " << j << ": " << entities[j].getEntitiesInRange();
	}
	cin >> ab;
	return 0;
}