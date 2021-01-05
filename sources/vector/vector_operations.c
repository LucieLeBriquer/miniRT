/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_operations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <lle-briq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 05:29:23 by lle-briq          #+#    #+#             */
/*   Updated: 2021/01/03 16:00:34 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	init_vect(t_vect *v, double x, double y, double z)
{
	v->x = x;
	v->y = y;
	v->z = z;
}

t_vect	add_vect(t_vect a, t_vect b)
{
	t_vect	c;

	init_vect(&c, a.x + b.x, a.y + b.y, a.z + b.z);
	return (c);
}

t_vect	sub_vect(t_vect a, t_vect b)
{
	t_vect	c;

	init_vect(&c, a.x - b.x, a.y - b.y, a.z - b.z);
	return (c);
}

t_vect	mul_vect(double t, t_vect a)
{
	t_vect	c;

	init_vect(&c, t * a.x, t * a.y, t * a.z);
	return (c);
}

t_vect	div_vect(double t, t_vect a)
{
	t_vect	c;

	init_vect(&c, a.x / t, a.y / t, a.z / t);
	return (c);
}
