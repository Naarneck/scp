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

void	update(t_data *d)
{
	SDL_GL_SwapWindow(d->window);
}

void	quit_scop(t_data *d)
{
	SDL_GL_DeleteContext(d->glcontext);
	SDL_DestroyWindow(d->window);
	SDL_Quit();
}

void	handle_event_tex(SDL_Event event, t_transf *tf, t_texture *tex)
{
	if (event.key.keysym.sym == SDLK_t)
	{
		++tex->id;
		texture_del(tex);
		if (tex->id == 0)
			texture_init("resources/diffuse.bmp", tex);
		else if (tex->id == 1)
			texture_init("resources/ponie.bmp", tex);
		else if (tex->id == 2)
		{
			texture_init(tex->name, tex);
			tex->id = -1;
		}
	}
	else if (event.key.keysym.sym == SDLK_y)
	{
		if (tf->mode == 0)
			tf->mode = 1;
		else
			tf->mode = 0;
	}
}

void	handle_event_obj(SDL_Event event, t_transf *tf)
{
	if (event.key.keysym.sym == SDLK_l)
		tf->pos.x += 0.1;
	else if (event.key.keysym.sym == SDLK_k)
		tf->pos.x -= 0.1;
	else if (event.key.keysym.sym == SDLK_f)
		tf->pos.z += 0.1;
	else if (event.key.keysym.sym == SDLK_g)
		tf->pos.z -= 0.1;
	else if (event.key.keysym.sym == SDLK_h)
		tf->pos.y += 0.1;
	else if (event.key.keysym.sym == SDLK_j)
		tf->pos.y -= 0.1;
	else if (event.key.keysym.sym == SDLK_z)
		tf->rot.y += 0.1;
	else if (event.key.keysym.sym == SDLK_x)
		tf->rot.y -= 0.1;
	else if (event.key.keysym.sym == SDLK_c)
		tf->rot.z += 0.1;
	else if (event.key.keysym.sym == SDLK_v)
		tf->rot.z -= 0.1;
	else if (event.key.keysym.sym == SDLK_b)
		tf->rot.x += 0.1;
	else if (event.key.keysym.sym == SDLK_n)
		tf->rot.x -= 0.1;
}

int		handle_event(SDL_Event event, t_transf *tf, t_cam *cam, t_texture *tex)
{
	if (event.type == SDL_QUIT || (event.type == SDL_KEYDOWN &&
										event.key.keysym.sym == SDLK_ESCAPE))
		return (0);
	if (event.type == SDL_KEYDOWN)
	{
		handle_event_obj(event, tf);
		if (event.key.keysym.sym == SDLK_d)
			cam->pos.x -= 0.1;
		else if (event.key.keysym.sym == SDLK_a)
			cam->pos.x += 0.1;
		else if (event.key.keysym.sym == SDLK_q)
			cam->pos.y -= 0.1;
		else if (event.key.keysym.sym == SDLK_e)
			cam->pos.y += 0.1;
		else if (event.key.keysym.sym == SDLK_s)
			cam->pos.z -= 1.1;
		else if (event.key.keysym.sym == SDLK_w)
			cam->pos.z += 1.1;
		else if (event.key.keysym.sym == SDLK_p)
			tf->scale = vmul(tf->scale, 0.75);
		else if (event.key.keysym.sym == SDLK_o)
			tf->scale = vmul(tf->scale, 1.25);
		handle_event_tex(event, tf, tex);
	}
	return (1);
}

void	sdlgl_init(t_data *d)
{
	d->run = 1;
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	d->window = SDL_CreateWindow("Scop", SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_OPENGL);
	d->glcontext = SDL_GL_CreateContext(d->window);
	glewExperimental = GL_TRUE;
	d->status = glewInit();
	if (d->status != GLEW_OK)
	{
		printf("GLEW ERROR\n");
		exit(0);
	}
	glEnable(GL_DEPTH_CLAMP);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
}

void	data_init(t_data *d)
{
	write(1, "obj loaded\n", 11);
	cam_init(vinit(0.0f, 0.5f, -3.0f - d->obji.far), 70.0f,
							(float)WIDTH / (float)HEIGHT, &d->camera);
	transform_init(vinit(0.0f, 0.0f, 0.0f), vinit(0.0f, 0.0f, 0.0f),
								vinit(1.0f, 1.0f, 1.0f), &d->transform);
	shader_init(&d->shader);
	write(1, "shader loaded\n", 14);
	texture_init("resources/diffuse.bmp", &d->texture);
	write(1, "texture loaded\n", 15);
	mesh_init(&d->mesh, &d->obji);
	write(1, "mesh initialized\n", 17);
}

void	data_del(t_data *d)
{
	shader_del(&d->shader);
	mesh_del(&d->mesh);
	texture_del(&d->texture);
	quit_scop(d);
}

int		print_usage(void)
{
	write(1, "Usage: ./scop [obj path] [texture path]\n", 40);
	write(1, "\tkeys:\n", 7);
	write(1, "\tw,s,a,d,q,e \t- move camera x,y,z\n", 35);
	write(1, "\tf,g,h,j,k,l \t- move object x,y,z\n", 35);
	write(1, "\tz,x,c,v,b,n \t- rotate object\n", 30);
	write(1, "\tt \t\t- apply texture\n", 21);
	write(1, "\ty \t\t- blinking shader\n", 23);
	return (0);
}

int		main(int argc, char **argv)
{
	SDL_Event		e;
	t_data			d;

	d.texture.id = 0;
	if (argc < 2)
		return (print_usage());
	d.texture.name = argc > 2 ? argv[2] : "resources/gr.bmp";
	sdlgl_init(&d);
	obj_loadfile(argv[1], &d.obji);
	data_init(&d);
	while (d.run)
	{
		SDL_PollEvent(&e);
		d.run = handle_event(e, &d.transform, &d.camera, &d.texture);
		glClearColor(0.0f, 0.95f, 0.85f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		shader_update(&d.transform, &d.shader, &d.camera);
		shader_mode_update(&d.shader, &d.transform);
		shader_bind(&d.shader);
		texture_bind(0, &d.texture);
		mesh_draw(&d.mesh);
		update(&d);
	}
	data_del(&d);
	return (0);
}
