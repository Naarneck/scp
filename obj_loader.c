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


void		obj_checkFile(const char *filename, t_objIndex *obji)
{
	int		fd;
	char	*line;
	char	**line_arr;
	int 	i;

	obji->numIndices = 0;
	obji->numNormals = 0;
	obji->numTex = 0;
	obji->numPositions = 0;
	obji->numLines = 0;
	obji->text = ft_strnew(1);
	fd = open(filename, O_RDONLY);
 	// printf("fd # %d\n", fd);
	while (get_next_line(fd, &line) == 1)
	{
		i = -1;
		obji->numLines++;
		line_arr = ft_strsplit(line, ' ');
		if (line_arr[0] && line_arr[0])
		{
			// printf("fd %d\n", obji->numLines);
			if (line_arr[0][0] == 'f')
				obji->numIndices++;
			else if (line_arr[0][0] == 'v' && line_arr[0][1] == 't')
				obji->numTex++;
			else if (line_arr[0][0] == 'v' && line_arr[0][1] == 'n')
				obji->numNormals++;
			else if (line_arr[0][0] == 'v')
				obji->numPositions++;
		}
		line = ft_strjoin(line, "\n");
		obji->text = ft_strjoin(obji->text, line);
		while (line_arr[++i])
			free(line_arr[i]);
		free(line_arr);
		free(line);	
	}
	// close(fd); close in some del function in the end
	// printf("f:%u vn:%u vt:%u v:%u\n", obji->numIndices, obji->numNormals, obji->numTex, obji->numPositions);
}

void	obj_loadFile(const char *filename, t_objIndex *obji)
{
	char	*line;
	char	**line_arr;
	int 	i, j;
//to do
//check length..
//cheack params count,
//check 1000 other stuff..

	obj_checkFile(filename, obji);
	obji->vertices = (t_vertex *)malloc(sizeof(t_vertex) * obji->numPositions);
	obji->indices = (unsigned int *)malloc(sizeof(unsigned int) * obji->numPositions);
	obji->numIndices = 0;
	obji->numPositions = 0;
	line = ft_strnew(1);
	i = 0;
	j = 0;
	while (obji->text[i] != '\0') 
	{
		j = i;
		while (obji->text[j] != '\n' && obji->text[j] != '\0')
			j++;
		// printf("i: %d j: %d \n", i, j);
		line = ft_strsub(obji->text, i, j-i);
		// printf("%s\n", line);
		line_arr = ft_strsplit(line, ' ');
		if (line_arr[0] && line_arr[1])
		{
			// printf("text %d\n", i);
			if (line_arr[0][0] == 'f')
			{
				//to do - concert ABCDEF to ABC ACD BDE CEF DFG
				obji->indices[obji->numIndices] = (unsigned int)ft_atoi(line_arr[1]);
				obji->indices[obji->numIndices] = (unsigned int)ft_atoi(line_arr[2]);
				obji->indices[obji->numIndices] = (unsigned int)ft_atoi(line_arr[3]);
				obji->numIndices++;
			}
			else if (line_arr[0][0] == 'v' && line_arr[0][1] == '\0')
			{
				obji->vertices[obji->numPositions].pos.x = ft_atof(line_arr[1]) - 1;
				obji->vertices[obji->numPositions].pos.y = ft_atof(line_arr[2]) - 1;
				obji->vertices[obji->numPositions].pos.z = ft_atof(line_arr[3]) - 1;
				obji->vertices[obji->numPositions].uv.x = 0.1 + i * 0.01;
				obji->vertices[obji->numPositions].uv.y = 0.1 + i * 0.01;				
				printf("x:%f y:%f z:%f \n", 
					obji->vertices[obji->numPositions].pos.x,
					obji->vertices[obji->numPositions].pos.y,
					obji->vertices[obji->numPositions].pos.z);
				obji->numPositions++;
			}
		}
		free(line);
		i++;
	}
	// printf("obj loaded\n");
	// printf("f:%u vn:%u vt:%u v:%u\n", obji->numIndices, obji->numNormals, obji->numTex, obji->numPositions);
}
