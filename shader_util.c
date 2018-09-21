/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izelensk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/21 15:07:28 by izelensk          #+#    #+#             */
/*   Updated: 2018/09/21 15:07:32 by izelensk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void	shader_mode_update(t_shader *shader, t_transf *tf)
{
	if (tf->loop > 360.0)
		tf->loop = 0.0;
	glUniform1f(shader->unifs[LOOP_U], tf->loop);
	glUniform1i(shader->unifs[MODE_U], tf->mode);
}

char	*shader_load(const char *filename)
{
	int		fd;
	char	*text;
	char	*line;

	text = ft_strnew(100000);
	fd = open(filename, O_RDONLY);
	while (get_next_line(fd, &line) == 1)
	{
		ft_strcat(text, "\n");
		ft_strcat(text, line);
		free(line);
	}
	return (text);
}
