/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_geometry.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <lle-briq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 05:29:22 by lle-briq          #+#    #+#             */
/*   Updated: 2021/01/04 16:40:30 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

float	dot(t_vect a, t_vect b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

t_vect	prod_vect(t_vect a, t_vect b)
{
	t_vect	c;

	c.x = a.y * b.z - a.z * b.y;
	c.y = -a.x * b.z + a.z * b.x;
	c.z = a.x * b.y - a.y * b.x;
	return (c);
}
