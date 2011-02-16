/*
 * camera_angling.c
 *
 *  Created on: Feb 5, 2011
 *      Author: shawn
 */

#include <SDL_opengl.h>
#include <math.h>
#include "../headers/types.h"
#include "../headers/vector_math.h"
#include "../headers/camera_angling.h"


void setUpAndLoadModelViewMatrix(CAMERA_POSITION *cam) {
	float mat[16];
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
	mat[1] = -cos_z*sin_y*cos_x+sin_z*sin_x;
	mat[2] = -cos_z*sin_y*sin_x-sin_z*cos_x;
	mat[3] = 0;
	mat[4] = -sin_z*cos_y;
	mat[5] = sin_z*sin_y*cos_x+cos_z*sin_x;
	mat[6] = sin_z*sin_y*sin_x-cos_z*cos_x;
	mat[7] = 0;
	mat[8] = sin_y;
	mat[9] = cos_y*cos_x;
	mat[10] = cos_y*sin_x;
	mat[11] = 0;
	mat[12] = -mat[0]*cam->offset[0] - mat[4]*cam->offset[1]
	                - mat[8]*cam->offset[2];
	mat[13] = -mat[1]*cam->offset[0] - mat[5]*cam->offset[1]
	                - mat[9]*cam->offset[2];
	mat[14] = -mat[2]*cam->offset[0] - mat[6]*cam->offset[1]
	                - mat[10]*cam->offset[2];
	mat[15] = 1;
	// I hope this works
	glMultMatrixf(mat);
}


void rotateCamera_X(CAMERA_POSITION *cam, float deg) {
	float newXr = cam->rot_x + deg;
	if (newXr <= M_PI/2 && newXr >= -M_PI/2) {
		cam->rot_x = newXr;
	}
}
void rotateCamera_Y(CAMERA_POSITION *cam, float deg) {
	cam->rot_y += deg;
}
void rotateCamera_Z(CAMERA_POSITION *cam, float deg) {
	cam->rot_z += deg;
}

// forward is positive amount
void moveCameraForward(CAMERA_POSITION *cam, float amt) {
	vec3_t delta, temp;

	// compute some necessary values
	float cos_x = cos(cam->rot_x);
	float cos_y = cos(cam->rot_y);
	float cos_z = cos(cam->rot_z);
	float sin_x = sin(cam->rot_x);
	float sin_y = sin(cam->rot_y);
	float sin_z = sin(cam->rot_z);

	// compute changes in world coords
	delta[0] = cos_z*sin_y*sin_x + sin_z*cos_x;
	delta[1] = cos_z*cos_x - sin_z*sin_y*sin_x;
	delta[2] = -cos_y*sin_x;

	if (!cam->isFree) {
		delta[2] = 0;
		vect_normalize_3(delta,temp);
		vect_copy_3(temp,delta);
	}

	cam->offset[0] += amt *delta[0];
	cam->offset[1] += amt *delta[1];
	cam->offset[2] += amt *delta[2];
}

// right is positive amount, left is negative
void moveCameraStrafe(CAMERA_POSITION *cam, float amt) {
	vec3_t delta, temp;
	// compute some necessary values
	float cos_y = cos(cam->rot_y);
	float cos_z = cos(cam->rot_z);
	float sin_y = sin(cam->rot_y);
	float sin_z = sin(cam->rot_z);

	// compute changes in world coords
	delta[0] = cos_z*cos_y;
	delta[1] = -sin_z*cos_y;
	delta[2] = sin_y;

	if (!cam->isFree) {
		delta[2] = 0;
		vect_normalize_3(delta,temp);
		vect_copy_3(temp,delta);
	}

	cam->offset[0] += amt *delta[0];
	cam->offset[1] += amt *delta[1];
	cam->offset[2] += amt *delta[2];
}
