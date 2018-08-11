
void	transform(t_vector pos, t_vector rot, t_vector scale, t_transf *tf)
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
}

t_mat4 	mat4_mult(t_mat4 a, t_mat4 b)
{
	t_mat4 mul;

    mul[0] = b[0][0] * a[0][0] + b[0][1] * a[1][0] + b[0][2] * a[2][0] + b[0][3] * a[3][0];
    mul[1] = b[0][0] * a[0][1] + b[0][1] * a[1][1] + b[0][2] * a[2][1] + b[0][3] * a[3][1];
    mul[2] = b[0][0] * a[0][2] + b[0][1] * a[1][2] + b[0][2] * a[2][2] + b[0][3] * a[3][2];
    mul[3] = b[0][0] * a[0][3] + b[0][1] * a[1][3] + b[0][2] * a[2][3] + b[0][3] * a[3][3];
    mul[4] = b[1][0] * a[0][0] + b[1][1] * a[1][0] + b[1][2] * a[2][0] + b[1][3] * a[3][0];
    mul[5] = b[1][0] * a[0][1] + b[1][1] * a[1][1] + b[1][2] * a[2][1] + b[1][3] * a[3][1];
    mul[6] = b[1][0] * a[0][2] + b[1][1] * a[1][2] + b[1][2] * a[2][2] + b[1][3] * a[3][2];
    mul[7] = b[1][0] * a[0][3] + b[1][1] * a[1][3] + b[1][2] * a[2][3] + b[1][3] * a[3][3];
    mul[8] = b[2][0] * a[0][0] + b[2][1] * a[1][0] + b[2][2] * a[2][0] + b[2][3] * a[3][0];
    mul[9] = b[2][0] * a[0][1] + b[2][1] * a[1][1] + b[2][2] * a[2][1] + b[2][3] * a[3][1];
    mul[10] = b[2][0] * a[0][2] + b[2][1] * a[1][2] + b[2][2] * a[2][2] + b[2][3] * a[3][2];
    mul[11] = b[2][0] * a[0][3] + b[2][1] * a[1][3] + b[2][2] * a[2][3] + b[2][3] * a[3][3];
    mul[12] = b[3][0] * a[0][0] + b[3][1] * a[1][0] + b[3][2] * a[2][0] + b[3][3] * a[3][0];
    mul[13] = b[3][0] * a[0][1] + b[3][1] * a[1][1] + b[3][2] * a[2][1] + b[3][3] * a[3][1];
    mul[14] = b[3][0] * a[0][2] + b[3][1] * a[1][2] + b[3][2] * a[2][2] + b[3][3] * a[3][2];
    mul[15] = b[3][0] * a[0][3] + b[3][1] * a[1][3] + b[3][2] * a[2][3] + b[3][3] * a[3][3];
    return(mul);
}

t_mat4	mat4_translate(t_vector pos)
{
	t_mat4 tr;

	tr.a[0][0] = 1;
	tr.a[0][1] = 0;
	tr.a[0][2] = 0;
	tr.a[0][3] = pos.x;

	tr.a[1][0] = 0;
	tr.a[1][1] = 1;
	tr.a[1][2] = 0;
	tr.a[1][3] = pos.y;

	tr.a[2][0] = 0;
	tr.a[2][1] = 0;
	tr.a[2][2] = 1;
	tr.a[2][3] = pos.z;

	tr.a[3][0] = 0;
	tr.a[3][1] = 0;
	tr.a[3][2] = 0;
	tr.a[3][3] = 1;

	return (tr);
}

void	mat4_rotateX(t_vector ang)
{
	t_mat4 tr;

	tr.a[0][0] = 1;
	tr.a[0][1] = 0;
	tr.a[0][2] = 0;
	tr.a[0][3] = 0;

	tr.a[1][0] = 0;
	tr.a[1][1] = cos(ang.x);
	tr.a[1][2] = sin(ang.x);
	tr.a[1][3] = 0;

	tr.a[2][0] = 0;
	tr.a[2][1] = -sin(ang.x);
	tr.a[2][2] = cos(ang.x);
	tr.a[2][3] = 0;

	tr.a[3][0] = 0;
	tr.a[3][1] = 0;
	tr.a[3][2] = 0;
	tr.a[3][3] = 1;

	return (tr);	
}

void	mat4_rotateY(t_vector ang)
{
	t_mat4 tr;

	tr.a[0][0] = cos(ang.y);
	tr.a[0][1] = 0;
	tr.a[0][2] = sin(ang.y);
	tr.a[0][3] = 0;

	tr.a[1][0] = 0;
	tr.a[1][1] = 1;
	tr.a[1][2] = 0;
	tr.a[1][3] = 0;

	tr.a[2][0] = -sin(ang.y);
	tr.a[2][1] = 0;
	tr.a[2][2] = cos(ang.y);
	tr.a[2][3] = 0;

	tr.a[3][0] = 0;
	tr.a[3][1] = 0;
	tr.a[3][2] = 0;
	tr.a[3][3] = 1;

	return (tr);	
}

void	mat4_rotateZ(t_vector ang)
{
	t_mat4 tr;

	tr.a[0][0] = cos(ang.z);
	tr.a[0][1] = sin(ang.z);
	tr.a[0][2] = 0;
	tr.a[0][3] = 0;

	tr.a[1][0] = -sin(ang.z);
	tr.a[1][1] = cos(ang.z);
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

void	mat4_scale(t_vector sc)
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
