/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izelensk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/17 18:13:43 by izelensk          #+#    #+#             */
/*   Updated: 2018/10/17 18:13:47 by izelensk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

int			obj_checkvvnvt(t_fileobj *fo, t_objindex *obji)
{
	if (fo->line_arr[0][0] == 'v' && fo->line_arr[0][1] == 't')
	{
		if (fo->num < 3)
			return (0);
		obji->numtex++;
	}
	else if (fo->line_arr[0][0] == 'v' && fo->line_arr[0][1] == 'n')
	{
		if (fo->num < 4)
			return (0);
		obji->numnormals++;
	}
	else if (fo->line_arr[0][0] == 'v')
	{
		if (fo->num < 4)
			return (0);
		obji->numpositions++;
	}
	return (1);
}

int			obj_checkf(t_fileobj *fo, t_objindex *obji)
{
	int			i;

	if (fo->line_arr[0][0] == 'f')
	{
		i = 0;
		while (++i < fo->num)
		{
			if (ft_atoi(fo->line_arr[i]) <= 0)
				return (0);
		}
		if (fo->num < 3)
			return (0);
		obji->numindices += (fo->num - 3);
		if (ft_atoi(fo->line_arr[1]) <= 0)
			return (0);
		obji->is_normals = getnormal(fo->line_arr[1]) > 0 ? 1 : 0;
		obji->is_uvs = getuv(fo->line_arr[1]) > 0 ? 1 : 0;
	}
	return (obj_checkvvnvt(fo, obji));
}

void		obj_checkfile(const char *filename, t_objindex *obji)
{
	t_fileobj	fo;

	obj_init(obji, filename);
	fo.fd = open(filename, O_RDONLY);
	while (get_next_line(fo.fd, &fo.line) == 1)
	{
		if (fo.line != NULL)
			fo.line_arr = ft_strsplitnum(fo.line, ' ', &fo.num);
		if (fo.line_arr[0] && fo.line_arr[0][0])
		{
			if (!obj_checkf(&fo, obji))
			{
				printf("missing some coordinates, or negative\n");
				exit(0);
			}
		}
		obj_free_line(&fo);
	}
	if (obji->numpositions == 0 || obji->numindices == 0)
	{
		printf("faces or indices missing i file.\n");
		exit(0);
	}
}
