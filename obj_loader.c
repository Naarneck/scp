#include "scop.h"

float		ft_atof(char *str)
{
	int		i;
	float	n;
	int		div_part;
	int		mod_part;
	char	*temp;

	i = 0;
	n = 0.0;
	while (str[i] != '.' && str[i] != ' ' && str[i] != '\0' && str[i] != '\n')
		i++;
	temp = ft_strsub(str, 0, i);
	div_part = ft_atoi(temp);
	n += (float)div_part;
	free(temp);
	temp = ft_strsub(str, i + 1, ft_strlen(str) - i);
	mod_part = ft_atoi(temp);
	if (div_part > 0)
		n += pow(0.1, ft_strlen(str) - i - 1) * (float)mod_part;
	else
		n -= pow(0.1, ft_strlen(str) - i - 1) * (float)mod_part;
	free(temp);
	return (n);
}

void openObjFile(const char *filename, t_objindex *obji)
{
	int fd;
	char *line;
	char	**line_arr;

//to do
//check length..
//cheack params count,
//check 1000 other stuff..
	fd = open(filename, O_RDONLY);
	while (get_next_line(fd, &line) == 1)
	{
		line_arr = ft_strsplit(line, ' ');
		if (ft_strequ(line_arr[0], "#"))
			continue;
		else (ft_strequ(line_arr[0], "v"))
		{
			obji->positions[numIndices].x = ft_atof(line_arr[1]);
			obji->positions[numIndices].y = ft_atof(line_arr[2]);
			obji->positions[numIndices].z = ft_atof(line_arr[3]);
		}
		free(line);
	}
	close(fd);
}