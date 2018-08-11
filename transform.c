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
}

t_mat4	transform_getModel(t_transf *tf)
{
	t_model model;
//to do assign
	model.pos = mat4_translate(tf->pos);
	model.rotX = mat4_rotateX(vinit(1.0, 0.0, 0.0));
	model.rotY = mat4_rotateY(vinit(0.0, 1.0, 0.0));
	model.rotZ = mat4_rotateZ(vinit(0.0, 0.0, 1.0));
	model.scale = mat4_scale(vinit(1.0, 1.0, 1.0));

	model.rot = mat4_mul(mat4_mul(model.rotZ, model.rotY), model.rotZ);
 	return(mat4_mul(mat4_mul(model.pos, model.rot), model.scale));
}