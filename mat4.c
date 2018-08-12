#include "scop.h"

t_mat4 	mat4_mult(t_mat4 a, t_mat4 b)
{
	t_mat4 m;

    m.a[0][0] = a.a[0][0] * b.a[0][0] + a.a[0][1] * b.a[1][0] + a.a[0][2] * b.a[2][0] + a.a[0][3] * b.a[3][0];
    m.a[0][1] = a.a[0][0] * b.a[0][1] + a.a[0][1] * b.a[1][1] + a.a[0][2] * b.a[2][1] + a.a[0][3] * b.a[3][1];
    m.a[0][2] = a.a[0][0] * b.a[0][2] + a.a[0][1] * b.a[1][2] + a.a[0][2] * b.a[2][2] + a.a[0][3] * b.a[3][2];
    m.a[0][3] = a.a[0][0] * b.a[0][3] + a.a[0][1] * b.a[1][3] + a.a[0][2] * b.a[2][3] + a.a[0][3] * b.a[3][3];
    m.a[1][0] = a.a[1][0] * b.a[0][0] + a.a[1][1] * b.a[1][0] + a.a[1][2] * b.a[2][0] + a.a[1][3] * b.a[3][0];
    m.a[1][1] = a.a[1][0] * b.a[0][1] + a.a[1][1] * b.a[1][1] + a.a[1][2] * b.a[2][1] + a.a[1][3] * b.a[3][1];
    m.a[1][2] = a.a[1][0] * b.a[0][2] + a.a[1][1] * b.a[1][2] + a.a[1][2] * b.a[2][2] + a.a[1][3] * b.a[3][2];
    m.a[1][3] = a.a[1][0] * b.a[0][3] + a.a[1][1] * b.a[1][3] + a.a[1][2] * b.a[2][3] + a.a[1][3] * b.a[3][3];
    m.a[2][0] = a.a[2][0] * b.a[0][0] + a.a[2][1] * b.a[1][0] + a.a[2][2] * b.a[2][0] + a.a[2][3] * b.a[3][0];
    m.a[2][1] = a.a[2][0] * b.a[0][1] + a.a[2][1] * b.a[1][1] + a.a[2][2] * b.a[2][1] + a.a[2][3] * b.a[3][1];
    m.a[2][2] = a.a[2][0] * b.a[0][2] + a.a[2][1] * b.a[1][2] + a.a[2][2] * b.a[2][2] + a.a[2][3] * b.a[3][2];
    m.a[2][3] = a.a[2][0] * b.a[0][3] + a.a[2][1] * b.a[1][3] + a.a[2][2] * b.a[2][3] + a.a[2][3] * b.a[3][3];
    m.a[3][0] = a.a[3][0] * b.a[0][0] + a.a[3][1] * b.a[1][0] + a.a[3][2] * b.a[2][0] + a.a[3][3] * b.a[3][0];
    m.a[3][1] = a.a[3][0] * b.a[0][1] + a.a[3][1] * b.a[1][1] + a.a[3][2] * b.a[2][1] + a.a[3][3] * b.a[3][1];
    m.a[3][2] = a.a[3][0] * b.a[0][2] + a.a[3][1] * b.a[1][2] + a.a[3][2] * b.a[2][2] + a.a[3][3] * b.a[3][2];
    m.a[3][3] = a.a[3][0] * b.a[0][3] + a.a[3][1] * b.a[1][3] + a.a[3][2] * b.a[2][3] + a.a[3][3] * b.a[3][3];
    return(m);
}

// t_mat4	mat4_translate(t_vector pos)
// {
// 	t_mat4 tr;

// 	tr.a[0][0] = 1;
// 	tr.a[0][1] = 0;
// 	tr.a[0][2] = 0;
// 	tr.a[0][3] = pos.x;

// 	tr.a[1][0] = 0;
// 	tr.a[1][1] = 1;
// 	tr.a[1][2] = 0;
// 	tr.a[1][3] = pos.y;

// 	tr.a[2][0] = 0;
// 	tr.a[2][1] = 0;
// 	tr.a[2][2] = 1;
// 	tr.a[2][3] = pos.z;

// 	tr.a[3][0] = 0;
// 	tr.a[3][1] = 0;
// 	tr.a[3][2] = 0;
// 	tr.a[3][3] = 1;

// 	return (tr);
// }

t_mat4	mat4_translate(t_vector pos)
{
	t_mat4 tr;

	tr.a[0][0] = 1;
	tr.a[0][1] = 0;
	tr.a[0][2] = 0;
	tr.a[0][3] = 0;

	tr.a[1][0] = 0;
	tr.a[1][1] = 1;
	tr.a[1][2] = 0;
	tr.a[1][3] = 0;

	tr.a[2][0] = 0;
	tr.a[2][1] = 0;
	tr.a[2][2] = 1;
	tr.a[2][3] = 0;

	tr.a[3][0] = pos.x;
	tr.a[3][1] = pos.y;
	tr.a[3][2] = pos.z;
	tr.a[3][3] = 1;

	return (tr);
}

t_mat4	mat4_rotateX(float ang)
{
	t_mat4 tr;
	
	tr.a[0][0] = 1;
	tr.a[0][1] = 0;
	tr.a[0][2] = 0;
	tr.a[0][3] = 0;

	tr.a[1][0] = 0;
	tr.a[1][1] = cos(ang);
	tr.a[1][2] = sin(ang);
	tr.a[1][3] = 0;
 
	tr.a[2][0] = 0;
	tr.a[2][1] = -sin(ang);
	tr.a[2][2] = cos(ang);
	tr.a[2][3] = 0;

	tr.a[3][0] = 0;
	tr.a[3][1] = 0;
	tr.a[3][2] = 0;
	tr.a[3][3] = 1;

	return (tr);	
}

t_mat4	mat4_rotateY(float ang)
{
	t_mat4 tr;

	tr.a[0][0] = cos(ang);
	tr.a[0][1] = 0;
	tr.a[0][2] = sin(ang);
	tr.a[0][3] = 0;

	tr.a[1][0] = 0;
	tr.a[1][1] = 1;
	tr.a[1][2] = 0;
	tr.a[1][3] = 0;

	tr.a[2][0] = -sin(ang);
	tr.a[2][1] = 0;
	tr.a[2][2] = cos(ang);
	tr.a[2][3] = 0;

	tr.a[3][0] = 0;
	tr.a[3][1] = 0;
	tr.a[3][2] = 0;
	tr.a[3][3] = 1;

	return (tr);	
}

t_mat4	mat4_rotateZ(float ang)
{
	t_mat4 tr;

	tr.a[0][0] = cos(ang);
	tr.a[0][1] = sin(ang);
	tr.a[0][2] = 0;
	tr.a[0][3] = 0;

	tr.a[1][0] = -sin(ang);
	tr.a[1][1] = cos(ang);
	tr.a[1][2] = 0;
	tr.a[1][3] = 0;

	tr.a[2][0] = 0;
	tr.a[2][1] = 0;
	tr.a[2][2] = 1;
	tr.a[2][3] = 0;

	tr.a[3][0] = 0;
	tr.a[3][1] = 0;
	tr.a[3][2] = 0;
	tr.a[3][3] = 1;

	return (tr);	
}

t_mat4	mat4_scale(t_vector sc)
{
	t_mat4 tr;

	tr.a[0][0] = sc.x;
	tr.a[0][1] = 0;
	tr.a[0][2] = 0;
	tr.a[0][3] = 0;

	tr.a[1][0] = 0;
	tr.a[1][1] = sc.y;
	tr.a[1][2] = 0;
	tr.a[1][3] = 0;

	tr.a[2][0] = 0;
	tr.a[2][1] = 0;
	tr.a[2][2] = sc.z;
	tr.a[2][3] = 0;

	tr.a[3][0] = 0;
	tr.a[3][1] = 0;
	tr.a[3][2] = 0;
	tr.a[3][3] = 1;

	return (tr);	
}

t_mat4	mat4_transpose(t_mat4 src)
{
	t_mat4 tr;

	tr.a[0][0] = src.a[0][0];
	tr.a[0][1] = src.a[1][0];
	tr.a[0][2] = src.a[2][0];
	tr.a[0][3] = src.a[3][0];

	tr.a[1][0] = src.a[0][1];
	tr.a[1][1] = src.a[1][1];
	tr.a[1][2] = src.a[2][1];
	tr.a[1][3] = src.a[3][1];

	tr.a[2][0] = src.a[0][2];
	tr.a[2][1] = src.a[1][2];
	tr.a[2][2] = src.a[2][2];
	tr.a[2][3] = src.a[3][2];

	tr.a[3][0] = src.a[0][3];
	tr.a[3][1] = src.a[1][3];
	tr.a[3][2] = src.a[2][3];
	tr.a[3][3] = src.a[3][3];

	return (tr);	
}
