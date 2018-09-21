/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat4.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izelensk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/17 19:12:37 by izelensk          #+#    #+#             */
/*   Updated: 2018/09/17 19:12:39 by izelensk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

t_mat4		mat4_translate(t_vector pos)
{
	t_mat4	tr;

	tr.a[0][0] = 1.0f;
	tr.a[0][1] = 0.0f;
	tr.a[0][2] = 0.0f;
	tr.a[0][3] = 0.0f;
	tr.a[1][0] = 0.0f;
	tr.a[1][1] = 1.0f;
	tr.a[1][2] = 0.0f;
	tr.a[1][3] = 0.0f;
	tr.a[2][0] = 0.0f;
	tr.a[2][1] = 0.0f;
	tr.a[2][2] = 1.0f;
	tr.a[2][3] = 0.0f;
	tr.a[3][0] = pos.x;
	tr.a[3][1] = pos.y;
	tr.a[3][2] = pos.z;
	tr.a[3][3] = 1.0f;
	return (tr);
}

t_mat4		mat4_rotatex(float ang)
{
	t_mat4	tr;

	tr.a[0][0] = 1.0f;
	tr.a[0][1] = 0.0f;
	tr.a[0][2] = 0.0f;
	tr.a[0][3] = 0.0f;
	tr.a[1][0] = 0.0f;
	tr.a[1][1] = cos(ang);
	tr.a[1][2] = sin(ang);
	tr.a[1][3] = 0.0f;
	tr.a[2][0] = 0.0f;
	tr.a[2][1] = -sin(ang);
	tr.a[2][2] = cos(ang);
	tr.a[2][3] = 0.0f;
	tr.a[3][0] = 0.0f;
	tr.a[3][1] = 0.0f;
	tr.a[3][2] = 0.0f;
	tr.a[3][3] = 1.0f;
	return (tr);
}

t_mat4		mat4_rotatey(float ang)
{
	t_mat4	tr;

	tr.a[0][0] = cos(ang);
	tr.a[0][1] = 0.0f;
	tr.a[0][2] = sin(ang);
	tr.a[0][3] = 0.0f;
	tr.a[1][0] = 0.0f;
	tr.a[1][1] = 1;
	tr.a[1][2] = 0.0f;
	tr.a[1][3] = 0.0f;
	tr.a[2][0] = -sin(ang);
	tr.a[2][1] = 0.0f;
	tr.a[2][2] = cos(ang);
	tr.a[2][3] = 0.0f;
	tr.a[3][0] = 0.0f;
	tr.a[3][1] = 0.0f;
	tr.a[3][2] = 0.0f;
	tr.a[3][3] = 1.0f;
	return (tr);
}

t_mat4		mat4_rotatez(float ang)
{
	t_mat4	tr;

	tr.a[0][0] = cos(ang);
	tr.a[0][1] = sin(ang);
	tr.a[0][2] = 0.0f;
	tr.a[0][3] = 0.0f;
	tr.a[1][0] = -sin(ang);
	tr.a[1][1] = cos(ang);
	tr.a[1][2] = 0.0f;
	tr.a[1][3] = 0.0f;
	tr.a[2][0] = 0.0f;
	tr.a[2][1] = 0.0f;
	tr.a[2][2] = 1.0f;
	tr.a[2][3] = 0.0f;
	tr.a[3][0] = 0.0f;
	tr.a[3][1] = 0.0f;
	tr.a[3][2] = 0.0f;
	tr.a[3][3] = 1.0f;
	return (tr);
}

t_mat4		mat4_scale(t_vector sc)
{
	t_mat4	tr;

	tr.a[0][0] = sc.x;
	tr.a[0][1] = 0.0f;
	tr.a[0][2] = 0.0f;
	tr.a[0][3] = 0.0f;
	tr.a[1][0] = 0.0f;
	tr.a[1][1] = sc.y;
	tr.a[1][2] = 0.0f;
	tr.a[1][3] = 0.0f;
	tr.a[2][0] = 0.0f;
	tr.a[2][1] = 0.0f;
	tr.a[2][2] = sc.z;
	tr.a[2][3] = 0.0f;
	tr.a[3][0] = 0.0f;
	tr.a[3][1] = 0.0f;
	tr.a[3][2] = 0.0f;
	tr.a[3][3] = 1.0f;
	return (tr);
}
