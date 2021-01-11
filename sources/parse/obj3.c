/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 13:39:56 by lle-briq          #+#    #+#             */
/*   Updated: 2021/01/11 15:20:28 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	fill_summits(t_obj sqr[4], t_base base, t_vect v[8])
{
	v[0] = add_vect(sqr[2].o, add_vect(mul_vect(-sqr[2].h / 2, base.x_axis),
				mul_vect(sqr[2].h / 2, base.y_axis)));
	v[1] = add_vect(sqr[2].o, add_vect(mul_vect(sqr[2].h / 2, base.x_axis),
				mul_vect(sqr[2].h / 2, base.y_axis)));
	v[2] = add_vect(sqr[2].o, add_vect(mul_vect(-sqr[2].h / 2, base.x_axis),
				mul_vect(-sqr[2].h / 2, base.y_axis)));
	v[3] = add_vect(sqr[2].o, add_vect(mul_vect(sqr[2].h / 2, base.x_axis),
				mul_vect(-sqr[2].h / 2, base.y_axis)));
	v[4] = add_vect(sqr[3].o, add_vect(mul_vect(-sqr[3].h / 2, base.x_axis),
				mul_vect(sqr[3].h / 2, base.y_axis)));
	v[5] = add_vect(sqr[3].o, add_vect(mul_vect(sqr[3].h / 2, base.x_axis),
				mul_vect(sqr[3].h / 2, base.y_axis)));
	v[6] = add_vect(sqr[3].o, add_vect(mul_vect(-sqr[3].h / 2, base.x_axis),
				mul_vect(-sqr[3].h / 2, base.y_axis)));
	v[7] = add_vect(sqr[3].o, add_vect(mul_vect(sqr[3].h / 2, base.x_axis),
				mul_vect(-sqr[3].h / 2, base.y_axis)));
}

static void	fill_triangles(t_obj trg[8], t_vect v[8])
{
	trg[0].o = v[0];
	trg[0].q = v[6];
	trg[0].p = v[2];
	trg[1].o = v[0];
	trg[1].q = v[6];
	trg[1].p = v[4];
	trg[2].o = v[1];
	trg[2].q = v[7];
	trg[2].p = v[5];
	trg[3].o = v[1];
	trg[3].q = v[7];
	trg[3].p = v[3];
}

static void	add_triangles_cube(t_scene *scn, t_obj sqr[4], t_base base, int nb)
{
	t_obj	trg[4];
	t_vect	v[8];
	int		i;

	fill_summits(sqr, base, v);
	fill_triangles(trg, v);
	i = -1;
	while (++i < 4)
	{
		trg[i].col = sqr[0].col;
		trg[i].type = TRIANGLE;
		trg[i].axe = prod_vect(sub_vect(trg[i].q, trg[i].o),
				sub_vect(trg[i].p, trg[i].o));
		normalize(&(trg[i].axe));
		(scn->objs)[nb + i] = trg[i];
	}
}

static void	add_squares_cube(t_scene *scene, t_obj cub, int nb)
{
	t_obj	sqr[4];
	t_vect	axe[4];
	t_base	base;
	int		i;

	init_base(&base, cub.axe);
	axe[0] = base.y_axis;
	axe[1] = base.y_axis;
	axe[2] = base.z_axis;
	axe[3] = base.z_axis;
	i = -1;
	while (++i < 4)
	{
		sqr[i].o = add_vect(cub.o, mul_vect(((i % 2) - 0.5) * cub.h, axe[i]));
		sqr[i].axe = axe[i];
		sqr[i].h = cub.h;
		sqr[i].type = SQUARE;
		sqr[i].col = cub.col;
	}
	i = -1;
	while (++i < 4)
		(scene->objs)[nb + i] = sqr[i];
	add_triangles_cube(scene, sqr, base, nb + 4);
}

int			parse_cub(t_scene *scene, char *line, int *nb)
{
	t_obj	cub;

	while (ft_isspace(*line))
		line++;
	if (to_vect(line, &(cub.o)) == -1)
		return (-1);
	line += skip_vect(line);
	if (to_vect_range(line, &(cub.axe)) == -1)
		return (-1);
	line += skip_vect(line);
	if (to_double(line, &(cub.h)) == -1)
		return (-1);
	line += skip_double(line);
	if (to_col(line, &(cub.col)) == -1)
		return (-1);
	add_squares_cube(scene, cub, *nb);
	*nb += 8;
	return (1);
}
