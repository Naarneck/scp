#include "scop.h"

void	data_init(t_data *d)
{
	d->run = 1;
}

void	update(t_data *d)
{
	SDL_GL_SwapWindow(d->window);
}

void	quit_scop(t_data *d)
{
	// SDL_FreeSurface(screen);
	SDL_GL_DeleteContext(d->glContext);
	SDL_DestroyWindow(d->window);
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
	SDL_Event		e;
	t_data			d;
	t_mesh 			mesh;
	t_shader		shader;
	t_texture		texture;

	t_vertex vertices[] = {vertex_init(vinit(-0.5, -0.5, 0.0), cinit(0.0, 0.0)),
							vertex_init(vinit(0.0, 0.5, 0.0), cinit(0.5, 1.0)),
							vertex_init(vinit(0.5, -0.5, 0.0), cinit(1.0, 0.0))};

	data_init(&d);
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	d.window = SDL_CreateWindow("Scop", SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_OPENGL);
	d.glContext = SDL_GL_CreateContext(d.window);
	glewExperimental = GL_TRUE;
	d.status = glewInit();

	if(d.status != GLEW_OK)
	{
		printf("error?");
	}
	shader_init("shaders/basic", &shader);
	texture_init("resources/pusheen.jpg", &texture);
	mesh_init(vertices, sizeof(vertices) / sizeof(vertices[0]), &mesh);
	
	while (d.run)
	{
		SDL_PollEvent(&e);
		d.run = handleEvent(e);
		glClearColor(0.0f, 0.15f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		shader_bind(&shader);
		texture_bind(0, &texture);
		mesh_draw(&mesh);
		update(&d);
	}
	shader_del(&shader);
	mesh_del(&mesh);
	texture_del(&texture);
	quit_scop(&d);
	return 0;
}
