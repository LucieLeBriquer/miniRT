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
	scene->w = width;
	while (ft_isdigit(*line))
		line++;
	while (ft_isspace(*line))
		line++;
	height = ft_atoi(line);
	if (height <= 0)
		return (-1);
	scene->h = height;
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

int		skip_float(char *line)
{
	int	i;

	i = 0;
	if (line[i] == '-')
		i++;
	while (ft_isdigit(line[i]))
		i++;
	if (line[i] == '.')
		i++;
	while (ft_isdigit(line[i]))
		i++;
	while (ft_isspace(line[i]))
		i++;
	return (i);
}

int		skip_float_ns(char *line)
{
	int	i;

	i = 0;
	if (line[i] == '-')
		i++;
	while (ft_isdigit(line[i]))
		i++;
	if (line[i] == '.')
		i++;
	while (ft_isdigit(line[i]))
		i++;
	return (i);
}

int		skip_vect(char *line)
{
	int	i;

	i = skip_float_ns(line);
	i++;
	i += skip_float_ns(line + i);
	i++;
	i += skip_float_ns(line + i);
	while (ft_isspace(line[i]))
		i++;
	return (i);
}

int		ft_atof(char *line, float *f)
{
	int		entiere;
	int		floating;
	int		sign;
	int		size;

	floating = 0;
	entiere = ft_atoi(line);
	sign = 1;
	if (*line == '-' && line++)
		sign = -1;
	while (ft_isdigit(*line))
		line++;
	if (*line == '.')
		line++;
	floating = ft_atoi(line);
	size = size_of_int(floating);
	while (*line == '0' && line++)
		size++;
	if (floating < 0)
		return (-1);
	*f = entiere + sign * (float)(floating) * pow(0.1, size); 
	return (1);
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
	if (ft_atof(line, &amb) < 0 || amb < 0 || amb > 1)
		return (-1);
	scene->amb = amb;
	line += skip_float(line);
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

int		to_vect(char *line, t_vect *vect)
{
	float	c;

	if (ft_atof(line, &c) < 0)
		return (-1);
	line += skip_float(line);
	if (*line != ',')
		return (-1);
	vect->x = c;
	line++;
	if (ft_atof(line, &c) < 0)
		return (-1);
	line += skip_float(line);
	if (*line != ',')
		return (-1);
	vect->y = c;
	line++;
	if (ft_atof(line, &c) < 0)
		return (-1);
	vect->z = c;
	return (1);
}

int		parse_cam(int fd, t_scene *scene, char *line)
{
	static int	nb;
	t_cam		cam;

	line++;
	while (ft_isspace(*line))
		line++;	
	if (to_vect(line, &(cam.pos)) == -1)
		return (-1);
	line += skip_vect(line);
	if (to_vect(line, &(cam.axe)) == -1)
		return (-1);
	line += skip_vect(line);
	cam.fov = ft_atoi(line);
	if (cam.fov < 0 || cam.fov > 180)
		return (-1);
	(scene->cams)[nb] = cam;
	nb++;
	return (1);
}

int		parse_lum(int fd, t_scene *scene, char *line)
{
	static int	nb;
	t_lum		lum;

	line++;
	while (ft_isspace(*line))
		line++;	
	if (to_vect(line, &(lum.pos)) == -1)
		return (-1);
	line += skip_vect(line);
	if (ft_atof(line, &(lum.ratio)) == -1)
		return (-1);
	line += skip_float(line);
	if (to_col(line, &(lum.col)) == -1)
		return (-1);
	(scene->lums)[nb] = lum;
	nb++;
	return (1);
}

int		parse_sph(int fd, t_scene *scene, char *line, int nb)
{
	t_obj2	sph;

	line++;
	while (ft_isspace(*line))
		line++;
	if (to_vect(line, &(sph.o)) == -1)
		return (-1);
	line += skip_vect(line);
	if (ft_atof(line, &(sph.r)) == -1)
		return (-1);
	line += skip_float(line);
	if (to_col(line, &(sph.col)) == -1)
		return (-1);
	sph.type = 0;
	sph.r = sph.r / 2;
	(scene->objs)[nb - 1] = sph;
	return (1);
}

int		parse_pln(int fd, t_scene *scene, char *line, int nb)
{
	t_obj2	pln;

	line++;
	while (ft_isspace(*line))
		line++;
	if (to_vect(line, &(pln.o)) == -1)
		return (-1);
	line += skip_vect(line);
	if (to_vect(line, &(pln.axe)) == -1)
		return (-1);
	line += skip_vect(line);
	if (to_col(line, &(pln.col)) == -1)
		return (-1);
	pln.type = 1;
	(scene->objs)[nb - 1] = pln;
	return (1);
}

int		parse_obj(int fd, t_scene *scene, char *line)
{	
	static int	nb;

	nb++;
	if (*line == 's' && *(++line) == 'p')
		return (parse_sph(fd, scene, line, nb));
	if (*line == 'p' && *(++line) == 'l')
		return (parse_pln(fd, scene, line, nb));
	/*if (*line == 's' && *(++line) == 'q')
		return (parse_sqr(fd, scene, line, nb));
	if (*line == 'c' && *(++line) == 'y')
		return (parse_cyl(fd, scene, line, nb));
	if (*line == 't' && *(++line) == 'r')
		return (parse_trg(fd, scene, line, nb));*/
	return (-1);
}

int		parse_line(int fd, t_scene *scene, char *line)
{
	while (ft_isspace(*line))
		line++;
	if (*line == 'R')
		return (parse_res(fd, scene, line));
	if (*line == 'A')
		return (parse_amb(fd, scene, line));
	if (*line == 'c')
		return (parse_cam(fd, scene, line));
	if (*line == 'l')
		return (parse_lum(fd, scene, line));
	else
		return (parse_obj(fd, scene, line));
}

int		parse(int fd, t_scene *scene)
{
	char	*line;

	scene->cams = malloc(scene->nb_cam * sizeof(t_cam));
	scene->lums = malloc(scene->nb_lum * sizeof(t_lum));
	scene->objs = malloc(scene->nb_obj * sizeof(t_obj2));
	if (!(scene->cams) || !(scene->lums))
		return (-1);
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

int		get_numbers(int *fd, t_scene *scene, char *file_name)
{
	char	*line;
	
	while (get_next_line(*fd, &line))
	{
		if (line && line[0])
		{
			while (ft_isspace(*line))
				line++;
			if (*line == 'c')
				scene->nb_cam++;
			else if (*line == 'l')
				scene->nb_lum++;
			else if (*line != 'R' && *line != 'A')
				scene->nb_obj++;
		}
	}
	close(*fd);
	*fd = open(file_name, O_RDONLY);
	return (*fd > 0);
}

int		main(int argc, char **argv)
{
	char	*save_name;
	int		fd;
	t_scene	scene;

	if (argc == 2 || (argc == 4 && is_save(argv[2])))
	{
		fd = open(argv[1], O_RDONLY);
		if (fd > 0)
		{
			scene.nb_cam = 0;
			scene.nb_lum = 0;
			scene.nb_obj = 0;
			if (get_numbers(&fd, &scene, argv[1]) == 1 && parse(fd, &scene) == 1)
				print_parsing(scene);
			else
				printf("Error\n");
		}
	}
	else
		printf("Error\n");
	return (0);
}
