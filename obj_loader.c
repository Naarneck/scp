/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_loader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izelensk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/17 19:14:39 by izelensk          #+#    #+#             */
/*   Updated: 2018/09/17 19:14:40 by izelensk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"
#define V 1
#define VT 2
#define VN 3

int			getuv(char *str)
{
	int		i;
	int		first_slash;
	int		sec_slash;
	char	*temp;

	first_slash = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (!first_slash && str[i] == '/')
			first_slash = i;
		else if (first_slash && str[i] == '/')
		{
			sec_slash = i;
			temp = ft_strsub(str, first_slash + 1, sec_slash - first_slash);
			i = ft_atoi(temp);
			free(temp);
			return (i);
		}
		i++;
	}
	return (0);
}

int			getnormal(char *str)
{
	int		i;
	int		first_slash;
	int		sec_slash;
	char	*temp;

	first_slash = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (!first_slash && str[i] == '/')
			first_slash = i;
		else if (first_slash && str[i] == '/')
		{
			sec_slash = i;
			temp = ft_strsub(str, sec_slash + 1, ft_strlen(str) - sec_slash);
			i = ft_atoi(temp);
			free(temp);
			return (i);
		}
		i++;
	}
	return (0);
}

float		ft_atof(char *str)
{
	int		i;
	float	n;
	int		mod_div[2];
	char	*temp;
	int		minus;

	i = 0;
	n = 0.0;
	while (str[i] != '.' && str[i] != ' ' && str[i] != '\0' && str[i] != '\n')
		i++;
	temp = ft_strsub(str, 0, i);
	minus = 1;
	if (str[0] == '-')
		minus = -1;
	mod_div[0] = abs(ft_atoi(temp));
	n += (float)mod_div[0];
	free(temp);
	temp = ft_strsub(str, i + 1, ft_strlen(str) - i);
	mod_div[1] = ft_atoi(temp);
	n += pow(0.1, ft_strlen(str) - i - 1) * (float)mod_div[1];
	free(temp);
	return (n * minus);
}

void		obj_init(t_objindex *obji)
{
	obji->is_uvs = 0;
	obji->is_normals = 0;
	obji->numindices = 0;
	obji->numpositions = 0;
	obji->numnormals = 0;
	obji->numtex = 0;
	obji->far = 0.0;
}

void		obj_alloc(t_objindex *obji)
{
	obji->v = (t_vector *)malloc(sizeof(t_vector) * obji->numpositions);
	obji->vt = (t_coord *)malloc(sizeof(t_coord) * obji->numtex);
	obji->vn = (t_vector *)malloc(sizeof(t_vector) * obji->numnormals);
	obji->posid = (unsigned int *)malloc(sizeof(unsigned int)
													* obji->numindices * 3);
	obji->uvsid = (unsigned int *)malloc(sizeof(unsigned int)
													* obji->numindices * 3);
	obji->normalsid = (unsigned int *)malloc(sizeof(unsigned int)
													* obji->numindices * 3);
	printf("faces:%u vertice normals:%u vertice texture:%u vertices:%u\n",
	obji->numindices, obji->numnormals, obji->numtex, obji->numpositions);
	obji->numindices = 0;
	obji->numpositions = 0;
	obji->numnormals = 0;
	obji->numtex = 0;
}

void		obj_free_line(t_fileobj *fo)
{
	fo->i = -1;
	while (fo->line_arr[++fo->i])
		free(fo->line_arr[fo->i]);
	free(fo->line_arr);
	free(fo->line);
}

void		obj_checkfile(const char *filename, t_objindex *obji)
{
	t_fileobj	fo;

	obj_init(obji);
	fo.fd = open(filename, O_RDONLY);
	while (get_next_line(fo.fd, &fo.line) == 1)
	{
		if (fo.line != NULL)
			fo.line_arr = ft_strsplitnum(fo.line, ' ', &fo.num);
		if (fo.line_arr[0] && fo.line_arr[0][0])
		{
			if (fo.line_arr[0][0] == 'f')
			{
				obji->numindices += (fo.num - 3);
				obji->is_normals = getnormal(fo.line_arr[1]) > 0 ? 1 : 0;
				obji->is_uvs = getuv(fo.line_arr[1]) > 0 ? 1 : 0;
			}
			else if (fo.line_arr[0][0] == 'v' && fo.line_arr[0][1] == 't')
				obji->numtex++;
			else if (fo.line_arr[0][0] == 'v' && fo.line_arr[0][1] == 'n')
				obji->numnormals++;
			else if (fo.line_arr[0][0] == 'v')
				obji->numpositions++;
		}
		obj_free_line(&fo);
	}
}

void		obj_triangulate_faces(t_objindex *obji, t_fileobj *fo)
{
	obji->posid[obji->numindices] = ft_atoi(fo->line_arr[1]) - 1;
	obji->uvsid[obji->numindices] = obji->is_uvs ?
												getuv(fo->line_arr[1]) - 1 : 0;
	obji->normalsid[obji->numindices] = obji->is_normals ?
											getnormal(fo->line_arr[1]) - 1 : 0;
	obji->posid[++obji->numindices] = ft_atoi(fo->line_arr[2 + fo->i]) - 1;
	obji->uvsid[obji->numindices] = obji->is_uvs ?
										getuv(fo->line_arr[2 + fo->i]) - 1 : 0;
	obji->normalsid[obji->numindices] = obji->is_normals ?
									getnormal(fo->line_arr[2 + fo->i]) - 1 : 0;
	obji->posid[++obji->numindices] = ft_atoi(fo->line_arr[3 + fo->i]) - 1;
	obji->uvsid[obji->numindices] = obji->is_uvs ?
										getuv(fo->line_arr[3 + fo->i]) - 1 : 0;
	obji->normalsid[obji->numindices] = obji->is_normals ?
									getnormal(fo->line_arr[3 + fo->i]) - 1 : 0;
	fo->i++;
	++obji->numindices;
}

void		obj_write_v_vt_vn(t_objindex *obji, t_fileobj *fo, int id)
{
	if (id == V)
	{
		obji->v[obji->numpositions].x = ft_atof(fo->line_arr[1]);
		obji->v[obji->numpositions].y = ft_atof(fo->line_arr[2]);
		obji->v[obji->numpositions].z = ft_atof(fo->line_arr[3]);
		obji->far = vmax(obji->v[obji->numpositions]);
		obji->numpositions++;
	}
	else if (id == VN)
	{
		obji->vn[obji->numnormals].x = ft_atof(fo->line_arr[1]);
		obji->vn[obji->numnormals].y = ft_atof(fo->line_arr[2]);
		obji->vn[obji->numnormals].z = ft_atof(fo->line_arr[3]);
		obji->numnormals++;
	}
	else if (id == VT)
	{
		obji->vt[obji->numtex].x = ft_atof(fo->line_arr[1]);
		obji->vt[obji->numtex].y = ft_atof(fo->line_arr[2]);
		obji->numtex++;
	}
}

void		obj_loadfile(const char *filename, t_objindex *obji)
{
	t_fileobj	fo;

	obj_checkfile(filename, obji);
	obj_alloc(obji);
	fo.fd = open(filename, O_RDONLY);
	while (get_next_line(fo.fd, &fo.line) == 1)
	{
		if (!isdigit(fo.line[ft_strlen(fo.line) - 1]))
			fo.line[ft_strlen(fo.line) - 1] = '\0';
		fo.line_arr = ft_strsplitnum(fo.line, ' ', &fo.num);
		if (fo.line_arr[0] && fo.line_arr[1] && fo.num > 0)
		{
			if ((fo.i = 0) || fo.line_arr[0][0] == 'f')
				while (fo.i < fo.num - 3)
					obj_triangulate_faces(obji, &fo);
			else if (fo.line_arr[0][0] == 'v' && fo.line_arr[0][1] == '\0')
				obj_write_v_vt_vn(obji, &fo, V);
			else if (fo.line_arr[0][0] == 'v' && fo.line_arr[0][1] == 't')
				obj_write_v_vt_vn(obji, &fo, VT);
			else if (fo.line_arr[0][0] == 'v' && fo.line_arr[0][1] == 'n')
				obj_write_v_vt_vn(obji, &fo, VN);
		}
		obj_free_line(&fo);
	}
}
