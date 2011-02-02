/*
 * main.c
 *
 *  Created on: Jan 26, 2011
 *      Author: shawn
 */

#include <SDL.h>
#include <SDL_main.h>
#include <SDL_opengl.h>
#include <stdio.h>

static int user_exit = 0;

static void r_init();
static void r_drawFrame();

int SDL_main(int argc, char* argv[])
{
	SDL_Event		event;
	SDL_Surface		*screen;

	if(SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER) != 0)
	{
		printf("Unable to initialize SDL: %s\n", SDL_GetError());
		return 1;
	}

	SDL_WM_SetCaption("SDL Window", "SDL Window");
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	//Initialize window
	screen = SDL_SetVideoMode(1024, 768, 32, SDL_OPENGL);
	if(!screen)
	{
		printf("Unable to set video mode: %s\n", SDL_GetError());
		return 1;
	}

	r_init();

	//Main loop
	while(!user_exit)
	{
		//Handle input
		while(SDL_PollEvent(&event))
		{
			switch(event.type)
			{
			case SDL_KEYDOWN:
			case SDL_KEYUP:
			case SDL_MOUSEMOTION:
				break;
			case SDL_QUIT:
				user_exit = 1;
			}
		}

		r_drawFrame();
	}

	SDL_Quit();

	return 0;
}

static void r_init()
{
	//nothing for now
}

static void r_drawFrame()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_POLYGON);
		glVertex3f(-0.5, 0.0, 0.0);
		glVertex3f(0.5, 0.0, 0.0);
		glVertex3f(0.0, 1.0, 0.0);
	glEnd();

	SDL_GL_SwapBuffers();
}
