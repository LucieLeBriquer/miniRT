/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter_4triangle.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <lle-briq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 05:45:12 by lle-briq          #+#    #+#             */
/*   Updated: 2021/01/05 22:11:06 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
**  A		B		C
**	o		axe		p
*/

int	is_inside(t_vect u, t_vect v, t_vect w, t_vect point)
{
	t_vect	v1;
	t_vect	v2;

	v1 = prod_vect(sub_vect(v, u), sub_vect(w, u));
	v2 = prod_vect(sub_vect(v, u), sub_vect(point, u));
	if (dot(v1, v2) < 0.00001)
		return (0);
	return (1);
}

double	inter_4triangle(t_ray ray, t_obj trg)
{
	t_vect	point;
	double	t;

	t = inter_1plane(ray, trg);
	if (t < 0)
		return (-1);
	point = add_vect(ray.org, mul_vect(t, ray.dir));
	if (is_inside(trg.o, trg.p, trg.q, point) == 0)
		return (-1);
	if (is_inside(trg.p, trg.q, trg.o, point) == 0)
		return (-1);
	if (is_inside(trg.q, trg.o, trg.p, point) == 0)
		return (-1);
	return (t);
}
