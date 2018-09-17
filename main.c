/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izelensk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/17 19:12:21 by izelensk          #+#    #+#             */
/*   Updated: 2018/09/17 19:12:23 by izelensk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
				//MOvE
				case 	SDLK_ESCAPE: 
				{
					return 0;
				}
				case 	SDLK_l: 
				{ 
					tf->pos.x += 0.1;
					break;
				}
				case 	SDLK_k: 
				{
					tf->pos.x -= 0.1;
					break;
				}
				case	SDLK_f: 
				{
					tf->pos.z += 0.1;;
					break;
				}
				case	SDLK_g: 
				{
					tf->pos.z -= 0.1;;
					break;
				}
				case	SDLK_h: 
				{
					tf->pos.y += 0.1;;
					break;
				}
				case	SDLK_j: 
				{
					tf->pos.y -= 0.1;;
					break;
				}
				//SCALE
				case	SDLK_p: 
				{
					tf->scale = vmul(tf->scale, 0.75);
					break;
				}
				case	SDLK_o: 
				{
					tf->scale = vmul(tf->scale, 1.25);
					break;
				}
				//ROTATE
				case	SDLK_z: 
				{
					tf->rot.y += 0.1;
					break;
				}
				case	SDLK_x: 
				{
					tf->rot.y -= 0.1;
					break;
				}
				case	SDLK_c:
				{
					tf->rot.z += 0.1;
					break;
				}
				case	SDLK_v: 
				{
					tf->rot.z -= 0.1;
					break;
				}
				case	SDLK_b:
				{
					tf->rot.x += 0.1;
					break;
				}
				case	SDLK_n: 
				{
					tf->rot.x -= 0.1;
					break;
				}
				//WASDECAM
				case	SDLK_d: 
				{
					cam->pos.x -= 0.1;
					break;
				}
				case	SDLK_a: 
				{
					cam->pos.x += 0.1;
					break;
				}
				case	SDLK_q: 
				{
					cam->pos.y -= 0.1;
					break;
				}
				case	SDLK_e: 
				{
					cam->pos.y += 0.1;
					break;
				}
				case	SDLK_s: 
				{
					cam->pos.z -= 1.1;
					break;
				}
				case	SDLK_w: 
				{
					cam->pos.z += 1.1;
					break;
				}
				case	SDLK_t: 
				{
					write(1,"t\n",2);
					++tex->id;
					texture_del(tex);
					if (tex->id == 0)
						texture_init("resources/diffuse.bmp", tex);
					else if (tex->id == 1)
					{
						texture_init("resources/ponie.bmp", tex);
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

	texture.id = 0;
	if (argc < 2)
	{
		write(1, "Usage: ./scop [obj path] [texture path]\n", 40);
		write(1, "\tkeys:\n", 7);
		write(1, "\tw,s,a,d,q,e \t- move camera x,y,z\n", 35);
		write(1, "\tf,g,h,j,k,l \t- move object x,y,z\n", 35);
		write(1, "\tz,x,c,v,b,n \t- rotate object\n", 30);
		write(1, "\tf,g,h,j\t\t- move camera\n", 24);
		write(1, "\tt \t\t- apply texture\n", 21);
		write(1, "\ty \t\t- blinking shader\n", 23);
		return (0);
	}

	if (argc >= 3)
		texture.name = argv[2];
	else
		texture.name = "resources/gr.bmp";
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
	obj_loadFile(argv[1], &obji);
	write(1,"obj loaded\n",11);
	cam_init(vinit(0.0f, 0.5f, -3.0f - obji.far), 70.0f, (float)WIDTH / (float)HEIGHT, &camera);
	transform_init(vinit(0.0f, 0.0f, 0.0f), vinit(0.0f, 0.0f, 0.0f), vinit(1.0f, 1.0f, 1.0f), &transform);
	shader_init(&shader);
	write(1,"shader loaded\n",14);
	texture_init("resources/diffuse.bmp", &texture);
	write(1,"texture loaded\n",15);
	mesh_init(&mesh, &obji);
	write(1,"mesh initialized\n",17);
	while (d.run)
	{
		SDL_PollEvent(&e);
		d.run = handleEvent(e, &transform, &camera, &texture);
		glClearColor(0.0f, 0.95f, 0.85f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT  | GL_DEPTH_BUFFER_BIT);
		// glClear(GL_COLOR_BUFFER_BIT);
		shader_update(&transform, &shader, &camera);
		shader_mode_update(&shader, &transform);
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
