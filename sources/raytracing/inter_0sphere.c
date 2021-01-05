/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter_0sphere.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <lle-briq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 05:44:14 by lle-briq          #+#    #+#             */
/*   Updated: 2021/01/05 16:10:31 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	inter_0sphere(t_ray ray, t_obj obj)
{
	t_vect	v;
	double	det;
	double	sc;
	double	det_sq;
	double	sol[2];

	v = sub_vect(ray.org, obj.o);
	sc = dot(ray.dir, v);
	det = 4 * (sc * sc - norm2(v) + obj.r * obj.r);
	if (det >= 0)
	{
		det_sq = sqrt(det);
		sol[1] = (-0.5) * (2 * sc - det_sq);
		if (sol[1] < 0)
			return (-1);
		sol[0] = (-0.5) * (2 * sc + det_sq);
		if (sol[0] > 0)
			return (sol[0]);
		return (sol[1]);
	}
	return (-1);
}
