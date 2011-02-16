/*
 * camera_angling.h
 *
 *  Created on: Feb 5, 2011
 *      Author: shawn
 */

#ifndef CAMERA_ANGLING_H_
#define CAMERA_ANGLING_H_

typedef struct {
	float rot_x;
	float rot_y;
	float rot_z;
	bool  isFree;
	vec3_t offset;
} CAMERA_POSITION;

void setUpAndLoadModelViewMatrix(CAMERA_POSITION *cam);

void rotateCamera_X(CAMERA_POSITION *cam, float deg);
void rotateCamera_Y(CAMERA_POSITION *cam, float deg);
void rotateCamera_Z(CAMERA_POSITION *cam, float deg);

void moveCameraForward(CAMERA_POSITION *cam, float amt);
void moveCameraStrafe(CAMERA_POSITION *cam, float amt);

#endif /* CAMERA_ANGLING_H_ */
