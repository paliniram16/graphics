// Transform.cpp: implementation of the Transform class.

// Note: when you construct a matrix using mat4() or mat3(), it will be COLUMN-MAJOR
// Keep this in mind in readfile.cpp and display.cpp
// See FAQ for more details or if you're having problems.

#include "Transform.h"
#include "Vector.h"

// Helper rotation function.  Please implement this.  
mat3 Transform::rotate(const float degrees, Vector axis) 
{
  // YOUR CODE FOR HW2 HERE
  // Please implement this.  Likely the same as in HW 1.  
  Vector naxis = Vector::normalize(axis);
  mat3 id3 = mat3(1,0,0,0,1,0,0,0,1);
	float rad =glm::radians(degrees);
	mat3 expr1 = cos(rad) * id3;
	mat3 axis_mat = mat3(naxis.x, naxis.y, naxis.z, 0,0,0,0,0,0);
	mat3 axist_mat = mat3(naxis.x, 0,0, naxis.y,0,0, naxis.z,0,0);
	mat3 aa_t = axis_mat * axist_mat;
	mat3 expr2 = (1 - cos(rad)) * aa_t;
	mat3 dual_mat = mat3(0, naxis.z, -naxis.y, -naxis.z, 0, naxis.x, naxis.y, -naxis.x, 0);
	mat3 expr3 = sin(rad) * dual_mat;
	mat3 result = expr1 + expr2 + expr3; 
	// You will change this return call
	return result;
}

void Transform::left(float degrees, Vector& eye, Vector& up) 
{
  // YOUR CODE FOR HW2 HERE
  // Likely the same as in HW 1.  
   Vector axis = Vector::normalize(up);
       mat3 res = rotate(degrees, axis);
        float rad = glm::radians(degrees);
        mat3 temp = mat3(cos(rad), 0, -sin(rad), 0, 1, 0, sin(rad), 0, cos(rad));//2D rotation about Y axis
        eye = Vector::mat_vec(res, eye);
	Vector::normalize(eye);
}

void Transform::up(float degrees, Vector& eye, Vector& up) 
{
  // YOUR CODE FOR HW2 HERE 
  // Likely the same as in HW 1.  
  Vector temp = Vector(1,0,0);
	Vector axis = Vector::cross(eye,up);
	axis = Vector::normalize(axis);
	mat3 res = rotate(degrees, axis);
	up = Vector::mat_vec(res, up);
	eye = Vector::mat_vec(res, eye);
}

mat4 Transform::lookAt(const Vector &eye, const Vector &center, const Vector &up) 
{
  // YOUR CODE FOR HW2 HERE
  // Likely the same as in HW 1. 
	Vector a = Vector::sub(eye, center);
	Vector b = up;
	Vector w = Vector::normalize(a);
	Vector u = Vector::normalize(Vector::cross(b,w));
	Vector v = Vector::cross(w,u);
	mat4 rot = mat4(u.x, v.x, w.x, 0, u.y, v.y, w.y, 0, u.z, v.z, w.z, 0, 0,0,0,1);
	mat4 trans = mat4(1,0,0,0,0,1,0,0,0,0,1,0,-eye.x, -eye.y, -eye.z, 1);
	mat4 res = mat4(u.x,v.x,w.x,0,u.y,v.y,w.y,0,u.z,v.z,w.z,0, 
	Vector::dot(u,-eye), Vector::dot(v, -eye), Vector::dot(w, -eye), 1);
	// You will change this return call
	return res;
   
}

mat4 Transform::perspective(float fovy, float aspect, float zNear, float zFar)
{
  mat4 ret;
  // YOUR CODE FOR HW2 HERE
  // New, to implement the perspective transform as well. 
  float angle = glm::radians(fovy/2);
  float d =  1/(tan(angle));
  float a = (zFar + zNear)/(zFar - zNear);
  float b = 2 * (zFar * zNear)/(zFar - zNear);
  ret = mat4((d/aspect), 0,0,0, 0,d,0,0, 0,0,-a,-1, 0,0,-b,0);
  return ret;
}

mat4 Transform::scale(const float &sx, const float &sy, const float &sz) 
{
  mat4 ret;
  // YOUR CODE FOR HW2 HERE
  // Implement scaling 
  ret = mat4(sx,0,0,0, 0,sy,0,0, 0,0,sz,0, 0,0,0,1);
  return ret;
}

mat4 Transform::translate(const float &tx, const float &ty, const float &tz) 
{
  mat4 ret;
  // YOUR CODE FOR HW2 HERE
  // Implement translation
  ret = mat4(1,0,0,0, 0,1,0,0, 0,0,1,0, tx,ty,tz,1); 
  return ret;
}

// To normalize the up direction and construct a coordinate frame.  
// As discussed in the lecture.  May be relevant to create a properly 
// orthogonal and normalized up. 
// This function is provided as a helper, in case you want to use it. 
// Using this function (in readfile.cpp or display.cpp) is optional.  

Vector Transform::upvector(const Vector &up, const Vector & zvec) 
{
  Vector x = Vector::cross(up,zvec); 
  Vector y = Vector::cross(zvec,x); 
  Vector ret = Vector::normalize(y); 
  return ret; 
}


Transform::Transform()
{

}

Transform::~Transform()
{

}
