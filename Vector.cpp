//Implementation of the Vector class. 
//Provides functions for basic vector operations

#include "Vector.h"

Vector::Vector(float x_in, float y_in, float z_in){
	Vector::x = x_in;
	Vector::y = y_in;
	Vector::z = z_in;
}

Vector Vector::add(Vector v1, Vector v2){
	return Vector(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
}

Vector Vector::sub(Vector v1, Vector v2){
	return Vector(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
}

Vector Vector::mult(float num, Vector v){
	return Vector(num * v.x, num * v.y, num * v.z);
}

Vector div(float num, Vector v){
	return Vector(v.x/num, v.y/num, v.z/num);
}

Vector Vector::cross(Vector v1, Vector v2){
	float term1 = (v1.y*v2.z) - (v1.z*v2.y);
	float term2 = (v1.z*v2.x) - (v1.x*v2.z);
	float term3 = (v1.x*v2.y) - (v1.y*v2.x);
	return Vector(term1, term2, term3);
}
float Vector::dot(Vector v1, Vector v2){
	return (v1.x * v2.x) + (v1.y * v2.y) + (v1.z + v2.z);
}
Vector Vector::normalize(Vector v){
	float magnitude = sqrt(v.x*v.x + v.y*v.y + v.z*v.z);
	return div(magnitude, v);
}
Vector Vector::mat_vec(mat3 mat, Vector v){
	float x_res = (mat[0][0]*v.x) + (mat[0][1]*v.y) + (mat[0][2]*v.z);
	float y_res = (mat[1][0]*v.x) + (mat[1][1]*v.y) + (mat[1][2]*v.z);
	float z_res = (mat[2][0]*v.x) + (mat[2][1]*v.y) + (mat[2][2]*v.z);
	return Vector(x_res, y_res, z_res);
}
