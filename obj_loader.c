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
	int 	num;

	obji->numIndices = 0;
	obji->numNormals = 0;
	obji->numTex = 0;
	obji->numPositions = 0;
	obji->numLines = 0;
	fd = open(filename, O_RDONLY);
 	// printf("fd # %d\n", fd);
	while (get_next_line(fd, &line) == 1)
	{
		i = -1;
		obji->numLines++;
		line_arr = ft_strsplitnum(line, ' ', &num);
		if (line_arr[0] && line_arr[0])
		{
			// printf("fd %d\n", obji->numLines);
			if (line_arr[0][0] == 'f')
			{
				obji->numIndices += (num - 3);
			}
			else if (line_arr[0][0] == 'v' && line_arr[0][1] == 't')
				obji->numTex++;
			else if (line_arr[0][0] == 'v' && line_arr[0][1] == 'n')
				obji->numNormals++;
			else if (line_arr[0][0] == 'v')
				obji->numPositions++;
		}
		// while (line_arr[++i])
		// 	free(line_arr[i]);
		// free(line_arr);
		free(line);	
	}
	// close(fd); close in some del function in the end
	// printf("f:%u vn:%u vt:%u v:%u\n", obji->numIndices, obji->numNormals, obji->numTex, obji->numPositions);
}

void	obj_loadFile(const char *filename, t_objIndex *obji)
{
	char	*line;
	char	**line_arr;
	int		i;
	int		num;
	int		fd;
//to do
//check length..
//cheack params count,
//check 1000 other stuff..

	obj_checkFile(filename, obji);
	obji->vertices = (t_vertex *)malloc(sizeof(t_vertex) * obji->numPositions);
	obji->indices = (unsigned int *)malloc(sizeof(unsigned int) * obji->numPositions * 3);
	obji->numIndices = 0;
	obji->numPositions = 0;
	fd = open(filename, O_RDONLY);
	while (get_next_line(fd, &line) == 1)
	{
		i = -1;
		line_arr = ft_strsplitnum(line, ' ', &num);
		// printf("num %d\n", num);
		if (line_arr[0] && line_arr[1] && num > 0)
		{
			if (line_arr[0][0] == 'f')
			{
				//to do - concert ABCDEF to ABC ACD BDE CEF DFG
				//to do - concert 123456 to 123 134 245 356 467
				obji->indices[obji->numIndices] = ft_atoi(line_arr[1]) - 1;
				// printf("faces: x:%u,",  
				// obji->indices[obji->numIndices]);
				obji->indices[++obji->numIndices] = ft_atoi(line_arr[2]) - 1;
				// printf("y:%u,",  
				// obji->indices[obji->numIndices]);
				obji->indices[++obji->numIndices] = ft_atoi(line_arr[3]) - 1;
				// printf("z:%u,\n",  
				// obji->indices[obji->numIndices]);
				if (num > 4)
				{
					++obji->numIndices;
					obji->indices[obji->numIndices] = ft_atoi(line_arr[1]) - 1;
					obji->indices[++obji->numIndices] = ft_atoi(line_arr[3]) - 1;
					obji->indices[++obji->numIndices] = ft_atoi(line_arr[4]) - 1;
				}
				if (num > 5)
				{
					++obji->numIndices;
					obji->indices[obji->numIndices] = ft_atoi(line_arr[1]) - 1;
					obji->indices[++obji->numIndices] = ft_atoi(line_arr[4]) - 1;
					obji->indices[++obji->numIndices] = ft_atoi(line_arr[5]) - 1;
				}
				if (num > 6)
				{
					++obji->numIndices;
					obji->indices[obji->numIndices] = ft_atoi(line_arr[1]) - 1;
					obji->indices[++obji->numIndices] = ft_atoi(line_arr[5]) - 1;
					obji->indices[++obji->numIndices] = ft_atoi(line_arr[6]) - 1;
				}
				if (num > 7)
				{
					++obji->numIndices;
					obji->indices[obji->numIndices] = ft_atoi(line_arr[1]) - 1;
					obji->indices[++obji->numIndices] = ft_atoi(line_arr[6]) - 1;
					obji->indices[++obji->numIndices] = ft_atoi(line_arr[7]) - 1;
				}
				obji->numIndices++;
				// printf("faces: x:%u y:%u z:%u \n", 
				// obji->indices[obji->numIndices],
				// obji->indices[obji->numIndices],
				// obji->indices[obji->numIndices]);
			}
			else if (line_arr[0][0] == 'v' && line_arr[0][1] == '\0')
			{
				obji->vertices[obji->numPositions].pos.x = ft_atof(line_arr[1]);
				obji->vertices[obji->numPositions].pos.y = ft_atof(line_arr[2]);
				obji->vertices[obji->numPositions].pos.z = ft_atof(line_arr[3]);
				obji->vertices[obji->numPositions].uv.x = 0.1 + obji->numPositions * 0.001;
				obji->vertices[obji->numPositions].uv.y = 0.1 + obji->numPositions * 0.001;				
				// // printf("pos: x:%f y:%f z:%f \n", 
				// obji->vertices[obji->numPositions].pos.x,
				// obji->vertices[obji->numPositions].pos.y,
				// obji->vertices[obji->numPositions].pos.z);
				obji->numPositions++;
			}
		}
			// while (line_arr[++i])
			// 	free(line_arr[i]);
			// free(line_arr);
		free(line);
	}
	// printf("obj loaded\n");
	// printf("f:%u vn:%u vt:%u v:%u\n", obji->numIndices, obji->numNormals, obji->numTex, obji->numPositions);
}
