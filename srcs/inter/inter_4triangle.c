/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter_4triangle.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <lle-briq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 05:45:12 by lle-briq          #+#    #+#             */
/*   Updated: 2020/12/22 00:24:33 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/*
**  A		B		C
**	o		axe		p
*/

float	inter_plane_trg(t_ray ray, t_obj trg)
{
	float	t;
	float	sc;
	t_vect	normale;
	
	normale = prod_vect(sub_vect(trg.axe, trg.o), sub_vect(trg.p, trg.o));
	normalize(&normale);
	sc = dot(sub_vect(trg.p, ray.org), normale);
	t = sc / dot(ray.dir, normale);
	if (t > 0)
		return (t);
	return (-1);
}

int		is_in_trg(t_vect u, t_vect v, t_vect w)
{
	float	det;
	float	alpha;
	float	beta;
	float	gamma;

	det = norm2(u) * norm2(v) - 2 * dot(u, v);
	beta = (dot(w, u) * norm2(v) - dot(v, u) * dot(w, v)) / det;
	gamma = (norm2(u) * dot(w, v) - dot(v, u) * dot(w, u)) / det;
	alpha = 1 - beta - gamma;
	if (alpha > 0 && beta > 0 && gamma > 0 && alpha <= 1 && beta <= 1 
	&& gamma <= 1)
		return (1);
	return (-1);
}

float	inter_4triangle(t_ray ray, t_obj trg)
{
	t_vect	u;
	t_vect	v;
	t_vect	w;
	t_vect	point;
	float	t;

	t = inter_plane_trg(ray, trg);
	if (t < 0)
		return (-1);
	point = add_vect(ray.org, mul_vect(t, ray.dir));
	u = sub_vect(trg.axe, trg.o);
	v = sub_vect(trg.p, trg.o);
	w = sub_vect(point, trg.o);
	if (is_in_trg(u, v, w))
		return (t);
	return (-1);
}
