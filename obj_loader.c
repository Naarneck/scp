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

int			getUV(char *str)
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
			free (temp);
			return (i);
		}
		i++;
	}
	return (0);
}

int			getNormal(char *str)
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
			free (temp);
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
	int		div_part;
	int		mod_part;
	char	*temp;
	int 	minus;

	i = 0;
	n = 0.0;
	while (str[i] != '.' && str[i] != ' ' && str[i] != '\0' && str[i] != '\n')
		i++;
	temp = ft_strsub(str, 0, i);
	minus = 1;
	if(str[0] == '-')
		minus = -1;
	div_part = abs(ft_atoi(temp));
	n += (float)div_part;
	free(temp);
	temp = ft_strsub(str, i + 1, ft_strlen(str) - i);
	mod_part = ft_atoi(temp);
		n += pow(0.1, ft_strlen(str) - i - 1) * (float)mod_part;
	free(temp);
	return (n * minus);
}

void		obj_checkFile(const char *filename, t_objIndex *obji)
{
	int		fd;
	char	*line;
	char	**line_arr;
	int		i;
	int		num;

	obji->is_uvs = 0;
	obji->is_normals = 0;
	obji->numIndices = 0;
	obji->numNormals = 0;
	obji->numTex = 0;
	obji->numPositions = 0;
	obji->far = 0.0;
	fd = open(filename, O_RDONLY);
	while (get_next_line(fd, &line) == 1)
	{
		if (line != NULL)
			line_arr = ft_strsplitnum(line, ' ', &num);
		if (line_arr[0] && line_arr[0][0])
		{
			if (line_arr[0][0] == 'f')
			{
				obji->numIndices += (num - 3);
				if (getUV(line_arr[1]) > 0 )
					obji->is_uvs = 1;
				if (getNormal(line_arr[1]) > 0)
					obji->is_normals = 1;
			}
			else if (line_arr[0][0] == 'v' && line_arr[0][1] == 't')
				obji->numTex++;
			else if (line_arr[0][0] == 'v' && line_arr[0][1] == 'n')
				obji->numNormals++;
			else if (line_arr[0][0] == 'v')
				obji->numPositions++;
		}
		i = -1;
		while (line_arr[++i])
			free(line_arr[i]);
		free(line_arr);
		free(line);
	}
	printf("faces:%u vertice normals:%u vertice texture:%u vertices:%u\n",
	 obji->numIndices, obji->numNormals, obji->numTex, obji->numPositions);
}

void	obj_loadFile(const char *filename, t_objIndex *obji)
{
	char	*line;
	char	**line_arr;
	int		i;
	int		num;
	int		fd;

	obj_checkFile(filename, obji);
	obji->v = (t_vector *)malloc(sizeof(t_vector) * obji->numPositions);
	obji->vt = (t_coord *)malloc(sizeof(t_coord) * obji->numTex);
	obji->vn = (t_vector *)malloc(sizeof(t_vector) * obji->numNormals);
	obji->posid = (unsigned int *)malloc(sizeof(unsigned int) * obji->numIndices * 3);
	obji->uvsid = (unsigned int *)malloc(sizeof(unsigned int) * obji->numIndices * 3);
	obji->normalsid = (unsigned int *)malloc(sizeof(unsigned int) * obji->numIndices * 3);
	obji->numIndices = 0;
	obji->numPositions = 0;
	obji->numTex = 0;
	obji->numNormals = 0;
	fd = open(filename, O_RDONLY);
	while (get_next_line(fd, &line) == 1)
	{
		if (line != NULL){
			if(!isdigit(line[ft_strlen(line) - 1]))
				line[ft_strlen(line) - 1] = '\0';
			line_arr = ft_strsplitnum(line, ' ', &num);
		}
		if (line_arr[0] && line_arr[1] && num > 0)
		{
			if (line_arr[0][0] == 'f')
			{
				i = 0;
				while (i < num - 3)
				{
					obji->posid[obji->numIndices] = ft_atoi(line_arr[1]) - 1;
					if (obji->is_uvs)
						obji->uvsid[obji->numIndices] = getUV(line_arr[1]) - 1;
					else
						obji->uvsid[obji->numIndices] = 0;
					if (obji->is_normals)
						obji->normalsid[obji->numIndices] = getNormal(line_arr[1]) - 1;
					else
						obji->normalsid[obji->numIndices] = 0;

					obji->posid[++obji->numIndices] = ft_atoi(line_arr[2 + i]) - 1;
					if (obji->is_uvs)
						obji->uvsid[obji->numIndices] = getUV(line_arr[2 + i]) - 1;
					else
						obji->uvsid[obji->numIndices] = 0;
					if (obji->is_normals)
						obji->normalsid[obji->numIndices] = getNormal(line_arr[2 + i]) - 1;
					else
						obji->normalsid[obji->numIndices] = 0;
					
					obji->posid[++obji->numIndices] = ft_atoi(line_arr[3 + i]) - 1;
					if (obji->is_uvs)
						obji->uvsid[obji->numIndices] = getUV(line_arr[3 + i]) - 1;
					else
						obji->uvsid[obji->numIndices] = 0;
					if (obji->is_normals)
						obji->normalsid[obji->numIndices] = getNormal(line_arr[3 + i]) - 1;
					else
						obji->normalsid[obji->numIndices] = 0;
					i++;
					++obji->numIndices;
				}
			}
			else if (line_arr[0][0] == 'v' && line_arr[0][1] == '\0')
			{
				obji->v[obji->numPositions].x = ft_atof(line_arr[1]);
				obji->v[obji->numPositions].y = ft_atof(line_arr[2]);
				obji->v[obji->numPositions].z = ft_atof(line_arr[3]);
				obji->far = vmax(obji->v[obji->numPositions]);
				obji->numPositions++;
			}
			else if (line_arr[0][0] == 'v' && line_arr[0][1] == 't')
			{
				obji->vt[obji->numTex].x = ft_atof(line_arr[1]);
				obji->vt[obji->numTex].y = ft_atof(line_arr[2]);
				obji->numTex++;
			}
			else if (line_arr[0][0] == 'v' && line_arr[0][1] == 'n')
			{
				obji->vn[obji->numNormals].x = ft_atof(line_arr[1]);
				obji->vn[obji->numNormals].y = ft_atof(line_arr[2]);
				obji->vn[obji->numNormals].z = ft_atof(line_arr[3]);
				obji->numNormals++;
			}
		}
		i = -1;
		while (line_arr[++i])
			free(line_arr[i]);
		free(line_arr);
		free(line);
	}
}
