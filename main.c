#include "scop.h"

void	data_init(t_data *d)
{
	d->run = 1;
}

void	quit_scop(SDL_Surface	*screen, SDL_Window	*window)
{
	SDL_FreeSurface(screen);
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
	SDL_Surface	*screen;
	SDL_Event	e;
	t_data		d;

	data_init(&d);
	SDL_Init(SDL_INIT_VIDEO);
	window =SDL_CreateWindow("Scop", SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_OPENGL);
	screen = SDL_GetWindowSurface(window);
	while (d.run)
	{
		SDL_PollEvent(&e);
		d.run = handleEvent(e);
	}
	quit_scop(screen , window);

	return 0;
}
