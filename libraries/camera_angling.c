/*
 * camera_angling.c
 *
 *  Created on: Feb 5, 2011
 *      Author: shawn
 */

#include <SDL_opengl.h>
#include <math.h>
#include "../headers/vector_math.h"
#include "../headers/camera_angling.h"


void setUpAndLoadModelViewMatrix(CAMERA_POSITION *cam) {
	float mat[16];
	int i;
	// compute some necessary values
	float cos_x = cos(cam->rot_x);
	float cos_y = cos(cam->rot_y);
	float cos_z = cos(cam->rot_z);
	float sin_x = sin(cam->rot_x);
	float sin_y = sin(cam->rot_y);
	float sin_z = sin(cam->rot_z);
	// initialize to the identity matrix
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	// matrix equations calculated in Maple.... hope it works
	mat[0] = cos_z*cos_y;
	mat[1] = -sin_z*cos_x + cos_z*sin_y*sin_x;
	mat[2] = sin_z*sin_x + cos_z*sin_y*cos_x;
	mat[3] = 0;
	mat[4] = sin_z*cos_y;
	mat[5] = cos_z*cos_x + sin_z*sin_y*sin_x;
	mat[6] = -cos_z*sin_x + sin_z*sin_y*cos_x;
	mat[7] = 0;
	mat[8] = -sin_y;
	mat[9] = cos_y*sin_x;
	mat[10] = cos_y*cos_x;
	mat[11] = 0;
	mat[12] = mat[13] = mat[14] = 0;
	mat[15] = 1;
	// I hope this works
	glMultMatrixf(mat);
	for (i = 0; i < 16; i++) {
		mat[i] = 0;
	}
	mat[0] = mat[5] = mat[10] = mat[15] = 1;
	mat[12] = cam->offset[0];
	mat[13] = cam->offset[1];
	mat[14] = cam->offset[2];
	glMultMatrixf(mat);
}
