/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_operations2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <lle-briq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 05:29:22 by lle-briq          #+#    #+#             */
/*   Updated: 2020/12/30 15:32:00 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vect	mul_vect(float t, t_vect a)
{
	t_vect	c;

	init_vect(&c, t * a.x, t * a.y, t * a.z);
	return (c);
}

t_vect	mul_col(float t, t_col a)
{
	t_vect	c;

	init_vect(&c, t * a.r, t * a.g, t * a.b);
	return (c);
}

t_vect	div_vect(float t, t_vect a)
{
	t_vect	c;

	init_vect(&c, a.x / t, a.y / t, a.z / t);
	return (c);
}

float	dot(t_vect a, t_vect b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

t_vect	min_col(t_col col1, t_col col2)
{
	t_vect	res;

	res.x = fmin(col1.r, col2.r);
	res.y = fmin(col1.g, col2.g);
	res.z = fmin(col1.b, col2.b);
	return (res);
}
