/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   circle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 15:55:05 by lle-briq          #+#    #+#             */
/*   Updated: 2021/01/11 15:55:07 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	parse_cir(t_scene *scene, char *line, int *nb)
{
	t_obj	cir;

	while (ft_isspace(*line))
		line++;
	if (to_vect(line, &(cir.o)) == -1)
		return (-1);
	line += skip_vect(line);
	if (to_vect_range(line, &(cir.axe)) == -1)
		return (-1);
	line += skip_vect(line);
	if (to_double(line, &(cir.r)) == -1)
		return (-1);
	cir.r = cir.r / 2;
	line += skip_double(line);
	if (to_col(line, &(cir.col)) == -1)
		return (-1);
	cir.type = CIRCLE;
	(scene->objs)[*nb] = cir;
	*nb += 1;
	return (1);
}
