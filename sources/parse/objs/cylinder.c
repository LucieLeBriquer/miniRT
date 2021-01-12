/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 15:55:57 by lle-briq          #+#    #+#             */
/*   Updated: 2021/01/11 15:56:12 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	parse_cyl(t_scene *scene, char *line, int *nb)
{
	t_obj	cyl;

	while (ft_isspace(*line))
		line++;
	if (to_vect(line, &(cyl.o)) == -1)
		return (-1);
	line += skip_vect(line);
	if (to_vect_range(line, &(cyl.axe)) == -1)
		return (-1);
	line += skip_vect(line);
	if (to_double(line, &(cyl.r)) == -1 || cyl.r < 0)
		return (-1);
	cyl.r = cyl.r / 2;
	line += skip_double(line);
	if (to_double(line, &(cyl.h)) == -1 || cyl.h < 0)
		return (-1);
	line += skip_double(line);
	if (to_col(line, &(cyl.col)) == -1)
		return (-1);
	cyl.type = CYLINDER;
	(scene->objs)[*nb] = cyl;
	*nb += 1;
	return (1);
}
