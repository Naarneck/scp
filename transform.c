/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izelensk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/17 19:29:29 by izelensk          #+#    #+#             */
/*   Updated: 2018/09/17 19:29:30 by izelensk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void	transform_init(t_vector pos, t_vector rot, t_vector scale, t_transf *tf)
{
	tf->pos.x = pos.x;
	tf->pos.y = pos.y;
	tf->pos.z = pos.z;
	tf->rot.x = rot.x;
	tf->rot.y = rot.y;
	tf->rot.z = rot.z;
	tf->scale.x = scale.x;
	tf->scale.y = scale.y;
	tf->scale.z = scale.z;
	tf->mode = 1;
	tf->loop = 0.0;
}

t_mat4	transform_getmodel(t_transf *tf)
{
	t_model	model;

	model.pos = mat4_translate(tf->pos);
	model.rotx = mat4_rotatex(tf->rot.x);
	model.roty = mat4_rotatey(tf->rot.y);
	model.rotz = mat4_rotatez(tf->rot.z);
	model.scale = mat4_scale(tf->scale);
	model.rot = mat4_mult(mat4_mult(model.rotx, model.roty), model.rotz);
	return (mat4_mult(mat4_mult(model.scale, model.rot), model.pos));
}
