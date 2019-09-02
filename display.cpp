// Basic includes to get this file to work.  
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <deque>
#include <stack>
// OSX systems require different headers
#ifdef __APPLE__
#include <OpenGL/gl3.h>
#include <OpenGL/glext.h>
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif
#include "Transform.h"
#include "Geometry.h"
using namespace std ; 
#include "variables.h"
#include "readfile.h"

void display() 
{
  glClearColor(0, 0, 1, 0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  
  modelview = Transform::lookAt(eye,center,up); 
  glUniformMatrix4fv(modelviewPos, 1, GL_FALSE, &modelview[0][0]);
  
  for (int i = 0 ; i < numobjects ; i++) {
    object* obj = &(objects[i]);
	if (obj->is_sphere) { 
		vec3 sphere_pos = (obj->sphere_obj).position;
		float sphere_rad = (obj->sphere_obj).radius;
		const int tessel = 20;
      solidSphere(sphere_rad, tessel, tessel); 
	}
  }
 }

