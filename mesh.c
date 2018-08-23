#include "scop.h"

void mesh_index_obj(t_mesh *mesh, t_objIndex obji)
{
	int i;


	mesh->positions = (t_vector *)malloc(sizeof(t_vector) * obji.numIndices);
	mesh->uvs = (t_coord *)malloc(sizeof(t_coord) * obji.numIndices);
	mesh->normals = (t_vector *)malloc(sizeof(t_vector) * obji.numIndices);
	i = 0;
	// printf("d: %d\n", obji.numIndices);
	while (i < obji.numIndices)
	{

		// printf("%d: ", i);
		// printf("f:  %d / %d / %d\n", obji.posid[i], obji.uvsid[i], obji.normalsid[i]);
		mesh->positions[i] = obji.v[obji.posid[i]];
		// mesh->uvs[i] = obji.vt[obji.uvsid[i]];
		mesh->uvs[i] = cinit(obji.vt[obji.uvsid[i]].x, 1.0 - obji.vt[obji.uvsid[i]].y);
		// printf("mew\n");
		mesh->normals[i] = vinit(0,0,0);
		i++;
	}
}

void mesh_init(t_mesh *mesh, t_objIndex obji)
{
	// t_vector		*poss;
	// t_coord			*uvs;
	// unsigned int	*inds;
	int i;

	i = 0;
	printf("f:  %d / %d / %d\n", obji.posid[8], obji.uvsid[8], obji.normalsid[8]);
	mesh_index_obj(mesh, obji);
	// poss = (t_vector *)malloc(sizeof(t_vector) * obji.numPositions);
	// uvs = (t_coord *)malloc(sizeof(t_coord) * obji.numPositions);
	// inds = (unsigned int *)malloc(sizeof(unsigned int) * obji.numIndices);
	// while (i < obji.numPositions)
	// {
	// 	poss[i] = vertex_getPos(obji.vertices[i]);
	// 	uvs[i] = vertex_getUV(obji.vertices[i]);
	// 	i++;
	// }
	// while (i < obji.numIndices)
	// {
	// 	inds[i] = indices[i];
	// 	i++;
	// }
	// mesh->drawCount = obji.numPositions;
	mesh->drawCount = obji.numIndices;
	glGenVertexArrays(1, &mesh->vertexArrObj);
	glBindVertexArray(mesh->vertexArrObj);
	glGenBuffers(NUM_BUFFERS, mesh->vertexArrBuf);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexArrBuf[POSITION_VB]);
	glBufferData(GL_ARRAY_BUFFER, obji.numIndices * sizeof(mesh->positions[0]), &mesh->positions[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexArrBuf[TEXCOORD_VB]);
	glBufferData(GL_ARRAY_BUFFER, obji.numIndices * sizeof(mesh->uvs[0]), &mesh->uvs[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

	// glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->vertexArrBuf[INDEX_VB]);
	// glBufferData(GL_ELEMENT_ARRAY_BUFFER, obji.numIndices * sizeof(obji.posid[0]), &obji.posid[0], GL_STATIC_DRAW);

	// glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->vertexArrBuf[INDEX_TB]);
	// glBufferData(GL_ELEMENT_ARRAY_BUFFER, obji.numIndices * sizeof(obji.uvsid[0]), &obji.uvsid[0], GL_STATIC_DRAW);

	glBindVertexArray(0);
	glBindVertexArray(1);
	
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
	// glDrawElements(GL_TRIANGLES, mesh->drawCount, GL_UNSIGNED_INT, 0);
	glDrawArrays(GL_TRIANGLES, 0, mesh->drawCount);
	glBindVertexArray(0);
}

/*
	x,y,z;
	x,y,z;
*/