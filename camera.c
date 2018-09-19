/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izelensk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/17 17:41:30 by izelensk          #+#    #+#             */
/*   Updated: 2018/09/17 17:41:34 by izelensk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void	cam_init(t_vector pos, float fov, float aspect, t_cam *cam)
{
	cam->perspective = cam_perspective(fov, aspect, 0.01f, 1000.0f);
	cam->pos = pos;
	cam->forward = vinit(0.0f, 0.0f, 1.0f);
	cam->up = vinit(0.0f, 1.0f, 0.0f);
}

t_mat4	cam_lookat(t_vector pos, t_vector dir, t_vector up)
{
	t_mat4		mat;
	t_vector	x;
	t_vector	y;
	t_vector	z;

	z = vnorm(vsub(pos, dir));
	x = vnorm(vcross(up, z));
	y = (vcross(z, x));
	mat.a[0][0] = x.x;
	mat.a[0][1] = y.x;
	mat.a[0][2] = z.x;
	mat.a[0][3] = 0.0;
	mat.a[1][0] = x.y;
	mat.a[1][1] = y.y;
	mat.a[1][2] = z.y;
	mat.a[1][3] = 0.0;
	mat.a[2][0] = x.z;
	mat.a[2][1] = y.z;
	mat.a[2][2] = z.z;
	mat.a[2][3] = 0.0;
	mat.a[3][0] = -1.0 * vdot(x, pos);
	mat.a[3][1] = -1.0 * vdot(y, pos);
	mat.a[3][2] = -1.0 * vdot(z, pos);
	mat.a[3][3] = 1.0;
	return (mat);
}

t_mat4	cam_perspective(float fov, float aspect, float znear, float zfar)
{
	t_mat4	mat;
	float	tanhalffov;
	float	zrange;

	tanhalffov = tan(TORADS(fov * 0.5f));
	zrange = (znear - zfar);
	mat.a[0][0] = 1.0f / (tanhalffov * aspect);
	mat.a[0][1] = 0.0f;
	mat.a[0][2] = 0.0f;
	mat.a[0][3] = 0.0f;
	mat.a[1][0] = 0.0f;
	mat.a[1][1] = 1.0f / tanhalffov;
	mat.a[1][2] = 0.0f;
	mat.a[1][3] = 0.0f;
	mat.a[2][0] = 0.0f;
	mat.a[2][1] = 0.0f;
	mat.a[2][2] = -(-znear - zfar) / zrange;
	mat.a[2][3] = -1.0f;
	mat.a[3][0] = 0.0f;
	mat.a[3][1] = 0.0f;
	mat.a[3][2] = 2.0f * zfar * znear / zrange;
	mat.a[3][3] = 0.0f;
	return (mat);
}
