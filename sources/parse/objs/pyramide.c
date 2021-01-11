/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pyramide.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 15:56:33 by lle-briq          #+#    #+#             */
/*   Updated: 2021/01/11 15:56:35 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	fill_summits(t_obj sqr, t_vect v[4], t_base base, t_obj pyr)
{
	v[0] = add_vect(pyr.o, mul_vect(pyr.h, pyr.axe));
	v[1] = add_vect(sqr.o, add_vect(mul_vect(-sqr.h / 2, base.x_axis),
				mul_vect(-sqr.h / 2, base.y_axis)));
	v[2] = add_vect(sqr.o, add_vect(mul_vect(sqr.h / 2, base.x_axis),
				mul_vect(-sqr.h / 2, base.y_axis)));
	v[3] = add_vect(sqr.o, add_vect(mul_vect(sqr.h / 2, base.x_axis),
				mul_vect(sqr.h / 2, base.y_axis)));
	v[4] = add_vect(sqr.o, add_vect(mul_vect(-sqr.h / 2, base.x_axis),
				mul_vect(sqr.h / 2, base.y_axis)));
}

static void	fill_square(t_obj *sqr, t_obj pyr)
{
	sqr->o = pyr.o;
	sqr->axe = pyr.axe;
	sqr->h = pyr.r;
	sqr->col = pyr.col;
	sqr->type = SQUARE;
}

static void	add_subobjs_pyra(t_scene *scene, t_obj pyr, int nb)
{
	t_obj	sqr;
	t_base	base;
	t_vect	v[5];
	t_obj	trg[4];
	int		i;

	init_base(&base, pyr.axe);
	fill_square(&sqr, pyr);
	(scene->objs)[nb] = sqr;
	fill_summits(sqr, v, base, pyr);
	i = -1;
	while (++i < 4)
	{
		trg[i].type = TRIANGLE;
		trg[i].o = v[0];
		trg[i].q = v[1 + (i % 4)];
		trg[i].p = v[1 + ((i + 1) % 4)];
		trg[i].col = pyr.col;
		trg[i].axe = prod_vect(sub_vect(trg[i].q, trg[i].o),
				sub_vect(trg[i].p, trg[i].o));
		normalize(&(trg[i].axe));
		(scene->objs)[nb + i + 1] = trg[i];
	}
}

int			parse_pyr(t_scene *scene, char *line, int *nb)
{
	t_obj	pyr;

	while (ft_isspace(*line))
		line++;
	if (to_vect(line, &(pyr.o)) == -1)
		return (-1);
	line += skip_vect(line);
	if (to_vect_range(line, &(pyr.axe)) == -1)
		return (-1);
	line += skip_vect(line);
	if (to_double(line, &(pyr.r)) == -1)
		return (-1);
	line += skip_double(line);
	if (to_double(line, &(pyr.h)) == -1)
		return (-1);
	line += skip_double(line);
	if (to_col(line, &(pyr.col)) == -1)
		return (-1);
	add_subobjs_pyra(scene, pyr, *nb);
	*nb += 5;
	return (1);
}
