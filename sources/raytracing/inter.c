/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <lle-briq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 05:43:41 by lle-briq          #+#    #+#             */
/*   Updated: 2020/12/30 15:31:38 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	fill_useful_vectors(t_inter *itr)
{
	if (itr->t > 0)
	{
		itr->p = add_vect(itr->ray.org, mul_vect(itr->t, itr->ray.dir));
		if (itr->obj_inter.type == 0)
			itr->n = sub_vect(itr->p, itr->obj_inter.o);
		else
			itr->n = itr->obj_inter.axe;
		normalize(&(itr->n));
		return (1);
	}
	return (0);
}

int	inter(t_inter *itr, t_scene scene)
{
	t_interfunc	inter_fun[4];
	float		new_t;
	int			i;

	inter_fun[0] = &inter_0sphere;
	inter_fun[1] = &inter_1plane;
	inter_fun[2] = &inter_2square;
	inter_fun[3] = &inter_3cylindre;
	inter_fun[4] = &inter_4triangle;
	itr->t = -1;
	i = -1;
	while (++i < scene.nb_obj)
	{
		new_t = (inter_fun[scene.objs[i].type])(itr->ray, scene.objs[i]);
		if (new_t > 0)
		{
			if (itr->t < 0 || (itr->t > 0 && new_t < itr->t))
			{
				itr->t = new_t;
				itr->obj_inter = scene.objs[i];
			}
		}
	}
	return (fill_useful_vectors(itr));
}
