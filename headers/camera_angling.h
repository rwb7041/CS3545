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
	vec3_t offset;
} CAMERA_POSITION;

void setUpAndLoadModelViewMatrix(CAMERA_POSITION *cam);

#endif /* CAMERA_ANGLING_H_ */
