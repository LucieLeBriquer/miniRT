/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <lle-briq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 05:27:26 by lle-briq          #+#    #+#             */
/*   Updated: 2020/12/21 22:55:47 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int		color_vect_ftoi(t_vect color)
{
	int	res;
	int	r;
	int	g;
	int	b;

	r = fmin(255, fmax(color.x, 0));
	g = fmin(255, fmax(color.y, 0));
	b = fmin(255, fmax(color.z, 0));
	res = 256 * 256 * r + 256 * g + b;
	return (res);
}

int		get_color(t_inter itr, t_scene scn)
{
	t_vect	light;
	t_vect	color;
	t_vect	intensity;
	int		i;
	float	sc;

	i = -1;
	init_vect(&color, 0, 0, 0);
	while (++i < scn.nb_lum)
	{
		light = sub_vect(scn.lums[i].pos, itr.p);
		sc = norm2(light);
		if (sc == 0)
			continue;
		sc = dot(light, itr.n) / norm(light);
		if ((sc <= 0 && itr.obj_inter.type == 0) || !is_visible(itr, scn, i))
			continue;
		intensity = mul_vect(fabs(sc) * scn.lums[i].ratio,
		min_col(scn.lums[i].col, itr.obj_inter.col));
		color = add_vect(color, intensity);
	}
	color = add_vect(color, mul_col(scn.amb, scn.amb_col));
	return (color_vect_ftoi(color));
}

/*
** tranformer en t_vect l'intensite et hop la couleur de la lumiere
*/
