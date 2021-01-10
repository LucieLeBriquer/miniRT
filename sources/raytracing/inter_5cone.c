/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter_5cone.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 13:31:13 by lle-briq          #+#    #+#             */
/*   Updated: 2021/01/10 21:40:16 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	solve_eq(double sc[4], double s, double sol[2])
{
	double	d[3];
	double	det;
	double	det_sq;

	d[0] = sc[0] * sc[0] + sc[2] * sc[2] - s * sc[4] * sc[4];
	d[1] = 2 * (sc[0] * sc[1] + sc[2] * sc[3] - s * sc[4] * sc[5]);
	d[2] = sc[1] * sc[1] + sc[3] * sc[3] - s * sc[5] * sc[5];
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

double		inter_5cone(t_ray ray, t_obj con)
{
	t_base	base;
	t_vect	origin;
	double	sc[6];
	double	t[2];
	double	z[2];

	init_base(&base, con.axe);
	origin = sub_vect(ray.org, con.o);
	sc[0] = dot(ray.dir, base.x_axis);
	sc[1] = dot(origin, base.x_axis);
	sc[2] = dot(ray.dir, base.y_axis);
	sc[3] = dot(origin, base.y_axis);
	sc[4] = dot(ray.dir, base.z_axis);
	sc[5] = dot(origin, base.z_axis);
	solve_eq(sc, (con.r * con.r) / (con.h * con.h), t);
	if (t[1] > 0)
	{
		z[0] = t[0] * sc[4] + sc[5];
		z[1] = t[1] * sc[4] + sc[5];
		if (t[0] > 0 && z[0] > 0 && z[0] <= con.h)
			return (t[0]);
		else if (z[1] > 0 && z[1] <= con.h)
			return (t[1]);
	}
	return (-1);
}
