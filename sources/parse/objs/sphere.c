/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 15:56:40 by lle-briq          #+#    #+#             */
/*   Updated: 2021/01/11 15:56:46 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	parse_sph(t_scene *scene, char *line, int *nb)
{
	t_obj	sph;

	while (ft_isspace(*line))
		line++;
	if (to_vect(line, &(sph.o)) == -1)
		return (-1);
	line += skip_vect(line);
	if (to_double(line, &(sph.r)) == -1 || sph.r < 0)
		return (-1);
	line += skip_double(line);
	if (to_col(line, &(sph.col)) == -1)
		return (-1);
	sph.type = SPHERE;
	sph.r = sph.r / 2;
	(scene->objs)[*nb] = sph;
	*nb += 1;
	return (1);
}
