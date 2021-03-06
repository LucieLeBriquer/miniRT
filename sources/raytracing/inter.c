/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <lle-briq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 05:43:41 by lle-briq          #+#    #+#             */
/*   Updated: 2021/01/11 13:07:53 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void		normale_type_cone(t_vect *n, t_obj obj, t_vect p)
{
	t_vect	tmp;
	double	sc;

	tmp = sub_vect(p, obj.o);
	sc = dot(obj.axe, tmp);
	if (sc != 0)
		*n = sub_vect(tmp, mul_vect(norm2(tmp) / sc, obj.axe));
	else
		init_vect(n, 0, 0, 0);
}

static t_vect	normale_type(t_vect p, t_obj obj, t_inter itr)
{
	t_vect	n;
	t_vect	tmp;

	if (obj.type == SPHERE)
		n = sub_vect(p, obj.o);
	else if (obj.type == CYLINDER)
	{
		tmp = mul_vect(dot(sub_vect(p, obj.o), obj.axe), obj.axe);
		n = sub_vect(p, add_vect(tmp, obj.o));
	}
	else if (obj.type == CONE)
		normale_type_cone(&n, obj, p);
	else
		n = obj.axe;
	if (dot(itr.ray.dir, n) > 0)
		n = mul_vect(-1, n);
	normalize(&n);
	return (n);
}

static int		fill_useful_vectors(t_inter *itr)
{
	if (itr->t > 0)
	{
		itr->p = add_vect(itr->ray.org, mul_vect(itr->t, itr->ray.dir));
		itr->n = normale_type(itr->p, itr->obj_inter, *itr);
		return (1);
	}
	return (0);
}

static void		init_inter_tab(t_interfunc inter_fun[7])
{
	inter_fun[0] = &inter_0sphere;
	inter_fun[1] = &inter_1plane;
	inter_fun[2] = &inter_2square;
	inter_fun[3] = &inter_3cylindre;
	inter_fun[4] = &inter_4triangle;
	inter_fun[5] = &inter_5cone;
	inter_fun[6] = &inter_6circle;
}

int				inter(t_inter *itr, t_scene scene)
{
	t_interfunc	inter_fun[7];
	double		new_t;
	int			i;

	itr->t = -1;
	i = -1;
	init_inter_tab(inter_fun);
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
