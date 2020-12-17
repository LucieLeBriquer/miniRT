#include "miniRT.h"

t_vect	mul_vect(float t, t_vect a)
{
	t_vect	c;

	init_vect(&c, t * a.x, t * a.y, t * a.z);
	return (c);
}

t_vect	mul_col(float t, t_col a)
{
	t_vect	c;

	init_vect(&c, t * a.r, t * a.g, t * a.b);
	return (c);
}

t_vect	div_vect(float t, t_vect a)
{
	t_vect	c;

	init_vect(&c, a.x / t, a.y / t, a.z / t);
	return (c);
}

float	dot(t_vect a, t_vect b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

t_vect	add_vect(t_vect a, t_vect b)
{
	t_vect	c;

	init_vect(&c, a.x + b.x, a.y + b.y, a.z + b.z);
	return (c);
}

t_vect	sub_vect(t_vect a, t_vect b)
{
	t_vect	c;

	init_vect(&c, a.x - b.x, a.y - b.y, a.z - b.z);
	return (c);
}

t_vect	prod_vect(t_vect a, t_vect b)
{
	t_vect	c;

	c.x = a.y * b.z - a.z * b.y;
	c.y = - a.x * b.z + a.z * b.x;
	c.z = a.x * b.y - a.y * b.x;
	return (c);
}
