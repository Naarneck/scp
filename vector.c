/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izelensk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/07 16:48:57 by izelensk          #+#    #+#             */
/*   Updated: 2017/07/07 16:48:59 by izelensk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

t_vector	vinit(float x, float y, float z)
{
	t_vector	vec;

	vec.x = x;
	vec.y = y;
	vec.z = z;
	return (vec);
}

t_vector	vsub(t_vector v1, t_vector v2)
{
	v1.x -= v2.x;
	v1.y -= v2.y;
	v1.z -= v2.z;
	return (v1);
}

t_vector	vadd(t_vector v1, t_vector v2)
{
	v1.x += v2.x;
	v1.y += v2.y;
	v1.z += v2.z;
	return (v1);
}

t_vector	vmul(t_vector v1, float l)
{
	v1.x *= l;
	v1.y *= l;
	v1.z *= l;
	return (v1);
}

t_vector	vnorm(t_vector v1)
{
	float	length;

	length = vlen(v1);
	if (length == 0.0)
		return (vinit(0.0, 0.0, 0.0));
	v1.x /= length;
	v1.y /= length;
	v1.z /= length;
	return (v1);
}

float		vdot(t_vector v1, t_vector v2)
{
	return ((v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z));
}

float		vlen(t_vector v1)
{
	return (sqrt((v1.x * v1.x) + (v1.y * v1.y) + (v1.z * v1.z)));
}

t_vector	vcross(t_vector v1, t_vector v2)
{
	t_vector vec;

	vec.x = v1.y * v2.z - v1.z * v2.y;
	vec.y = v1.z * v2.x - v1.x * v2.z;
	vec.z = v1.x * v2.y - v1.y * v2.x;
	return (vec);
}

t_vertex	vertex_init(t_vector pos, t_coord uv)
{
	t_vertex	vert;

	vert.pos.x = pos.x;
	vert.pos.y = pos.y;
	vert.pos.z = pos.z;
	vert.uv.x = uv.x;
	vert.uv.y = uv.y;
	return (vert);
}

t_vector	vertex_getPos(t_vertex vertex)
{
	t_vector	vec;

	vec.x = vertex.pos.x;
	vec.y = vertex.pos.y;
	vec.z = vertex.pos.z;
	return (vec);
}

t_coord		vertex_getUV(t_vertex vertex)
{
	t_coord	coord;

	coord.x = vertex.uv.x;
	coord.y = vertex.uv.y;
	return (coord);
}

t_vector	vcalcNormal(t_vector p0, t_vector p1 ,t_vector p2)
{
	t_vector n;
	t_vector a;
	t_vector b;

	a = vsub(p1, p0);
	b = vsub(p2, p1);
	// printf("a_pos   :  %f / %f / %f\n", a.x, a.y, a.z);
	// printf("b_pos   :  %f / %f / %f\n", b.x, b.y, b.z);
	n.x = a.y * b.z - a.z * b.y;
	n.y = a.z * b.x - a.x * b.z;
	n.z = a.x * b.y - a.y * b.x;
	// printf("n_pos   :  %f / %f / %f\n", n.x, n.y, n.z);
	return (vnorm(n));
}

float	vmax(t_vector vec)
{
	vec.x = fabs(vec.x);
	vec.y = fabs(vec.y);
	vec.z = fabs(vec.z);
	vec.x = vec.x > vec.y ? vec.x : vec.y;
	vec.z = vec.z > vec.x ? vec.z : vec.x;
	return (vec.z);
}

