/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izelensk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/17 19:12:59 by izelensk          #+#    #+#             */
/*   Updated: 2018/09/17 19:13:01 by izelensk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"
#define UV 1
#define NORMAL 2

void	generate_uv_norm(t_mesh *mesh, unsigned int i, int id)
{
	if (id == UV)
	{
		mesh->uvs[i] = cinit(1.0, 0.0);
		if (i % 3 == 0)
			mesh->uvs[i] = cinit(0.0, 0.0);
		else if (i % 2 == 0)
			mesh->uvs[i] = cinit(0.5, 1.0);
	}
	else if (id == NORMAL)
	{
		if (i % 3 == 2)
		{
			mesh->normals[i] = vcalcnormal(mesh->positions[i - 2],
								mesh->positions[i - 1], mesh->positions[i]);
			mesh->normals[i - 1] = mesh->normals[i];
			mesh->normals[i - 2] = mesh->normals[i];
		}
	}
}

void	mesh_index_obj(t_mesh *mesh, t_objindex *obji)
{
	unsigned int i;

	mesh->drawcount = obji->numindices;
	mesh->positions = (t_vector *)malloc(sizeof(t_vector) * obji->numindices);
	mesh->uvs = (t_coord *)malloc(sizeof(t_coord) * obji->numindices);
	mesh->normals = (t_vector *)malloc(sizeof(t_vector) * obji->numindices);
	i = -1;
	while (++i < obji->numindices)
	{
		mesh->positions[i] = obji->v[obji->posid[i]];
		if (obji->is_uvs)
			mesh->uvs[i] = cinit(obji->vt[obji->uvsid[i]].x,
										1.0 - obji->vt[obji->uvsid[i]].y);
		else
			generate_uv_norm(mesh, i, UV);
		if (obji->is_normals)
			mesh->normals[i] = obji->vn[obji->normalsid[i]];
		else if (i > 1)
			generate_uv_norm(mesh, i, NORMAL);
	}
}

void	mesh_init(t_mesh *mesh, t_objindex *obji)
{
	mesh_index_obj(mesh, obji);
	glGenVertexArrays(1, &mesh->vertexarrobj);
	glBindVertexArray(mesh->vertexarrobj);
	glGenBuffers(NUM_BUFFERS, mesh->vertexarrbuf);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexarrbuf[POSITION_VB]);
	glBufferData(GL_ARRAY_BUFFER, obji->numindices * sizeof(mesh->positions[0]),
										&mesh->positions[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexarrbuf[TEXCOORD_VB]);
	glBufferData(GL_ARRAY_BUFFER, obji->numindices * sizeof(mesh->uvs[0]),
												&mesh->uvs[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexarrbuf[NORMAL_VB]);
	glBufferData(GL_ARRAY_BUFFER, obji->numindices * sizeof(mesh->normals[0]),
											&mesh->normals[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindVertexArray(0);
	glBindVertexArray(1);
	glBindVertexArray(2);
	free(mesh->positions);
	free(mesh->normals);
	free(mesh->uvs);
}

void	mesh_del(t_mesh *mesh)
{
	glDeleteVertexArrays(1, &mesh->vertexarrobj);
}

void	mesh_draw(t_mesh *mesh)
{
	glBindVertexArray(mesh->vertexarrobj);
	glDrawArrays(GL_TRIANGLES, 0, mesh->drawcount);
	glBindVertexArray(0);
}
