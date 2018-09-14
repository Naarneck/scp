#include "scop.h"

void	transform_init(t_vector pos, t_vector rot, t_vector scale, t_transf *tf)
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

	tf->mode = 1;
	tf->loop = 0.0;
}

t_mat4	transform_getModel(t_transf *tf)
{
	t_model model;

	model.pos = mat4_translate(tf->pos);
	model.rotX = mat4_rotateX(tf->rot.x);
	model.rotY = mat4_rotateY(tf->rot.y);
	model.rotZ = mat4_rotateZ(tf->rot.z);
	model.scale = mat4_scale(tf->scale);

	model.rot = mat4_mult(mat4_mult(model.rotX, model.rotY), model.rotZ);
 	return (mat4_mult(mat4_mult(model.scale, model.rot), model.pos));
}