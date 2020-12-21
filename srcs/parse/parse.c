/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <lle-briq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/20 16:24:51 by lle-briq          #+#    #+#             */
/*   Updated: 2020/12/21 05:54:42 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int		parse_line(t_scene *scene, char *line)
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

int		parse(int fd, t_scene *scene)
{
	char	*line;

	scene->cams = malloc(scene->nb_cam * sizeof(t_cam));
	scene->lums = malloc(scene->nb_lum * sizeof(t_lum));
	scene->objs = malloc(scene->nb_obj * sizeof(t_obj));
	if (!(scene->cams) || !(scene->lums) || !(scene->objs))
		return (0);
	while (get_next_line(fd, &line))
	{
		if (line && line[0])
		{
			if (line[0] == '#')
				continue;
			if (parse_line(scene, line) == -1)
				return (0);
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
			if (*line == 'c' && ft_isspace(line[1]))
				scene->nb_cam++;
			else if (*line == 'l' && ft_isspace(line[1]))
				scene->nb_lum++;
			else if (*line != 'R' && *line != 'A')
				scene->nb_obj++;
		}
	}
	close(*fd);
	*fd = open(file_name, O_RDONLY);
	return (*fd > 0);
}

int		parse_file(int argc, char **argv, t_scene *scene)
{
	int		fd;

	if (argc == 2 || (argc == 4 && is_save(argv[2])))
	{
		fd = open(argv[1], O_RDONLY);
		if (fd > 0)
		{
			scene->nb_cam = 0;
			scene->nb_lum = 0;
			scene->nb_obj = 0;
			if (get_numbers(&fd, scene, argv[1]) && parse(fd, scene))
				return (close(fd));
			else
				printf("Error\n");
		}
	}
	else
		printf("Error\n");
	return (-1);
}