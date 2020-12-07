#ifndef MINIRT_H
# define MINIRT_H
# include "mlx.h"
# include <math.h>
# define W 1920
# define H 1080
# define FOV 1.0472
# define PI 3.1415926535897932
# define PURPLE 0x00A061D1
# define WHITE 0x00FFFFFF
# define BLACK 0x00000000

# include <stdio.h>

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

void	init_vect(t_vect *v, float x, float y, float z);
void	print_vect(t_vect v);
t_vect	mul_vect(float t, t_vect a);
t_vect	div_vect(float t, t_vect a);
float	norm2(t_vect v);
float	norm(t_vect v);
void	normalize(t_vect *u);
float	dot(t_vect a, t_vect b);
t_vect	add_vect(t_vect a, t_vect b);
t_vect	sub_vect(t_vect a, t_vect b);
void	init_sphere(t_sphere *sph, float x, float y, float z, float r);
int		inter(t_vect ray, t_sphere sph, t_vect *p, t_vect *n);
int		color_convert(t_vect intensity);
void	maj_lum(t_vect *lum);
int		draw(void *mlx, void *win, t_sphere sph);

#endif
