//Ray.cpp: Implementation of the Ray class

#include "Ray.h"
#include "variables.h"

Ray Ray::generateRay(vec3 lookFrom, vec3 lookAt, vec3 up, float fovy, float fovx, 
					float i, float j, int width, int height){
	vec3 a = lookFrom - lookAt;
	vec3 b = up;
	
	//construct an orthogonal coordinate frame given a and b
	vec3 w = normalize(a);
	vec3 u = normalize(cross(b,w));
	vec3 v = cross(w,u);
	
	//compute alpha and beta terms
	float alpha = tan((glm::radians(fovx))/2) * ((j - (width/2))/(width/2));
	float beta = tan((glm::radians(fovy))/2) * (((height/2) - i)/(height/2));
	
	//compute the ray direction
	Ray::direction = normalize(alpha*u + beta*v - w);
	Ray::origin = lookFrom;
}

