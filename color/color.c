/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <lle-briq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 05:27:26 by lle-briq          #+#    #+#             */
/*   Updated: 2020/12/21 05:27:28 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int		color_convert(t_vect intensity)
{
	int	res;
	int	r;
	int	g;
	int	b;

	r = fmin(255, fmax(intensity.x, 0)); 
	g = fmin(255, fmax(intensity.y, 0)); 
	b = fmin(255, fmax(intensity.z, 0)); 
	res = 256 * 256 * r + 256 * g + b;
	return (res);
}

t_vect	intensity_calculator(float t, t_vect p, t_vect n, t_obj obj, float intensity)
{
	if (obj.type == 0)
		return (mul_col(fmax(0, dot(p, n)) * intensity / norm2(p), obj.col));
	if (obj.type == 3)
		return (mul_col(intensity / (t * 100), obj.col));
}
