/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izelensk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/21 15:10:05 by izelensk          #+#    #+#             */
/*   Updated: 2018/09/21 15:10:07 by izelensk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

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

void		obj_free_line(t_fileobj *fo)
{
	fo->i = -1;
	while (fo->line_arr[++fo->i])
		free(fo->line_arr[fo->i]);
	free(fo->line_arr);
	free(fo->line);
}

void		obj_init(t_objindex *obji, const char *fn)
{
	obji->status = 1;
	if (ft_strlen(fn) <= 4 || fn[ft_strlen(fn) - 1] != 'j'
		|| fn[ft_strlen(fn) - 2] != 'b' || fn[ft_strlen(fn) - 3] != 'o'
		|| fn[ft_strlen(fn) - 4] != '.')
		obji->status = 0;
	obji->is_uvs = 0;
	obji->is_normals = 0;
	obji->numindices = 0;
	obji->numpositions = 0;
	obji->numnormals = 0;
	obji->numtex = 0;
	obji->far = 0.0;
}
