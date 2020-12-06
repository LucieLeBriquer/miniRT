#include "mlx.h"
#include <math.h>
#define W 600
#define H 400
#define FOV 1.0472
#define PI 3.1415926535897932
#define PURPLE 0x00A061D1
#define WHITE 0x00FFFFFF
#define BLACK 0x00000000

typedef struct
{
	float	x;
	float	y;
	float	z;
}			t_vect;

typedef struct
{
	t_vect	o;
	float	r;
}			t_sphere;

void	init_vect(t_vect *v, float x, float y, float z)
{
	v->x = x;
	v->y = y;
	v->z = z;
}

t_vect	mul_vect(float t, t_vect a)
{
	t_vect	c;

	init_vect(&c, t * a.x, t * a.y, t * a.z);
	return (c);
}

t_vect	div_vect(float t, t_vect a)
{
	t_vect	c;

	init_vect(&c, a.x / t, a.y / t, a.z / t);
	return (c);
}

float	norm2(t_vect v)
{
	return (v.x * v.x + v.y * v.y + v.z * v.z);
}

float	norm(t_vect v)
{
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}

void	normalize(t_vect *u)
{
	float	n;

	n = norm(*u);
	if (n > 0)
	{
		u->x = u->x / n;
		u->y = u->y / n;
		u->z = u->z / n;
	}
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

void	init_sphere(t_sphere *sph, float x, float y, float z, float r)
{
	t_vect	o;

	init_vect(&o, x, y, z);
	sph->o = o;
	sph->r = r;
}

int		inter(t_vect ray, t_sphere sph)
{
	t_vect	v;
	float	det;
	float	sc;
	float	det_sq;

	v = mul_vect(-1, sph.o);
	sc = dot(ray, v);
	det = 4 * (sc * sc - norm2(v) + sph.r * sph.r); 
	if (det >= 0)
	{
		det_sq = sqrt(det);
		if ((-0.5) * (2 * sc + det_sq) > 0 || (-0.5) * (2 * sc - det_sq) > 0)
			return (1);
	}
	return (0);
}

int		draw(void *mlx, void *win)
{
	t_vect		ray;
	t_sphere	sph;
	int			i;
	int			j;

	init_sphere(&sph, 0, 0, -55, 15);
	i = 0;
	while (i <= H)
	{
		j = 0;
		while (j <= W)
		{
			init_vect(&ray, j - W / 2, i - H / 2, (-W) / (2 * tan(FOV / 2)));
			normalize(&ray);
			if (inter(ray, sph))
				mlx_pixel_put(mlx, win, j, i, PURPLE);
			j++;
		}
		i++;
	}
}

int		main()
{
	void	*mlx;
	void	*win;
	int		x;
	int		y;
	void	*param[2];

	mlx = mlx_init();
	win = mlx_new_window(mlx, W, H, "sphere");
	draw(mlx, win);
	mlx_loop(mlx);
	return (0);
}

