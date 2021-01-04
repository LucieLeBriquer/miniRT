/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter_3cylindre.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <lle-briq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 05:44:57 by lle-briq          #+#    #+#             */
/*   Updated: 2021/01/04 16:59:02 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static float	inter_infinite_cyl(t_ray ray, t_obj cyl)
{
	float	d[3];
	float	sc[2];
	float	det;
	float	det_sq;
	float	sol[2];

	sc[0] = dot(ray.dir, cyl.axe);
	sc[1] = dot(ray.org, cyl.axe);
	d[0] = 1 - sc[0] * sc[0];
	d[1] = 2 * (dot(ray.org, ray.dir) - sc[0] * sc[1]); 
	d[2] = norm2(ray.org) - sc[1] * sc[1] - cyl.r * cyl.r;
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

float	inter_3cylindre(t_ray ray, t_obj cyl)
{
	float	t;

	t = inter_infinite_cyl(ray, cyl);
	return (t);
}
