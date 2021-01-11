/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 15:56:17 by lle-briq          #+#    #+#             */
/*   Updated: 2021/01/11 15:56:25 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	parse_pln(t_scene *scene, char *line, int *nb)
{
	t_obj	pln;

	while (ft_isspace(*line))
		line++;
	if (to_vect(line, &(pln.o)) == -1)
		return (-1);
	line += skip_vect(line);
	if (to_vect_range(line, &(pln.axe)) == -1)
		return (-1);
	line += skip_vect(line);
	if (to_col(line, &(pln.col)) == -1)
		return (-1);
	pln.type = PLANE;
	(scene->objs)[*nb] = pln;
	*nb += 1;
	return (1);
}
