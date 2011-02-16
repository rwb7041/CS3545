/*
 * main.c
 *
 *  Created on: Jan 26, 2011
 *      Author: Clinton Freeman
 *      Hacker such that it is unrecognizable: Shawn Waldon & Ryan Belt
 */

#include <SDL.h>
#include <SDL_main.h>
#include <SDL_opengl.h>
#include <SDL_keysym.h>
#include <stdio.h>
#include <math.h>
#include "headers/types.h"
#include "headers/vector_math.h"
#include "headers/rendererMagicNumbers.h"
#include "headers/camera_angling.h"

//Means of the user exiting the main loop - it is static because it will not be seen outside of this file.
static int user_exit = 0;

static float root3over4 = sqrt(3)/4.0;


static float RED[3] =   {1.0,0.0,0.0};
static float GREEN[3] = {0.0,1.0,0.0};
static float BLUE[3] =  {0.0,0.0,1.0};

static int keys_down[256];
static void input_update(CAMERA_POSITION *cam);
static void resetCamera(CAMERA_POSITION *camera);
static void input_keyDown(SDLKey k, CAMERA_POSITION *cam);
static void randomizeColors(float **colors);
static void input_keyUp(SDLKey k);

static void input_mouseMoved(CAMERA_POSITION *cam, int x, int y);


//Added two new functions - also static as they will not be used outside of this file.
//Eventually these will be moved out of here into a "rendering" subsystem, which is why they are prefixed r_.
static void r_init(CAMERA_POSITION *cam);
static void r_reset(CAMERA_POSITION *cam);
static void r_drawFrame(float **colors);

//Program entry point
int SDL_main(int argc, char* argv[])
{
	int i;
	SDL_Event	event;		//Used for handling input events, as you can see later on.
	SDL_Surface	*screen;	//http://www.libsdl.org/cgi/docwiki.cgi/SDL_Surface
	CAMERA_POSITION camera;
	float *colors[3] = {&RED[0], &GREEN[0], &BLUE[0]};

	for (i = 0; i < 256; i++) {
		keys_down[i] = 0;
	}
	resetCamera(&camera);

	//The following is pretty self-explanatory
	if(SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER) != 0)
	{
		printf("Unable to initialize SDL: %s\n", SDL_GetError());
		return 1;
	}

	//You can of course customize this.
	SDL_WM_SetCaption("Perspective Projection", "Perspective Projection");

	//We need to explicitly enable double buffering
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	//Initialize window, setting the resolution to 1024x768 @ 32 bits per pixel. We want an OpenGL window.
	screen = SDL_SetVideoMode(1024, 768, 32, SDL_OPENGL);
	if(!screen)
	{
		printf("Unable to set video mode: %s\n", SDL_GetError());
		return 1;
	}

	//Any other one-time initialization would typically go here.
	//"Renderer" initialization
	r_init(&camera);

	//This is what is referred to as the "game loop." Obviously there is not much here currently.
	while(!user_exit)
	{
		bool mouseMoved = FALSE;
		int x = 0, y = 0;
		//Handle input
		while(SDL_PollEvent(&event))
		{
			switch(event.type)
			{
			case SDL_KEYDOWN:
				input_keyDown(event.key.keysym.sym, &camera);
				break;
			case SDL_KEYUP:
				input_keyUp(event.key.keysym.sym);
				break;
			case SDL_MOUSEBUTTONDOWN:
				randomizeColors(colors);
				break;
			case SDL_MOUSEMOTION:
				x = event.motion.x;
				y = event.motion.y;
				mouseMoved = TRUE;
				break;
			case SDL_QUIT:
				exit(0);
			}
		}
		input_update(&camera);
		if (mouseMoved) {
			input_mouseMoved(&camera, x, y);
			setUpAndLoadModelViewMatrix(&camera);
		}

		//Here is where you will do any OpenGL drawing. You would also do things like update moving objects, etc.
		//Do whatever we need to do to draw a single image.
		r_drawFrame(colors);
	}

	//Shut down SDL
	SDL_Quit();

	//Everything went OK.
	return 0;
}

static void r_init(CAMERA_POSITION *cam)
{
	//Enable depth buffering
	glEnable(GL_DEPTH_TEST);

	//Change to projection mode (three modes: modelview, projection, and texture
	//we will be using the just the first two)
	glMatrixMode(GL_PROJECTION);
	//Load the identity matrix
	glLoadIdentity();
	//Generate a perspective projection matrix using the following parameters
	//90 degree field of view (horizontal), 1.33 aspect ratio (width/height of viewport)
	//Distance to the nearplane (must be positive), distance to the farplane (also positive).
	gluPerspective(90.0, 1.33, 0.1, 30.0);
	// set up and load the model view matrix for this camera
	setUpAndLoadModelViewMatrix(cam);

	glEnable(GL_CULL_FACE);

	glCullFace(GL_BACK);

}

static void r_reset(CAMERA_POSITION *cam)
{
	resetCamera(cam);
	setUpAndLoadModelViewMatrix(cam);
}

//Produces a simple image
static void r_drawFrame(float **colors)
{
	// Clear the color buffer (these are the final values that get sent to the monitor).
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// White triangle
	glColor3f(1.0, 1.0, 1.0);

	// first face
	glBegin(GL_TRIANGLES);
		glColor3fv(colors[0]);
		glVertex3f(-0.5, -root3over4, -root3over4);
		glColor3fv(colors[1]);
		glVertex3f( 0.5, -root3over4, -root3over4);
		glColor3fv(colors[2]);
		glVertex3f( 0.0,  0.0, root3over4);
	glEnd();

	// second face
	glBegin(GL_TRIANGLES);
		glColor3fv(colors[2]);
		glVertex3f(0.5, -root3over4, -root3over4);
		glColor3fv(colors[0]);
		glVertex3f( 0.0, root3over4, -root3over4);
		glColor3fv(colors[1]);
		glVertex3f( 0.0,  0.0, root3over4);
	glEnd();

	// third face
	glBegin(GL_TRIANGLES);
		glColor3fv(colors[1]);
		glVertex3f(-0.5, -root3over4, -root3over4);
		glColor3fv(colors[2]);
		glVertex3f( 0.0, 0.0, root3over4);
		glColor3fv(colors[0]);
		glVertex3f( 0.0,  root3over4, -root3over4);
	glEnd();

	// base
	glBegin(GL_TRIANGLES);
		glColor3fv(colors[1]);
		glVertex3f(0.0, root3over4, -root3over4);
		glColor3fv(colors[0]);
		glVertex3f( 0.5, -root3over4, -root3over4);
		glColor3fv(colors[2]);
		glVertex3f( -0.5,  -root3over4, -root3over4);
	glEnd();

	glBegin(GL_LINES);
		// x axis from grey to red (red is +x)
		glColor3f(.5,.5,.5);
		glVertex3f(-5,0,0);
		glColor3f(1,0,0);
		glVertex3f(5,0,0);
		// y axis from grey to green (green is +y)
		glColor3f(.5,.5,.5);
		glVertex3f(0,-5,0);
		glColor3f(0,1,0);
		glVertex3f(0,5,0);
		// z axis from grey to blue (blue is +z)
		glColor3f(.5,.5,.5);
		glVertex3f(0,0,-5);
		glColor3f(0,0,1);
		glVertex3f(0,0,5);
	glEnd();

	//The view frustum at this point is still pointing down the negative Z (into the monitor).
	//The near plane is located at Z = -1.0, and the far plane at Z = -10.0.
	//This means, as before, drawing things at > -1.0 will lead to them being clipped out
	//of the view. (Actually, it isn't quite that accurate, primitives at -1.0 get clipped
	//as well).
	//Try playing around with moving the triangle further away from the nearplane, (i.e. decreasing
	//the Z values (-6.0, -7.0, etc.). You should notice it shrinking.
	//Also, it is probably best to view a 3D object to see the effects of the perspective projection.
	//Try making a cube using GL_QUADS or GL_POLYGON, and placing it offset from the center. You should
	//see a foreshortening effect.

	//Swap the front and back frame buffers to display the image in our window.
	SDL_GL_SwapBuffers();
}

static void input_update(CAMERA_POSITION *cam) {
	if (keys_down[SDLK_DOWN]) {
		rotateCamera_X(cam, 0.005);
		setUpAndLoadModelViewMatrix(cam);
	} else if (keys_down[SDLK_UP]) {
		rotateCamera_X(cam, -0.005);
		setUpAndLoadModelViewMatrix(cam);
	}
	if (keys_down[SDLK_RIGHT]) {
		rotateCamera_Z(cam, 0.005);
		setUpAndLoadModelViewMatrix(cam);
	} else if (keys_down[SDLK_LEFT]) {
		rotateCamera_Z(cam, -0.005);
		setUpAndLoadModelViewMatrix(cam);
	}
	if (keys_down[SDLK_q]) {
		rotateCamera_Y(cam, -0.005);
		setUpAndLoadModelViewMatrix(cam);
	} else if (keys_down[SDLK_e]) {
		rotateCamera_Y(cam, 0.005);
		setUpAndLoadModelViewMatrix(cam);
	}

	if (keys_down[SDLK_w]) {
		moveCameraForward(cam,0.005);
		setUpAndLoadModelViewMatrix(cam);
	} else if (keys_down[SDLK_s]) {
		moveCameraForward(cam,-0.005);
		setUpAndLoadModelViewMatrix(cam);
	}

	if (keys_down[SDLK_a]) {
		moveCameraStrafe(cam, -0.005);
		setUpAndLoadModelViewMatrix(cam);
	} else if (keys_down[SDLK_d]) {
		moveCameraStrafe(cam, 0.005);
		setUpAndLoadModelViewMatrix(cam);
	}

//	if (keys_down[SDLK_SPACE]) {
//		cam->offset[1] -= 0.001; // -y
//		setUpAndLoadModelViewMatrix(cam);
//	} else if (keys_down[SDLK_c]) {
//		cam->offset[1] += 0.001; // +y
//		setUpAndLoadModelViewMatrix(cam);
//	}



	if(keys_down[SDLK_r]) {
		r_reset(cam);
	}
}
static void input_keyDown(SDLKey k, CAMERA_POSITION *cam) {
	keys_down[k] = 1;
	if(k == SDLK_ESCAPE) user_exit = 1;
	if(k == SDLK_BACKQUOTE) cam->isFree = !cam->isFree;
}
static void input_keyUp(SDLKey k) {
	keys_down[k] = 0;
}

static void resetCamera(CAMERA_POSITION *camera) {
	camera->offset[0] = 0;
	camera->offset[1] = -3;
	camera->offset[2] = 0;
	camera->rot_x = 0;
	camera->rot_y = 0;
	camera->rot_z = 0;
	camera->isFree = TRUE;
}

static void randomizeColors(float **colors) {
	int i;
	for (i = 2; i > 0; i--) {
		float *c = colors[i];
		int r = (int) (drand48() * (i+1));
		colors[i] = colors[r];
		colors[r] = c;
	}
}

static void input_mouseMoved(CAMERA_POSITION *cam, int x, int y) {
	float halfWinHeight = (float)WINDOW_HEIGHT/2.0;
	float halfWinWidth = (float)WINDOW_WIDTH/2.0;

	float dx = x-halfWinWidth;
	float dy = y-halfWinHeight;

	rotateCamera_X(cam, dy/120.0);
	rotateCamera_Z(cam, dx/120.0);

	//Reset cursor to center
	SDL_WarpMouse(halfWinWidth, halfWinHeight);
}
