#include "scop.h"

void	data_init(t_data *d)
{
	d->run = 1;
}

void	update(SDL_Window	*window)
{
	SDL_GL_SwapWindow(window);
}

void	quit_scop(SDL_GLContext glContext, SDL_Window	*window)
{
	// SDL_FreeSurface(screen);
	SDL_GL_DeleteContext(glContext);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

int		handleEvent(SDL_Event event)
{
	switch(event.type) 
	{
		case SDL_QUIT: 
		{ 
			return 0;
		}
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym)
			{
				case 	SDLK_ESCAPE: 
				{ 
					return 0;
				}
			}
	}
	return 1;
}

int main(int argc, char const **argv)
{
	SDL_Window	*window;
	// SDL_Surface	*screen;
	SDL_GLContext glContext;
	SDL_Event	e;
	t_data		d;

	data_init(&d);
	SDL_Init(SDL_INIT_VIDEO);
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	window = SDL_CreateWindow("Scop", SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_OPENGL);
	glContext = SDL_GL_CreateContext(window);
	// screen = SDL_GetWindowSurface(window);
	d.status = glewInit();
	if(d.status != GLEW_OK)
	{
		printf("error?");
	}
	while (d.run)
	{
		SDL_PollEvent(&e);
		d.run = handleEvent(e);
		glClearColor(0.0f, 0.15f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		update(window);
	}
	quit_scop(glContext , window);

	return 0;
}
