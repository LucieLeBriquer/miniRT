/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <lle-briq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 05:58:50 by lle-briq          #+#    #+#             */
/*   Updated: 2021/01/08 17:49:51 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	init_base(t_base *base, t_vect c_axe)
{
	t_vect	u;

	init_vect(&u, 0, 1, 0);
	//base->z_axis = mul_vect(-1, c_axe);
	base->z_axis = c_axe;
	if (fabs(c_axe.y) == 1)
		init_vect(&(base->x_axis), 1, 0, 0);
	else
		base->x_axis = prod_vect(u, base->z_axis);
	base->y_axis = prod_vect(base->z_axis, base->x_axis);
	normalize(&(base->x_axis));
	normalize(&(base->y_axis));
	normalize(&(base->z_axis));
}

void	rotate(t_vect *rayd, t_base base)
{
	t_vect	tmp;
	/*rayd->x = dot(*rayd, base.x_axis);
	rayd->y = dot(*rayd, base.y_axis);
	rayd->z = dot(*rayd, base.z_axis);*/
	tmp.x = rayd->x * base.x_axis.x + rayd->y * base.y_axis.x + rayd->z *
	base.z_axis.x;
	tmp.y = rayd->x * base.x_axis.y + rayd->y * base.y_axis.y + rayd->z *
	base.z_axis.y;
	tmp.z = rayd->x * base.x_axis.z + rayd->y * base.y_axis.z + rayd->z *
	base.z_axis.z;
	*rayd = tmp;
	normalize(rayd);
}
