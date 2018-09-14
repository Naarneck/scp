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

int		handleEvent(SDL_Event event, t_transf *tf, t_cam *cam, t_texture *tex)
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
					tf->scale = vmul(tf->scale, 0.75);
					break;
				}
				case	SDLK_e: 
				{
					write(1,"e\n",2);
					tf->scale = vmul(tf->scale, 1.25);
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
				case	SDLK_h: 
				{
					write(1,"h\n",2);
					cam->pos.y -= 0.1;
					break;
				}
				case	SDLK_j: 
				{
					write(1,"j\n",2);
					cam->pos.y += 0.1;
					break;
				}
				case	SDLK_k: 
				{
					write(1,"k\n",2);
					cam->pos.z -= 1.1;
					break;
				}
				case	SDLK_l: 
				{
					write(1,"l\n",2);
					cam->pos.z += 1.1;
					break;
				}
				case	SDLK_t: 
				{
					write(1,"t\n",2);
					++tex->id;
					texture_del(tex);
					if (tex->id == 0)
						texture_init("resources/gr.bmp", tex);
					else if (tex->id == 1)
					{
						texture_init("resources/diff.bmp", tex);
					}
					else if (tex->id == 2)
					{
						texture_init(tex->name, tex);
						tex->id = -1;
					}
					break;
				}
				case	SDLK_y: 
				{
					write(1,"y\n",2);
					if (tf->mode == 0)
						tf->mode = 1;
					else 
						tf->mode = 0;
					printf("moooooooododddddddeeeeeeeee :%d \n", tf->mode);
					break;
				}
			}
	}
	return 1;
}

int main(int argc, char **argv)
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
	texture.id = 0;
	if (argc < 2)
	{
		write(1, "Usage: ./scop [obj path] [texture path]\n", 40);
		write(1, "\tkeys:\n", 7);
		write(1, "\tw,a,s,d \t- move object x,y,z\n", 30);
		write(1, "\tq,e \t- scale object\n", 21);
		write(1, "\tz,x,c,v,b,n \t- rotate object\n", 30);
		write(1, "\tf,g,h,j\t- move camera\n", 23);
		write(1, "\tt \t- apply texture\n", 20);
		return (0);
	}
	if (argc >= 3)
		texture.name = argv[2];
	data_init(&d);
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
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
	glEnable(GL_DEPTH_CLAMP);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK); 
	//teapot teapot2 uno drink cat bird Lumia_650 CSH/csh
	obj_loadFile(argv[1], &obji);
	write(1,"obj loaded\n",11);
	// printf("numNormals: %u numPositions: %u numTex: %u numIndices: %u\n",
	// 	obji.numNormals, obji.numPositions, obji.numTex, obji.numIndices);
	// vertices = obji.vertices;
	// indices = obji.indices;
	cam_init(vinit(0.0f, 0.5f, -3.0f - obji.far), 70.0f, (float)WIDTH / (float)HEIGHT, &camera);
	transform_init(vinit(0.0f, 0.0f, 0.0f), vinit(0.0f, 0.0f, 0.0f), vinit(1.0f, 1.0f, 1.0f), &transform);
	shader_init("shaders/basic", &shader);
	write(1,"shader loaded\n",14);
	texture_init("resources/gr.bmp", &texture);
	write(1,"texture loaded\n",15);
	// mesh_init(vertices, sizeof(vertices) / sizeof(vertices[0]), indices, sizeof(indices) / sizeof(indices[0]), &mesh);
	// printf("f:%u vn:%u vt:%u v:%u\n", obji.numIndices, obji.numNormals, obji.numTex, obji.numPositions);
	mesh_init(&mesh, &obji);
	write(1,"mesh initialized\n",17);
	while (d.run)
	{
		write(1,"loop started\n",14);
		// printf("kek\n");
		SDL_PollEvent(&e);
		d.run = handleEvent(e, &transform, &camera, &texture);
		glClearColor(0.0f, 0.95f, 0.85f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT  | GL_DEPTH_BUFFER_BIT);
		// glClear(GL_COLOR_BUFFER_BIT);
		shader_update(&transform, &shader, &camera);
		shader_mode_update(&shader, &transform);
		write(1,"texture updated\n",16);
		write(1,"loop started\n",14);
		shader_bind(&shader);
		write(1,"shader binded\n",14);
		texture_bind(0, &texture);
		write(1,"texture binded\n",15);
		mesh_draw(&mesh);
		write(1,"mesh draw\n",10);
		update(&d);
	}
	shader_del(&shader);
	mesh_del(&mesh);
	texture_del(&texture);
	quit_scop(&d);
	return 0;
}
