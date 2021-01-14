/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_norm.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <lle-briq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 05:28:10 by lle-briq          #+#    #+#             */
/*   Updated: 2021/01/03 16:01:50 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	norm2(t_vect v)
{
	return (v.x * v.x + v.y * v.y + v.z * v.z);
}

double	norm(t_vect v)
{
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}

void	normalize(t_vect *u)
{
	double	n;

	n = norm(*u);
	if (n > 0)
	{
		u->x = u->x / n;
		u->y = u->y / n;
		u->z = u->z / n;
	}
}

void	normalize_and_reverse(t_vect *u)
{
	double	n;

	n = norm(*u);
	if (n > 0)
	{
		u->x = -u->x / n;
		u->y = -u->y / n;
		u->z = -u->z / n;
	}
}
