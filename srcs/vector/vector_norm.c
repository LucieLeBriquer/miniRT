/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_norm.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <lle-briq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 05:28:10 by lle-briq          #+#    #+#             */
/*   Updated: 2020/12/21 05:28:13 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	init_vect(t_vect *v, float x, float y, float z)
{
	v->x = x;
	v->y = y;
	v->z = z;
}

void	init_col(t_col *col, int r, int g, int b)
{
	col->r = r;
	col->g = g;
	col->b = b;
}

float	norm2(t_vect v)
{
	return (v.x * v.x + v.y * v.y + v.z * v.z);
}

float	norm(t_vect v)
{
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}

void	normalize(t_vect *u)
{
	float	n;

	n = norm(*u);
	if (n > 0)
	{
		u->x = u->x / n;
		u->y = u->y / n;
		u->z = u->z / n;
	}
}
