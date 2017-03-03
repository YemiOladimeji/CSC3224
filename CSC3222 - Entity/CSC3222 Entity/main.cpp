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

	//randomly generate positions for entities
	//assign those positions to the entities <- vector data may possibly be getting lost, due to no proper "setPosition" function, needs checking
	//push those entities onto the vector <- using two for loops may have meant that the elements in the vector only existed in the scope of that loop and not globally
	//use previously written functions

	cout << "Enter the number of entities you would like to generate: ";
	cin >> entNo;

	for (std::vector<Entity>::size_type j = 0; j != entities.size(); j++) {

		cout << "\nEntity " << j << ": " << "<" << entities[j].getEntityX() << ", " << entities[j].getEntityY() << ", " << entities[j].getEntityZ() << ">";
		cout << "\nCurrent entities in range for entity " << j << ": " << entities[j].getEntitiesInRange();
	}
	cin >> ab;
	return 0;
}