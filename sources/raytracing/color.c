/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <lle-briq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 05:27:26 by lle-briq          #+#    #+#             */
/*   Updated: 2021/01/08 23:23:46 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	color_vect_ftoi(t_vect color)
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

int	is_visible(t_inter itr, t_scene scn, int n_lum)
{
	t_inter	omb;
	t_vect	v;
	double	epsilon;

	v = sub_vect(scn.lums[n_lum].pos, itr.p);
	epsilon = 0.00001;
	init_ray(&(omb.ray), add_vect(itr.p, mul_vect(epsilon, itr.n)), v);
	if (inter(&omb, scn) && omb.t * omb.t < norm2(v) && omb.t > 2 * epsilon)
		return (0);
	return (1);
}

int	get_color(t_inter *itr, t_scene scn)
{
	t_vect	light;
	t_vect	color;
	t_vect	intensity;
	int		i;
	double	sc;

	i = -1;
	init_vect(&color, 0, 0, 0);
	if (!inter(itr, scn))
		return (0);
	while (++i < scn.nb_lum)
	{
		light = sub_vect(scn.lums[i].pos, itr->p);
		sc = norm2(light);
		if (sc == 0)
			continue ;
		sc = dot(light, itr->n) / sc;
		if (!is_visible(*itr, scn, i))
			continue ;
		intensity = mul_vect(fabs(sc) * scn.lums[i].ratio * 100,
				min_col(scn.lums[i].col, itr->obj_inter.col));
		color = add_vect(color, intensity);
	}
	color = add_vect(color, mul_col(scn.amb, scn.amb_col));
	return (color_vect_ftoi(color));
}

t_vect	get_colors(t_inter *itr, t_scene scn)
{
	t_vect	light;
	t_vect	color;
	t_vect	intensity;
	int		i;
	double	sc;

	i = -1;
	init_vect(&color, 0, 0, 0);
	if (!inter(itr, scn))
		return (color);
	while (++i < scn.nb_lum)
	{
		light = sub_vect(scn.lums[i].pos, itr->p);
		sc = norm2(light);
		if (sc == 0)
			continue ;
		sc = dot(light, itr->n) / sc;
		if (!is_visible(*itr, scn, i))
			continue ;
		intensity = mul_vect(fabs(sc) * scn.lums[i].ratio * 100,
				min_col(scn.lums[i].col, itr->obj_inter.col));
		color = add_vect(color, intensity);
	}
	color = add_vect(color, mul_col(scn.amb, scn.amb_col));
	return (color);
}

int	average_color(t_inter *itr, t_scene scn)
{
	t_vect	color[4];
	t_vect	average;

	color[0] = get_colors(itr, scn);
	color[1] = get_colors(itr + 1, scn);
	color[2] = get_colors(itr + 2, scn);
	color[3] = get_colors(itr + 3, scn);
	average = color[0];
	average = add_vect(average, color[1]);
	average = add_vect(average, color[2]);
	average = add_vect(average, color[3]);
	average = mul_vect(0.25, average);
	return (color_vect_ftoi(average));
}
