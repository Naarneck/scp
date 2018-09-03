#include "scop.h"

void	cam_init(t_vector pos, float fov, float aspect, t_cam *cam)
{
	cam->perspective = cam_perspective(fov, aspect, 0.01f, 1000.0f);
	cam->pos = pos;
	cam->forward = vinit(0.0f, 0.0f, 1.0f);
	cam->up  = vinit(0.0f, 1.0f, 0.0f);
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

t_mat4	cam_perspective(float fov, float aspect, float zNear, float zFar)
{
	t_mat4	mat;
	float	tanHalfFov;
	float	zRange;

	tanHalfFov = tan(TORADS(fov * 0.5f));
	zRange = (zNear - zFar);
	printf("aspect: %f\n", aspect);
	mat.a[0][0] = 1.0f / (tanHalfFov * aspect); //>?
	mat.a[0][1] = 0.0f;
	mat.a[0][2] = 0.0f;
	mat.a[0][3] = 0.0f;

	mat.a[1][0] = 0.0f;
	mat.a[1][1] = 1.0f / tanHalfFov;
	mat.a[1][2] = 0.0f;
	mat.a[1][3] = 0.0f;

	mat.a[2][0] = 0.0f;
	mat.a[2][1] = 0.0f;
	mat.a[2][2] = -(-zNear - zFar) / zRange; // - (-0.1) 
	mat.a[2][3] = -1.0f;

	mat.a[3][0] = 0.0f;
	mat.a[3][1] = 0.0f;
	mat.a[3][2] = 2.0f * zFar * zNear / zRange;
	mat.a[3][3] = 0.0f;

	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			printf("%f ", mat.a[i][j]);
		}
		printf("\n");
	}
	// sleep(500);
	return (mat);
}