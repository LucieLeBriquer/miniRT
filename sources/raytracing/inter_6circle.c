/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter_6circle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 12:49:29 by lle-briq          #+#    #+#             */
/*   Updated: 2021/01/11 13:09:45 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	inter_6circle(t_ray ray, t_obj cir)
{
	t_base	base;
	t_vect	point;
	double	t;
	double	proj[2];

	init_base(&base, cir.axe);
	t = inter_1plane(ray, cir);
	if (t < 0)
		return (-1);
	point = add_vect(ray.org, mul_vect(t, ray.dir));
	proj[0] = dot(sub_vect(point, cir.o), base.x_axis);
	proj[1] = dot(sub_vect(point, cir.o), base.y_axis);
	if (proj[0] * proj[0] + proj[1] * proj[1] <= cir.r * cir.r)
		return (t);
	return (-1);
}
