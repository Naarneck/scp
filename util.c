/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izelensk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/17 19:25:01 by izelensk          #+#    #+#             */
/*   Updated: 2018/09/17 19:25:22 by izelensk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

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
