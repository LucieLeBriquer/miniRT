#include "miniRT.h"

float	inter_0sphere(t_vect ray, t_obj obj)
{
	t_vect	v;
	float	det;
	float	sc;
	float	det_sq;
	float	sol[2];

	v = mul_vect(-1, obj.o);
	sc = dot(ray, v);
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

float	inter_1square(t_vect ray, t_obj obj)
{
	(void)ray;
	(void)obj;
	return (-1);
}

float	inter_2cylindre(t_vect ray, t_obj obj)
{
	(void)ray;
	(void)obj;
	return (-1);
}

/*
** Pour un plan l'axe est defini comme la normale
*/

float	inter_3plane(t_vect ray, t_obj obj)
{
	float	t;
	float	sc;

	sc = dot(obj.axe, obj.o);
	if (sc != 0)
	{
		t = sc / dot(obj.axe, ray);
		if (t > 0)
			return (t);
	}
	return (-1);
}

float	inter_4triangle(t_vect ray, t_obj obj)
{
	(void)ray;
	(void)obj;
	return (-1);
}

int		inter(t_vect ray, t_obj *objs, t_vect *p, t_vect *n, t_col *col, 
			t_obj *obj_inter, float *t_min)
{
	float	t;
	float	(*inter_fun[4])(t_vect, t_obj);

	inter_fun[0] = &inter_0sphere;
	inter_fun[1] = &inter_1square;
	inter_fun[2] = &inter_2cylindre;
	inter_fun[3] = &inter_3plane;
	inter_fun[4] = &inter_4triangle;
	*t_min = -1;
	while (objs)
	{
		t = (inter_fun[objs->type])(ray, *objs);
		if (t > 0)
		{
			if (*t_min < 0 || *t_min > 0 && t < *t_min)
			{
				*t_min = t;
				*obj_inter = *objs;
			}
		}
		objs = objs->next;	
	}
	if (*t_min > 0)
	{
		*p = mul_vect(*t_min, ray);
		*col = obj_inter->col;
		if (obj_inter->type == 0)
			*n = sub_vect(*p, obj_inter->o);
		else
			*n = obj_inter->axe;
		normalize(n);
		return (1);
	}
	return (0);
}
