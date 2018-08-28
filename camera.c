#include "scop.h"

void	cam_init(t_vector pos, float fov, float aspect, t_cam *cam)
{
	cam->perspective = cam_perspective(fov, aspect, 0.01f, 1000.0f);
	cam->pos = pos;
	cam->forward = vinit(0.0f, 0.0f, 1.0f);
	cam->up  = vinit(0.0f, 1.0f, 0.0f);
}

t_mat4	cam_getViewProj(t_cam *cam)
{
	return (mat4_mult(cam->perspective, cam_lookAt(cam->pos, vadd(cam->pos, cam->forward), cam->up)));
	// return (cam->perspective);
	// return (cam_lookAt(cam->pos, vadd(cam->pos, cam->forward), cam->up));
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
	y = vcross(z, x);
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

    // const float ar = m_persProj.Width / m_persProj.Height;
    // const float zNear = m_persProj.zNear;
    // const float zFar = m_persProj.zFar;
    // const float zRange = zNear - zFar;
    // const float tanHalfFOV = tanf(ToRadian(m_persProj.FOV / 2.0));

    // m.m[0][0] = 1.0f / (tanHalfFOV * ar); 
    // m.m[0][1] = 0.0f;
    // m.m[0][2] = 0.0f;
    // m.m[0][3] = 0.0f;

    // m.m[1][0] = 0.0f;
    // m.m[1][1] = 1.0f / tanHalfFOV; 
    // m.m[1][2] = 0.0f; 
    // m.m[1][3] = 0.0f;

    // m.m[2][0] = 0.0f; 
    // m.m[2][1] = 0.0f; 
    // m.m[2][2] = (-zNear - zFar) / zRange; 
    // m.m[2][3] = 2.0f * zFar * zNear / zRange;

    // m.m[3][0] = 0.0f;
    // m.m[3][1] = 0.0f; 
    // m.m[3][2] = 1.0f; 
    // m.m[3][3] = 0.0f;


   // f/aspect, 0.0f,    0.0f,  0.0f,
   //      0.0f,    f,    0.0f,  0.0f,
   //      0.0f, 0.0f,    0.0f, -1.0f,
   //      0.0f, 0.0f, 2*zNear,  0.0f


t_mat4	cam_perspective(float fov, float aspect, float zNear, float zFar)
{
	t_mat4	mat;
	float	tanHalfFov;
	float	zRange;

	tanHalfFov = tan(fov * 0.5f * (float)PI / 180.0f);
	zRange = (zNear - zFar);

	mat.a[0][0] = 1.0f / aspect * tanHalfFov;
	mat.a[0][1] = 0.0f;
	mat.a[0][2] = 0.0f;
	mat.a[0][3] = 0.0f;

	mat.a[1][0] = 0.0f;
	mat.a[1][1] = 1.0f / tanHalfFov;
	mat.a[1][2] = 0.0f;
	mat.a[1][3] = 0.0f;

	mat.a[2][0] = 0.0f;
	mat.a[2][1] = 0.0f;
	mat.a[2][2] = (-zNear - zFar) / zRange;
	mat.a[2][3] = 2.0f * zFar * zNear / zRange;

	mat.a[3][0] = 0.0f;
	mat.a[3][1] = 0.0f;
	mat.a[3][2] = 1.0f;
	mat.a[3][3] = 0.0f;

	return (mat);
}