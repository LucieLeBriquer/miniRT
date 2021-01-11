/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   closed_cylinder.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 15:55:12 by lle-briq          #+#    #+#             */
/*   Updated: 2021/01/11 15:55:21 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	add_circles_cylinder(t_scene *scene, t_obj cyl, int nb)
{
	t_obj	cir[2];
	t_vect	o[2];

	o[0] = add_vect(cyl.o, mul_vect(cyl.h / 2, cyl.axe));
	o[1] = add_vect(cyl.o, mul_vect(-cyl.h / 2, cyl.axe));
	cir[0].o = o[0];
	cir[0].r = cyl.r;
	cir[0].axe = cyl.axe;
	cir[0].col = cyl.col;
	cir[0].type = CIRCLE;
	cir[1].o = o[1];
	cir[1].r = cyl.r;
	cir[1].axe = cyl.axe;
	cir[1].col = cyl.col;
	cir[1].type = CIRCLE;
	(scene->objs)[nb + 1] = cir[0];
	(scene->objs)[nb + 2] = cir[1];
}

int			parse_cyc(t_scene *scene, char *line, int *nb)
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
	if (to_double(line, &(cyl.r)) == -1)
		return (-1);
	cyl.r = cyl.r / 2;
	line += skip_double(line);
	if (to_double(line, &(cyl.h)) == -1)
		return (-1);
	line += skip_double(line);
	if (to_col(line, &(cyl.col)) == -1)
		return (-1);
	cyl.type = CYLINDER;
	(scene->objs)[*nb] = cyl;
	add_circles_cylinder(scene, cyl, *nb);
	*nb += 3;
	return (1);
}
