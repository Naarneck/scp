#include "scop.h"


void mesh_init(t_vertex *vertices, unsigned int num, t_mesh *mesh)
{
	mesh->drawCount = num;
	write(1, "1\n", 2);
	glGenVertexArrays(1, &mesh->vertexArrObj);
	glBindVertexArray(mesh->vertexArrObj);
	glGenBuffers(NUM_BUFFERS, mesh->vertexArrBuf);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexArrBuf[POSITION_VB]);
	glBufferData(GL_ARRAY_BUFFER, num * sizeof(vertices[0]), vertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindVertexArray(0);
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
