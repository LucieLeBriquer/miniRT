#include "mlx.h"
#include <math.h>
#define W 1920
#define H 1080
#define FOV 1.0472
#define PI 3.1415926535897932
#define PURPLE 0x00A061D1
#define WHITE 0x00FFFFFF
#define BLACK 0x00000000

#include <stdio.h>

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
	t_vect	col;
}			t_sphere;

void	init_vect(t_vect *v, float x, float y, float z)
{
	v->x = x;
	v->y = y;
	v->z = z;
}

void	print_vect(t_vect v)
{
	printf("%f %f %f\n", v.x, v.y, v.z);
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
	init_vect(&(sph->col), 1, 0, 0.5);
	normalize(&(sph->col));
}

int		inter(t_vect ray, t_sphere sph, t_vect *p, t_vect *n)
{
	t_vect	v;
	float	det;
	float	sc;
	float	det_sq;
	float	sol[2];

	v = mul_vect(-1, sph.o);
	sc = dot(ray, v);
	det = 4 * (sc * sc - norm2(v) + sph.r * sph.r); 
	if (det >= 0)
	{
		det_sq = sqrt(det);
		sol[1] = (-0.5) * (2 * sc - det_sq);
		if (sol[1] < 0)
			return (0);
		sol[0] = (-0.5) * (2 * sc + det_sq);
		if (sol[0] > 0)
			*p = mul_vect(sol[0], ray);
		else
			*p = mul_vect(sol[1], ray);
		*n = sub_vect(*p, sph.o);
		normalize(n);
		return (1);
	}
	return (0);
}

int		color_convert(t_vect intensity)
{
	int	res;
	int	r;
	int	g;
	int	b;

	r = (int)fmin(255, fmax(255 * intensity.x, 0)); 
	g = (int)fmin(255, fmax(255 * intensity.y, 0)); 
	b = (int)fmin(255, fmax(255 * intensity.z, 0)); 
	res = 256 * 256 * r + 256 * g + b;
	return (res);
}

void	maj_lum(t_vect *lum)
{
	init_vect(lum, lum->x, (-1) * lum->y, lum->z);
}

int		draw(void *mlx, void *win, t_sphere sph)
{
	t_vect		ray;
	t_vect		lum;
	t_vect		p;
	t_vect		n;
	int			i;
	int			j;
	float		intense;
	t_vect		intensity;

	init_vect(&lum, 15, 20, -20);
	maj_lum(&lum);
	intense = 1;
	i = 0;
	while (i <= H)
	{
		j = 0;
		while (j <= W)
		{
			init_vect(&ray, j - W / 2, i - H / 2, (-W) / (2 * tan(FOV / 2)));
			normalize(&ray);
			if (inter(ray, sph, &p, &n))
			{
				p = sub_vect(lum, p);
				normalize(&p);
				intensity = mul_vect(fmax(0, dot(p, n)) * intense / norm2(p), \
				sph.col);
				mlx_pixel_put(mlx, win, j, i, color_convert(intensity));
			}
			j++;
		}
		i++;
	}
}

int		main()
{
	void		*mlx;
	void		*win;
	int			x;
	int			y;
	t_sphere	sph;

	mlx = mlx_init();
	win = mlx_new_window(mlx, W, H, "sphere");
	init_sphere(&sph, 0, 0, -55, 15);
	draw(mlx, win, sph);
	init_sphere(&sph, 5, 0, -30, 5);
	draw(mlx, win, sph);
	init_sphere(&sph, -5, 5, -20, 2);
	draw(mlx, win, sph);
	mlx_loop(mlx);
	return (0);
}

