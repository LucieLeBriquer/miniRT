#include "miniRT.h"

float	inter_0sphere(t_ray ray, t_obj obj)
{
	t_vect	v;
	float	det;
	float	sc;
	float	det_sq;
	float	sol[2];

	v = sub_vect(ray.org, obj.o);
	sc = dot(ray.dir, v);
	det = 4 * (sc * sc - norm2(v) + obj.r * obj.r); 
	if (det >= 0)
	{
		det_sq = sqrt(det);
		sol[1] = (-0.5) * (2 * sc - det_sq);
		if (sol[1] < 0)
			return (0);
		sol[0] = (-0.5) * (2 * sc + det_sq);
		if (sol[0] > 0)
			return (sol[0]);
		else
			return (sol[1]);
	}
	return (-1);
}

float	inter_1plane(t_ray ray, t_obj obj)
{
	float	t;
	float	sc;

	sc = dot(obj.axe, obj.o);
	if (sc != 0)
	{
		t = sc / dot(obj.axe, ray.dir);
		if (t > 0)
			return (t);
	}
	return (-1);
}

float	inter_2square(t_ray ray, t_obj obj)
{
	(void)ray;
	(void)obj;

	return (-1);
}

float	inter_3cylindre(t_ray ray, t_obj obj)
{
	(void)ray;
	(void)obj;

	return (-1);
}

float	inter_4triangle(t_ray ray, t_obj obj)
{
	(void)ray;
	(void)obj;

	return (-1);
}

int		fill_useful_vectors(t_inter *itr)
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

int		inter(t_inter *itr, t_scene scene)
{
	float	(*inter_fun[4])(t_ray, t_obj);
	float	new_t;
	int		i;

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
			if (itr->t < 0 || itr->t > 0 && new_t < itr->t)
			{
				itr->t = new_t;
				itr->obj_inter = scene.objs[i];
			}
		}
	}
	return (fill_useful_vectors(itr));
}
