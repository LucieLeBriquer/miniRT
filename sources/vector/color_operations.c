/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_operations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <lle-briq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 05:29:22 by lle-briq          #+#    #+#             */
/*   Updated: 2021/01/03 16:00:23 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	init_col(t_col *col, int r, int g, int b)
{
	col->r = r;
	col->g = g;
	col->b = b;
}

t_vect	mul_col(double t, t_col a)
{
	t_vect	c;

	init_vect(&c, t * a.r, t * a.g, t * a.b);
	return (c);
}

t_vect	min_col(t_col col1, t_col col2)
{
	t_vect	res;

	res.x = fmin(col1.r, col2.r);
	res.y = fmin(col1.g, col2.g);
	res.z = fmin(col1.b, col2.b);
	return (res);
}
