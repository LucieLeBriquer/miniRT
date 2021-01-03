/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <lle-briq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/20 16:24:51 by lle-briq          #+#    #+#             */
/*   Updated: 2021/01/03 14:40:59 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	parse_line(t_scene *scene, char *line)
{
	while (ft_isspace(*line))
		line++;
	if (line[0] == 'R' && ft_isspace(line[1]))
		return (parse_res(scene, line + 1));
	if (line[0] == 'A' && ft_isspace(line[1]))
		return (parse_amb(scene, line + 1));
	if (line[0] == 'c' && ft_isspace(line[1]))
		return (parse_cam(scene, line + 1));
	if (line[0] == 'l' && ft_isspace(line[1]))
		return (parse_lum(scene, line + 1));
	else
		return (parse_obj(scene, line));
}

int	at_least_res_cam(t_scene scene)
{
	if (scene.w <= 0 || scene.h <= 0 || scene.nb_cam <= 0)
		return (0);
	return (1);
}

int	parse(int fd, t_scene *scene)
{
	char	*line;

	scene->cams = malloc(scene->nb_cam * sizeof(t_cam));
	scene->lums = malloc(scene->nb_lum * sizeof(t_lum));
	scene->objs = malloc(scene->nb_obj * sizeof(t_obj));
	if (!(scene->cams) || !(scene->lums) || !(scene->objs))
		return (-1);
	scene->w = -1;
	scene->h = -1;
	while (get_next_line(fd, &line) == 1)
	{
		if (line && line[0])
		{
			if (line[0] == '#')
				;
			else if (parse_line(scene, line) == -1)
			{
				free(line);
				return (0);
			}
		}
		free(line);
	}
	free(line);
	return (at_least_res_cam(*scene));
}

int	get_numbers(int *fd, t_scene *scene)
{
	char	*line;
	int		is_readable;
	int		i;

	is_readable = 0;
	while (get_next_line(*fd, &line) > 0)
	{
		if (line && line[0])
		{
			is_readable = 1;
			i = 0;
			while (ft_isspace(line[i]))
				i++;
			if (line[i] == 'c' && ft_isspace(line[i + 1]))
				scene->nb_cam++;
			else if (line[i] == 'l' && ft_isspace(line[i + 1]))
				scene->nb_lum++;
			else if (line[i] != 'R' && line[i] != 'A' && line[i] != '#')
				scene->nb_obj++;
		}
		free(line);
	}
	free(line);
	return (is_readable);
}

int	parse_file(int argc, char **argv, t_scene *scene)
{
	int		fd;
	int		err_parse;

	if (argc == 2 || (argc == 4 && is_save(argv[2])))
	{
		fd = open(argv[1], O_RDONLY);
		if (fd > 0)
		{
			scene->nb_cam = 0;
			scene->nb_lum = 0;
			scene->nb_obj = 0;
			if (!get_numbers(&fd, scene))
				return (-4 * (1 + close(fd)));
			fd = open(argv[1], O_RDONLY);
			err_parse = parse(fd, scene);
			if (!err_parse)
				return (-5 * (1 + close(fd)));
			if (err_parse < 0)
				return (-6 * (1 + close(fd)));
			return (close(fd));
		}
		return (-3);
	}
	return (-2);
}
