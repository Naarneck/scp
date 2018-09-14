#include "scop.h"

void mesh_index_obj(t_mesh *mesh, t_objIndex *obji)
{
	unsigned int i;

	mesh->positions = (t_vector *)malloc(sizeof(t_vector) * obji->numIndices);
	mesh->uvs = (t_coord *)malloc(sizeof(t_coord) * obji->numIndices);
	mesh->normals = (t_vector *)malloc(sizeof(t_vector) * obji->numIndices);
	i = 0;
	printf("d: %d\n", obji->numIndices);
	while (i < obji->numIndices)
	{
		mesh->positions[i] = obji->v[obji->posid[i]];
		if (obji->is_uvs)
			mesh->uvs[i] = cinit(obji->vt[obji->uvsid[i]].x, 1.0 - obji->vt[obji->uvsid[i]].y);
		else
		{
			if (i % 3 == 0)
				mesh->uvs[i] = cinit(0.0, 0.0);
			else if (i % 2 == 0)
				mesh->uvs[i] = cinit(0.5, 1.0);
			else
				mesh->uvs[i] = cinit(1.0, 0.0);
		}
		if (obji->is_normals)
			mesh->normals[i] = obji->vn[obji->normalsid[i]];
		else if (i > 1)
		{
			if (i % 3 == 2)
			{
				mesh->normals[i] = vcalcNormal(mesh->positions[i - 2], mesh->positions[i - 1] ,mesh->positions[i]);
				mesh->normals[i - 1] = mesh->normals[i];
				mesh->normals[i - 2] = mesh->normals[i];
			}
		}
		i++;
	}
}

void mesh_init(t_mesh *mesh, t_objIndex *obji)
{
	int i;

	i = 0;
	printf("f:  %d / %d / %d\n", obji->posid[8], obji->uvsid[8], obji->normalsid[8]);
	mesh_index_obj(mesh, obji);

	mesh->drawCount = obji->numIndices;
	glGenVertexArrays(1, &mesh->vertexArrObj);
	glBindVertexArray(mesh->vertexArrObj);
	glGenBuffers(NUM_BUFFERS, mesh->vertexArrBuf);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexArrBuf[POSITION_VB]);
	glBufferData(GL_ARRAY_BUFFER, obji->numIndices * sizeof(mesh->positions[0]), &mesh->positions[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexArrBuf[TEXCOORD_VB]);
	glBufferData(GL_ARRAY_BUFFER, obji->numIndices * sizeof(mesh->uvs[0]), &mesh->uvs[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexArrBuf[NORMAL_VB]);
	glBufferData(GL_ARRAY_BUFFER, obji->numIndices * sizeof(mesh->normals[0]), &mesh->normals[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2 , 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindVertexArray(0);
	glBindVertexArray(1);
	glBindVertexArray(2);
	
	free(mesh->positions);
	free(mesh->normals);
	free(mesh->uvs);
}

void mesh_del(t_mesh *mesh)
{
	glDeleteVertexArrays(1, &mesh->vertexArrObj);
}

void mesh_draw(t_mesh *mesh)
{
	glBindVertexArray(mesh->vertexArrObj);
	glDrawArrays(GL_TRIANGLES, 0, mesh->drawCount);
	glBindVertexArray(0);
}
