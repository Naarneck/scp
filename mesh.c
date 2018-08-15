#include "scop.h"

void mesh_init(t_vertex *vertices, unsigned int numVertices, unsigned int *indices, unsigned int numIndices, t_mesh *mesh)
{
	t_vector	*poss;
	t_coord		*uvs;

	int i;

	i = 0;
	poss = (t_vector *)malloc(sizeof(t_vector) * numVertices);
	uvs = (t_coord *)malloc(sizeof(t_coord) * numVertices);
	while (i < numVertices)
	{
		poss[i] = vertex_getPos(vertices[i]);
		uvs[i] = vertex_getUV(vertices[i]);
		// printf("UV: %d : x: %f y: %f\n", i, uvs[i].x, uvs[i].y);
		// printf("Pos: %d : x: %f y: %f z:  %f\n", i, poss[i].x, poss[i].y, poss[i].z);
		i++;
	}
	
	mesh->drawCount = numVertices;
	mesh->drawCount = numIndices;
	glGenVertexArrays(1, &mesh->vertexArrObj);
	glBindVertexArray(mesh->vertexArrObj);
	glGenBuffers(NUM_BUFFERS, mesh->vertexArrBuf);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexArrBuf[POSITION_VB]);
	glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(poss[0]), &poss[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexArrBuf[TEXCOORD_VB]);
	glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(uvs[0]), &uvs[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->vertexArrBuf[INDEX_VB]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, numIndices * sizeof(indices[0]), &indices[0], GL_STATIC_DRAW);

	glBindVertexArray(0);
	glBindVertexArray(1);
	
	free(poss);
	free(uvs);
}

void mesh_del(t_mesh *mesh)
{
	glDeleteVertexArrays(1, &mesh->vertexArrObj);
}

void mesh_draw(t_mesh *mesh)
{
	glBindVertexArray(mesh->vertexArrObj);
	glDrawElements(GL_TRIANGLES, mesh->drawCount, GL_UNSIGNED_INT, 0);
	// glDrawArrays(GL_TRIANGLES, 0, mesh->drawCount);
	glBindVertexArray(0);
}



/*
	x,y,z;
	x,y,z;
*/