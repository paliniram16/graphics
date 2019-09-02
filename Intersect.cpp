//Implementation of the Intersect class

#include "Intersect.h"
#include "variables.h"

static bool ray_sphere(Vector p0, Vector p1, Vector center, float radius){
	//Note: This returns the intersection in physical coord; no
	//further conversion is needed. 
	Vector temp = Vector::sub(-p0, center);
	temp = Vector::mult(-1, temp);
	float alpha = Vector::dot(temp, p1);
	Vector q = Vector::add(p0, Vector::mult(alpha, p1));
	float temp1 = glm::length(q - center);
	float bSq = Vector::dot(temp1, temp1);
	float r2 = pow(radius, 2);
	
	if(bSq > r2){
		//throw an exception? what to do 
		return false;
	}
	
	float a = sqrt(r2 - bSq);
	
	if(alpha >= a || a + alpha > 0){
		Intersect::intersection_point = Intersect::ray_sphere_val(alpha, a, q, p1);
		return true;
	}
	else{
		return false;
	}
}

static Vector ray_sphere_val(float alpha, float a, Vector q, Vector p1){
	if(alpha >= a){
		intersect = true;
		Vector q1 = Vector::sub(q , Vector::mult(alpha,p1));
		return q1;
	}
	
	else if(a + alpha > 0){
		intersect = true;
		Vector q2 = Vector::add(q , Vector::mult(alpha * p1));
		return q2;
	}
}

static bool ray_plane(Vector p0, Vector p1, Vector normal, float a){
	float x = Vector::dot(p1, normal);//does the ray intersect the sphere?
	if(x == 0){
		return false;
	}
	float temp = (a - Vector::dot(p0, normal));
	Intersect::alpha = temp/x;
	return true;
}


static bool ray_triangle(Vector v0, Vector v1, Vector v2, Vector p0, Vector p1){
	Vector normal = Vector::cross(Vector::sub(v1,v0),Vector::sub(v2,v0));
	float d = Vector::dot(normal, v0);
	if(ray_plane(p0, p1, normal, d) == false){
		return false;
	}
	//compute the intersection
	Vector q =  Vector::add(p0, Vector::mult((Intersect::alpha),p1));
	
	//edge vectors for the triangle
	Vector e1 = v1 - v0;	
	Vector e2 = v2 - v0;
		
	float a = Vector::dot(e1, e1);
	float b = Vector::dot(e1, e2);
	float c = Vector::dot(e2, e2);
		
	float D = (a*c) - pow(b, 2);
	float A = a/D;
	float B = b/D;
	float C = c/D;
		
	Vector u_beta = Vector::sub(Vector::mult(C,e1), Vector::mult(B,e2));
	Vector u_gamma = Vector::sub(Vector::mult(A,e2), Vector::mult(B,e1));
	
	Vector temp = Vector::sub(q, v0);
	float beta = Vector::dot(u_beta, temp);
	
	if(beta < 0){
		return false;
	}
	
	float gamma = glm::dot(u_gamma, temp);
	if(gamma < 0){
		return false;
	}
	
	float alpha = 1 - beta - gamma;
	if(alpha < 0){
		return false;
	}
	
	Intersect::intersection_point = q;
	return true;
}
