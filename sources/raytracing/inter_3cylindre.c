/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter_3cylindre.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <lle-briq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 05:44:57 by lle-briq          #+#    #+#             */
/*   Updated: 2021/01/04 18:18:41 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static float	solve_eq(float sc[4], float r)
{
	float	d[3];
	float	det;
	float	det_sq;
	float	sol[2];

	d[0] = sc[0] * sc[0] + sc[2] * sc[2];
	d[1] = 2 * (sc[0] * sc[1] + sc[2] * sc[3]);
	d[2] = sc[1] * sc[1] + sc[3] * sc[3] - r * r;
	det = d[1] * d[1] - 4 * d[0] * d[2];
	if (det >= 0)
	{
		det_sq = sqrt(det);
		sol[1] = (-d[1] + det_sq) / (2 * d[0]);
		if (sol[1] < 0)
			return (-1);
		sol[0] = (-d[1] - det_sq) / (2 * d[0]);
		if (sol[0] > 0)
			return (sol[0]);
		else
			return (sol[1]);
	}
	return (-1);
}

static float	inter_infinite_cyl(t_ray ray, t_obj cyl)
{
	t_base	base;
	float	sc[4];

	init_base(&base, cyl.axe);
	sc[0] = dot(ray.dir, base.x_axis);
	sc[1] = dot(ray.org, base.x_axis);
	sc[2] = dot(ray.dir, base.y_axis);
	sc[3] = dot(ray.org, base.y_axis);
	return(solve_eq(sc, cyl.r));
}

float	inter_3cylindre(t_ray ray, t_obj cyl)
{
	float	t;

	t = inter_infinite_cyl(ray, cyl);
	return (t);
}
