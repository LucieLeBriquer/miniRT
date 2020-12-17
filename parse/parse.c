#include "miniRT.h"

int		parse_res(int fd, t_scene *scene, char *line)
{
	int		width;
	int		height;

	line++;
	while (ft_isspace(*line))
		line++;
	width = ft_atoi(line);
	if (width <= 0)
		return (-1);
	scene->W = width;
	while (ft_isdigit(*line))
		line++;
	while (ft_isspace(*line))
		line++;
	height = ft_atoi(line);
	if (height <= 0)
		return (-1);
	scene->H = height;
	return (1);
}

int		size_of_int(int i)
{
	int	size;

	if (i == 0)
		return (1);
	while (i > 0)
	{
		i = i / 10;
		size++;
	}
	return (size);
}

float	ft_atof(char *line)
{
	int		entiere;
	int		floating;
	float	res;

	floating = 0;
	entiere = ft_atoi(line);
	while (ft_isdigit(*line))
		line++;
	if (*line == '.')
		line++;
	floating = ft_atoi(line);
	res = entiere + (float)(floating) / pow(10, size_of_int(floating)); 
	return (res);
}

/*
** A modifier en passant le float en param et en retournant un int si 
** la conversion n'est pas bonne
*/

int		to_col(char *line, t_col *col)
{
	int		c;

	c = ft_atoi(line);
	if (c < 0 || c > 255)
		return (-1);
	col->r = c;
	while (ft_isdigit(*line))
		line++;
	if (*line != ',')
		return (-1);
	line++;
	c = ft_atoi(line);
	if (c < 0 || c > 255)
		return (-1);
	col->g = c;
	while (ft_isdigit(*line))
		line++;
	if (*line != ',')
		return (-1);
	line++;
	c = ft_atoi(line);
	if (c < 0 || c > 255)
		return (-1);
	col->b = c;
	return (1);
}

int		parse_amb(int fd, t_scene *scene, char *line)
{
	float	amb;
	int		one_point;
	t_col	col;

	line++;
	one_point = 0;
	while (ft_isspace(*line))
		line++;
	amb = ft_atof(line);
	if (amb < 0 || amb > 1)
		return (-1);
	scene->amb = amb;
	while (ft_isdigit(*line))
		line++;
	if (*line == '.')
		line++;
	while (ft_isdigit(*line))
		line++;
	while (ft_isspace(*line))
		line++;
	if (to_col(line, &col) == -1)
		return (-1);
	while (ft_isdigit(*line) || *line == ',')
		line++;
	scene->amb_col = col;
	return (1);
}

/*
**	Verifier en plus qu'on est bien a la fin de la ligne
*/

int		parse_line(int fd, t_scene *scene, char *line)
{
	while (ft_isspace(*line))
		line++;
	if (*line == 'R')
		return (parse_res(fd, scene, line));
	if (*line == 'A')
		return (parse_amb(fd, scene, line));
	/*if (*line == 'c')
		return (parse_cam(fd, scene, line));
	if (*line == 'l')
		return (parse_lum(fd, scene, line));
	if (*line == 's' && *(++line) == 'p')
		return (parse_sph(fd, scene, line));
	if (*line == 'p' && *(++line) == 'l')
		return (parse_pln(fd, scene, line));
	if (*line == 's' && *(++line) == 'q')
		return (parse_sqr(fd, scene, line));
	if (*line == 'c' && *(++line) == 'y')
		return (parse_cyl(fd, scene, line));
	if (*line == 't' && *(++line) == 'r')
		return (parse_trg(fd, scene, line));*/
	return (-1);
}

int		parse(int fd, t_scene *scene)
{
	char	*line;

	while (get_next_line(fd, &line))
	{
		if (line && line[0])
		{
			if (parse_line(fd, scene, line) == -1)
				return (-1);
		}
	}
	return (1);
}

int		main(int argc, char **argv)
{
	char	*file_name;
	char	*save_name;
	int		fd;
	t_scene	scene;

	if (argc == 2 || (argc == 4 && is_save(argv[2])))
	{
		fd = open(argv[1], O_RDONLY);
		if (fd > 0)
		{
			if (parse(fd, &scene) == 1)
				print_parsing(scene);
			else
				printf("Error\n");
		}
	}
	else
		printf("Error\n");
	return (0);
}
