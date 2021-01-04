/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter_3cylindre.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <lle-briq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 05:44:57 by lle-briq          #+#    #+#             */
/*   Updated: 2021/01/04 18:37:13 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	solve_eq(float sc[4], float r, float sol[2])
{
	float	d[3];
	float	det;
	float	det_sq;

	d[0] = sc[0] * sc[0] + sc[2] * sc[2];
	d[1] = 2 * (sc[0] * sc[1] + sc[2] * sc[3]);
	d[2] = sc[1] * sc[1] + sc[3] * sc[3] - r * r;
	det = d[1] * d[1] - 4 * d[0] * d[2];
	sol[0] = -1;
	sol[1] = -1;
	if (det >= 0)
	{
		det_sq = sqrt(det);
		sol[1] = (-d[1] + det_sq) / (2 * d[0]);
		sol[0] = (-d[1] - det_sq) / (2 * d[0]);
	}
}

float	inter_3cylindre(t_ray ray, t_obj cyl)
{
	t_base	base;
	float	sc[6];
	float	t[2];

	init_base(&base, cyl.axe);
	sc[0] = dot(ray.dir, base.x_axis);
	sc[1] = dot(ray.org, base.x_axis);
	sc[2] = dot(ray.dir, base.y_axis);
	sc[3] = dot(ray.org, base.y_axis);
	solve_eq(sc, cyl.r, t);
	if (t[1] > 0)
	{
		sc[4] = dot(ray.dir, base.z_axis);
		sc[5] = dot(ray.org, base.z_axis);
		if (t[0] > 0 && fabs(t[0] * sc[4] + sc[5]) <= cyl.h / 2)
			return (t[0]);
		else if (fabs(t[1] * sc[4] + sc[5]) <= cyl.h / 2)
			return (t[1]);
	}
	return (-1);
}
