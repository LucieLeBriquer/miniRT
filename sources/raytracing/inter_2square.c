/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter_2square.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <lle-briq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 05:44:44 by lle-briq          #+#    #+#             */
/*   Updated: 2021/01/05 22:18:52 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	inter_2square(t_ray ray, t_obj sqr)
{
	t_base	base;
	t_vect	point;
	double	t;

	init_base(&base, sqr.axe);
	t = inter_1plane(ray, sqr);
	if (t < 0)
		return (-1);
	point = add_vect(ray.org, mul_vect(t, ray.dir));
	if (fabs(dot(sub_vect(point, sqr.o), base.x_axis)) < sqr.h / 2 &&
		fabs(dot(sub_vect(point, sqr.o), base.y_axis)) < sqr.h / 2)
		return (t);
	return (-1);
}
