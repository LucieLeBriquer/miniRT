/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <lle-briq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 05:58:50 by lle-briq          #+#    #+#             */
/*   Updated: 2020/12/22 23:23:44 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	init_base(t_base *base, t_vect c_axe)
{
	t_vect	u;

	init_vect(&u, 0, 1, 0);
	base->z_axis = c_axe;
	if (fabs(c_axe.y) == 1)
	{
		if (c_axe.y == -1)
			init_vect(&(base->x_axis), -1, 0, 0);
		else
			init_vect(&(base->x_axis), 1, 0, 0);
	}
	else
		base->x_axis = prod_vect(base->z_axis, u);
	base->y_axis = prod_vect(base->x_axis, base->z_axis);
}

void	rotate(t_vect *rayd, t_base base)
{
	rayd->x = dot(*rayd, base.x_axis);
	rayd->y = dot(*rayd, base.y_axis);
	rayd->z = dot(*rayd, base.z_axis);
	normalize(rayd);
}
