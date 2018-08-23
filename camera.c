#include "scop.h"

void	cam_init(t_vector pos, float fov, float aspect, t_cam *cam)
{
	cam->perspective = cam_perspective(fov, aspect, 0.01f, 100.0f);
	cam->pos = pos;
	cam->forward = vinit(0.0, 0.0, 1.0);
	cam->up  = vinit(0.0, 1.0, 0.0);
}

t_mat4	cam_getViewProj(t_cam *cam)
{
	// return (mat4_mult(cam->perspective, cam_lookAt(cam->pos, vadd(cam->pos, cam->forward), cam->up)));
	return (cam->perspective);
}
/*
  [         xaxis.x          yaxis.x          zaxis.x  0 ]
= [         xaxis.y          yaxis.y          zaxis.y  0 ]
  [         xaxis.z          yaxis.z          zaxis.z  0 ]
  [ dot(xaxis,-eye)  dot(yaxis,-eye)  dot(zaxis,-eye)  1 ]
*/
t_mat4	cam_lookAt(t_vector pos, t_vector dir, t_vector up)
{
	t_mat4 mat;
	t_vector x;
	t_vector y;
	t_vector z;

	z = vsub(pos, dir);
	vnorm(z);
	y = up;
	x = vcross(y, z);
	y = vcross(z, x);
	x = vnorm(x);
	y = vnorm(y);
	mat.a[0][0] = x.x;
	mat.a[0][1] = x.y;
	mat.a[0][2] = x.z;
	mat.a[0][3] = vdot(x, vmul(pos, -1.0));
	mat.a[1][0] = y.x;
	mat.a[1][1] = y.y;
	mat.a[1][2] = y.z;
	mat.a[1][3] = vdot(y, vmul(pos, -1.0));
	mat.a[2][0] = z.x;
	mat.a[2][1] = z.y;
	mat.a[2][2] = z.z;
	mat.a[2][3] = vdot(z, vmul(pos, -1.0));
	mat.a[3][0] = 0.0;
	mat.a[3][1] = 0.0;
	mat.a[3][2] = 0.0;
	mat.a[3][3] = 1.0;
	return (mat);
}

t_mat4	cam_perspective(float fov, float aspect, float zNear, float zFar)
{
	t_mat4	mat;
	float	tanHalfFov = tan(TORADS(fov) / 2.0f);
	float	zRange = (zNear - zFar);

	mat.a[0][0] = 1.0f / (aspect * tanHalfFov);
	mat.a[0][1] = 0.0;
	mat.a[0][2] = 0.0;
	mat.a[0][3] = 0.0;

	mat.a[1][0] = 0.0;
	mat.a[1][1] = 1.0f / (tanHalfFov);
	mat.a[1][2] = 0.0;
	mat.a[1][3] = 0.0;

	mat.a[2][0] = 0.0;
	mat.a[2][1] = 0.0;
	mat.a[2][2] = (-zNear - zFar) / zRange;
	mat.a[2][3] = 2.0f * zFar * zNear / zRange;

	mat.a[3][0] = 0.0;
	mat.a[3][1] = 0.0;
	mat.a[3][2] = 1.0f;
	mat.a[3][3] = 0.0;

	return (mat);
}