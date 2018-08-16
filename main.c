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

int		handleEvent(SDL_Event event, t_transf *tf, t_cam *cam)
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
				case 	SDLK_w: 
				{ 
					write(1,"w\n",2);
					tf->pos.x += 0.1;
					break;
				}
				case 	SDLK_s: 
				{
					write(1,"s\n",2);
					tf->pos.x -= 0.1;
					break;
				}
				case	SDLK_a: 
				{
					write(1,"a\n",2);
					tf->pos.y += 0.1;;
					break;
				}
				case	SDLK_d: 
				{
					write(1,"d\n",2);
					tf->pos.y -= 0.1;;
					break;
				}
				case	SDLK_q: 
				{
					write(1,"q\n",2);
					tf->scale = vmul(tf->scale, 0.5);
					break;
				}
				case	SDLK_e: 
				{
					write(1,"e\n",2);
					tf->scale = vmul(tf->scale, 1.5);
					break;
				}
				case	SDLK_z: 
				{
					write(1,"z\n",2);
					tf->rot.y += 0.1;
					break;
				}
				case	SDLK_x: 
				{
					write(1,"x\n",2);
					tf->rot.y -= 0.1;
					break;
				}
				case	SDLK_c:
				{
					write(1,"c\n",2);
					tf->rot.z += 0.1;
					break;
				}
				case	SDLK_v: 
				{
					write(1,"v\n",2);
					tf->rot.z -= 0.1;
					break;
				}
				case	SDLK_b:
				{
					write(1,"b\n",2);
					tf->rot.x += 0.1;
					break;
				}
				case	SDLK_n: 
				{
					write(1,"n\n",2);
					tf->rot.x -= 0.1;
					break;
				}
				case	SDLK_f: 
				{
					write(1,"f\n",2);
					cam->pos.x -= 0.1;
					break;
				}
				case	SDLK_g: 
				{
					write(1,"g\n",2);
					cam->pos.x += 0.1;
					break;
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
	t_transf		transform;
	t_cam 			camera;
	t_objIndex		obji;

	// t_vertex 		vertices[]		 = {vertex_init(vinit(-0.5, -0.5, 0.0), cinit(0.0, 0.0)),
	// 						vertex_init(vinit(0.0, 0.5, 0.0), cinit(0.5, 1.0)),
	// 						vertex_init(vinit(0.5, -0.5, 0.0), cinit(1.0, 0.0))};
	// unsigned int 	indices[] = {0, 1, 2};

	t_vertex 		*vertices;
	unsigned int 	*indices;

	data_init(&d);
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
	// SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	d.window = SDL_CreateWindow("Scop", SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_OPENGL);
	d.glContext = SDL_GL_CreateContext(d.window);
	glewExperimental = GL_TRUE;
	d.status = glewInit();

	if(d.status != GLEW_OK)
	{
		printf("error?\n");
	}
	// glEnable(GL_DEPTH_TEST);
	// glEnable(GL_CULL_FACE);
	// glCullFace(GL_BACK); 
	//teapot teapot2 uno drink cat bird
	obj_loadFile("resources/bird.obj", &obji);
	vertices = obji.vertices;
	indices = obji.indices;
	cam_init(vinit(0.0, 0.0, -1.0), 66.0f, (float)((float)WIDTH / (float)HEIGHT), &camera);
	transform_init(vinit(0.0, 0.0, 0.0), vinit(0.0, 0.0, 0.0), vinit(1.0, 1.0, 1.0), &transform);
	shader_init("shaders/basic", &shader);
	texture_init("resources/pusheen.jpg", &texture);
	// mesh_init(vertices, sizeof(vertices) / sizeof(vertices[0]), indices, sizeof(indices) / sizeof(indices[0]), &mesh);
	// printf("f:%u vn:%u vt:%u v:%u\n", obji.numIndices, obji.numNormals, obji.numTex, obji.numPositions);
	mesh_init(vertices, obji.numPositions, indices, obji.numIndices, &mesh);
	while (d.run)
	{
		// printf("kek\n");
		SDL_PollEvent(&e);
		d.run = handleEvent(e, &transform, &camera);
		glClearColor(0.0f, 0.15f, 0.3f, 1.0f);
		// glClear(GL_COLOR_BUFFER_BIT  | GL_DEPTH_BUFFER_BIT);
		glClear(GL_COLOR_BUFFER_BIT);
		shader_bind(&shader);
		texture_bind(0, &texture);
		shader_update(&transform, &shader, &camera);
		mesh_draw(&mesh);
		update(&d);
	}
	shader_del(&shader);
	mesh_del(&mesh);
	texture_del(&texture);
	quit_scop(&d);
	return 0;
}
