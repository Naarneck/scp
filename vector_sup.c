/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_sup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izelensk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/21 15:24:39 by izelensk          #+#    #+#             */
/*   Updated: 2018/09/21 15:24:40 by izelensk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

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

t_vector	vcalcnormal(t_vector p0, t_vector p1, t_vector p2)
{
	t_vector n;
	t_vector a;
	t_vector b;

	a = vsub(p1, p0);
	b = vsub(p2, p1);
	n.x = a.y * b.z - a.z * b.y;
	n.y = a.z * b.x - a.x * b.z;
	n.z = a.x * b.y - a.y * b.x;
	return (vnorm(n));
}

float		vmax(t_vector vec)
{
	vec.x = fabs(vec.x);
	vec.y = fabs(vec.y);
	vec.z = fabs(vec.z);
	vec.x = vec.x > vec.y ? vec.x : vec.y;
	vec.z = vec.z > vec.x ? vec.z : vec.x;
	return (vec.z);
}
