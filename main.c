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
	SDL_Window		*window;
	SDL_GLContext	glContext;
	SDL_Event		e;
	t_data			d;
	t_mesh 			mesh;
	t_shader		shader;

	t_vertex vertices[] = {vertex_init(vinit(-0.2, -0.5, 0.0)),
							vertex_init(vinit(0.0, 0.5, 0.0)),
							vertex_init(vinit(0.5, -0.5, 0.0))};

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
	glewExperimental = GL_TRUE;
	d.status = glewInit();

	if(d.status != GLEW_OK)
	{
		printf("error?");
	}
	shader_init("shaders/basic", &shader);
	mesh_init(vertices, sizeof(vertices) / sizeof(vertices[0]), &mesh);
	
	while (d.run)
	{
		SDL_PollEvent(&e);
		d.run = handleEvent(e);
		
		glClearColor(1.0f, 0.45f, 0.3f, 1.0f);
		mesh_draw(&mesh);

		update(window);
	}
	mesh_del(&mesh);
	quit_scop(glContext , window);
	return 0;
}
