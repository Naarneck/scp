#include "scop.h"

void mesh_init(t_vertex *vertices, unsigned int num, t_mesh *mesh)
{
	t_vector	*poss;
	t_coord		*uvs;

	// float	*poss;
	// float	*uvs;

	int i;

	i = 0;
	poss = (t_vector *)malloc(sizeof(t_vector) * num);
	uvs = (t_coord *)malloc(sizeof(t_coord) * num);
	// poss = (float *)malloc(sizeof(float) * num * 3);
	// uvs = (float *)malloc(sizeof(float) * num * 2);
	while (i < num)
	{
		poss[i] = vertex_getPos(vertices[i]);
		uvs[i] = vertex_getUV(vertices[i]);
		// poss[i * 3 + 0] = vertices[i].pos.x;
		// poss[i * 3 + 1] = vertices[i].pos.y;
		// poss[i * 3 + 2] = vertices[i].pos.z;
		// uvs[i * 2 + 0] = vertices[i].uv.x;
		// uvs[i * 2 + 1] = vertices[i].uv.y;
		printf("UV: %d : x: %f y: %f\n", i, uvs[i].x, uvs[i].y);
		printf("Pos: %d : x: %f y: %f z:  %f\n", i, poss[i].x, poss[i].y, poss[i].z);
		// printf("UV: %d : x: %f y: %f\n", i, uvs[i * 2 + 0], uvs[i * 2 + 1]);
		// printf("Pos: %d : x: %f y: %f z:  %f size: %i\n", i, poss[i * 3 + 0], poss[i * 3 + 1], poss[i * 3 + 2] , sizeof(poss[i]));
		i++;
	}
	write(1,"ms\n",3);
	mesh->drawCount = num;
	glGenVertexArrays(1, &mesh->vertexArrObj);
	glBindVertexArray(mesh->vertexArrObj);
	glGenBuffers(NUM_BUFFERS, mesh->vertexArrBuf);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexArrBuf[POSITION_VB]);
	glBufferData(GL_ARRAY_BUFFER, num * sizeof(poss[0]), &poss[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexArrBuf[TEXCOORD_VB]);
	glBufferData(GL_ARRAY_BUFFER, num * sizeof(uvs[0]), &uvs[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

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
	glDrawArrays(GL_TRIANGLES, 0, mesh->drawCount);
	glBindVertexArray(0);
}



/*
	x,y,z;
	x,y,z;
*/