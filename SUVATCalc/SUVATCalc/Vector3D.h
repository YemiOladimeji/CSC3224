//Author: Yemi Oladimeji
#ifndef VECTOR3D_H
#define VECTOR3D_H
using namespace std;

class Vector3D{
private:
	//Declaration of the x,y,z components
	float x, y, z;

public:
	//Constructors
	Vector3D(); //Parameterised constructor
	Vector3D(float x, float y, float z); //Default constructor
	~Vector3D() {}; //Destructor


	//Set functions
	inline void setX(float x) {
		this->x = x;
	}

	inline void setY(float y) {
		this->y = y;
	}

	inline void setZ(float z) {
		this->z = z;
	}

	//Get functions
	inline float getX() const {
		return x;
	}

	inline float getY() const {
		return y;
	}

	inline float getZ() const {
		return z;
	}

	//Copy constructor
	Vector3D (const Vector3D &v);

	//Assignment operator
	const Vector3D operator= (const Vector3D &v);

	//Compute the magnitude of a vector
	float getMagnitudeSquared() const;

	//Add vectors together
	Vector3D operator+ (const Vector3D &v) const;

	//Subtract vectors from eachother
	Vector3D operator- (const Vector3D &v) const;

	//Multiply a vector by a scalar
	Vector3D operator* (float n) const;

	//Divide a vector by a scalar
	Vector3D operator/ (const Vector3D &v) const;

	//Calculate the scalar product
	Vector3D operator* (const Vector3D &v) const;

	//Calculate the vector product
	Vector3D operator% (const Vector3D &v) const;

	//Create a unit vector
	Vector3D normaliseVector3D();

	//Find the distance between two vectors (calculate the difference between two vectors and then find the magnitude of that vector)
	float vectorDistance(const Vector3D &v);
};

//ostream &operator<< (ostream &outStream, Vector3D &v);
#endif // VECTOR3D_H
