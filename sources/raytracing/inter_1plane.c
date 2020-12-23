/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter_1plane.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <lle-briq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 05:44:34 by lle-briq          #+#    #+#             */
/*   Updated: 2020/12/22 23:24:26 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

float	inter_1plane(t_ray ray, t_obj obj)
{
	float	t;
	float	sc;

	sc = dot(obj.axe, ray.dir);
	if (sc == 0)
		return (-1);
	t = dot(obj.axe, sub_vect(obj.o, ray.org)) / sc;
	if (t > 0)
		return (t);
	return (-1);
}
