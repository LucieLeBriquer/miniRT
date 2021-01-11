/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   square.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 15:56:51 by lle-briq          #+#    #+#             */
/*   Updated: 2021/01/11 15:57:05 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	parse_sqr(t_scene *scene, char *line, int *nb)
{
	t_obj	sqr;

	while (ft_isspace(*line))
		line++;
	if (to_vect(line, &(sqr.o)) == -1)
		return (-1);
	line += skip_vect(line);
	if (to_vect_range(line, &(sqr.axe)) == -1)
		return (-1);
	line += skip_vect(line);
	if (to_double(line, &(sqr.h)) == -1)
		return (-1);
	line += skip_double(line);
	if (to_col(line, &(sqr.col)) == -1)
		return (-1);
	sqr.type = SQUARE;
	(scene->objs)[*nb] = sqr;
	*nb += 1;
	return (1);
}
