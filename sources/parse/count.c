/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <lle-briq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/20 16:24:51 by lle-briq          #+#    #+#             */
/*   Updated: 2021/01/11 15:24:23 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	nb_subobjects(char *line, int i)
{
	if (line[i] == 'c' && line[i + 1] == 'c')
		return (3);
	if (line[i] == 'c' && line[i + 1] == 'b')
		return (8);
	if (line[i] == 'p' && line[i + 1] == 'y')
		return (5);
	return (1);
}

int			get_numbers(int *fd, t_scene *scene)
{
	char	*line;
	int		is_readable;
	int		i;

	is_readable = 0;
	while (get_next_line(*fd, &line) > 0)
	{
		is_readable = 1;
		i = 0;
		while (ft_isspace(line[i]))
			i++;
		if (line[i] == 'c' && ft_isspace(line[i + 1]))
			scene->nb_cam++;
		else if (line[i] == 'l' && ft_isspace(line[i + 1]))
			scene->nb_lum++;
		else if (line[i] != '\0' && line[i] != 'R' &&
				line[i] != 'A' && line[i] != '#')
			scene->nb_obj += nb_subobjects(line, i);
		free(line);
	}
	free(line);
	return (is_readable);
}
