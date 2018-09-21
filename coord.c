/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coord.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izelensk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/07 16:48:57 by izelensk          #+#    #+#             */
/*   Updated: 2017/07/07 16:48:59 by izelensk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

t_coord		cinit(float x, float y)
{
	t_coord	vec;

	vec.x = x;
	vec.y = y;
	return (vec);
}

t_coord		cmul(t_coord v1, float l)
{
	v1.x *= l;
	v1.y *= l;
	return (v1);
}

t_coord		cnorm(t_coord v1)
{
	float	length;

	length = clen(v1);
	v1.x /= length;
	v1.y /= length;
	return (v1);
}

float		cdot(t_coord v1, t_coord v2)
{
	return ((v1.x * v2.x) + (v1.y * v2.y));
}

float		clen(t_coord v1)
{
	return (sqrt((v1.x * v1.x) + (v1.y * v1.y)));
}
