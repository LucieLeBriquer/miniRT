/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <lle-briq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/20 16:24:51 by lle-briq          #+#    #+#             */
/*   Updated: 2021/01/11 15:24:19 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int			parse_line(t_scene *scene, char *line)
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
	if (line[0] == '#' || !line[0])
		return (1);
	else
		return (parse_obj(scene, line));
}

static int	malloc_everything(t_scene *scene)
{
	scene->cams = ft_calloc(scene->nb_cam, sizeof(t_cam));
	scene->lums = ft_calloc(scene->nb_lum, sizeof(t_lum));
	scene->objs = ft_calloc(scene->nb_obj, sizeof(t_obj));
	return (!(scene->cams) || !(scene->lums) || !(scene->objs));
}

int			parse(int fd, t_scene *scene)
{
	char	*line;

	if (malloc_everything(scene))
		return (-1);
	scene->w = -1;
	scene->h = -1;
	scene->error_line = 1;
	while (get_next_line(fd, &line) == 1)
	{
		if (parse_line(scene, line) == -1)
		{
			free(line);
			return (0);
		}
		(scene->error_line)++;
		free(line);
	}
	free(line);
	scene->error_line = -1;
	return (scene->w > 0 && scene->h > 0 && scene->nb_cam > 0);
}

int			parse_file(t_option opt, t_scene *scene)
{
	int		fd;
	int		err_parse;

	fd = open(opt.file, O_RDONLY);
	if (fd > 0)
	{
		scene->nb_cam = 0;
		scene->nb_lum = 0;
		scene->nb_obj = 0;
		if (!get_numbers(&fd, scene))
			return (-4 * (1 + close(fd)));
		fd = open(opt.file, O_RDONLY);
		err_parse = parse(fd, scene);
		if (err_parse == 0)
			return (-5 * (1 + close(fd)));
		if (err_parse < 0)
			return (-6 * (1 + close(fd)));
		return (close(fd));
	}
	return (-3);
}
