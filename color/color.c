/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <lle-briq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 05:27:26 by lle-briq          #+#    #+#             */
/*   Updated: 2020/12/21 05:58:12 by lle-briq         ###   ########.fr       */
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
	float	intensity;
	float	sc;
	t_vect	color_final;

	light = sub_vect(scn.lums[0].pos, itr.p);
	normalize(&light);
	sc = dot(light, itr.n);
	intensity = fabs(sc) * scn.lums[0].ratio;
	if (sc <= 0 && itr.obj_inter.type == 0)
		return (0);
	color_final = mul_col(intensity, itr.obj_inter.col);
	return (color_vect_ftoi(color_final));
}
