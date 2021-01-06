/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter_3cylinder.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 13:31:13 by lle-briq          #+#    #+#             */
/*   Updated: 2021/01/06 13:31:23 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	solve_eq(double sc[4], double r, double sol[2])
{
	double	d[3];
	double	det;
	double	det_sq;

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

double	inter_3cylindre(t_ray ray, t_obj cyl)
{
	t_base	base;
	t_vect	origin;
	double	sc[6];
	double	t[2];

	init_base(&base, cyl.axe);
	origin = sub_vect(ray.org, cyl.o);
	sc[0] = dot(ray.dir, base.x_axis);
	sc[1] = dot(origin, base.x_axis);
	sc[2] = dot(ray.dir, base.y_axis);
	sc[3] = dot(origin, base.y_axis);
	solve_eq(sc, cyl.r, t);
	if (t[1] > 0)
	{
		sc[4] = dot(ray.dir, base.z_axis);
		sc[5] = dot(origin, base.z_axis);
		if (t[0] > 0 && fabs(t[0] * sc[4] + sc[5]) <= cyl.h / 2)
			return (t[0]);
		else if (fabs(t[1] * sc[4] + sc[5]) <= cyl.h / 2)
			return (t[1]);
	}
	return (-1);
}
