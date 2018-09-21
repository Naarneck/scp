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

void	quit_scop(t_data *d)
{
	SDL_GL_DeleteContext(d->glcontext);
	SDL_DestroyWindow(d->window);
	SDL_Quit();
}

void	sdlgl_init(t_data *d)
{
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
	d->run = d->obji.status;
	if (!d->run)
	{
		write(1, "file error\n", 11);
		return ;
	}
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
		SDL_GL_SwapWindow(d.window);
	}
	data_del(&d);
	return (0);
}
