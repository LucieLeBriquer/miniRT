/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter_1plane.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <lle-briq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 05:44:34 by lle-briq          #+#    #+#             */
/*   Updated: 2020/12/22 00:23:38 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

float	inter_1plane(t_ray ray, t_obj obj)
{
	float	t;
	float	sc;

	//sc = dot(obj.axe, obj.o);
	sc = dot(obj.axe, sub_vect(obj.o, ray.org));
	t = sc / dot(obj.axe, ray.dir);
	if (t > 0)
		return (t);
	return (-1);
}
