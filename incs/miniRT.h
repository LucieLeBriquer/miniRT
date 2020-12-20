#ifndef MINIRT_H
# define MINIRT_H
# include "mlx.h"
# include "get_next_line.h"
# include "libft.h"
# include <math.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# define W 800
# define H 600
# define FOV 1.0472
# define PI 3.1415926535897932

# include <stdio.h>

typedef struct
{
	float	x;
	float	y;
	float	z;
}			t_vect;

typedef struct
{
	int		r;
	int		g;
	int		b;
}			t_col;

typedef struct s_obj
{
	int				type;
	t_vect			o;
	t_vect			axe;
	t_col			col;
	float			r;
	float			h;
	struct s_obj	*next;
}					t_obj;

typedef struct
{
	t_vect	lum;
	float	intensity;
	float	amb;
}		t_scn;

typedef struct
{
	t_vect			pos;
	t_vect			axe;
	float			fov;
}					t_cam;

typedef struct
{
	float			ratio;
	t_vect			pos;
	t_col			col;
}					t_lum;

typedef struct
{
	int				type;
	t_vect			o;
	t_vect			axe;
	t_col			col;
	float			r;
	float			h;
}					t_obj2;

typedef struct
{
	int		w;
	int		h;
	int		nb_cam;
	int		nb_lum;
	int		nb_obj;
	float	amb;
	t_col	amb_col;
	t_cam	*cams;
	t_lum	*lums;
	t_obj2	*objs;
}			t_scene;

void	init_vect(t_vect *v, float x, float y, float z);
void	print_vect(t_vect v);
void	init_col(t_col *col, int r, int g, int b);
void	ft_addobj(t_obj **obj, t_obj *obj_new);
void	ft_objiter(t_obj *objs, void (*f)(t_obj));
t_obj	*new_obj(int type, t_vect o, t_vect axe, t_col col, float r, float h);
void	show_obj(t_obj obj);
t_vect	mul_vect(float t, t_vect a);
t_vect	mul_col(float t, t_col a);
t_vect	div_vect(float t, t_vect a);
float	norm2(t_vect v);
float	norm(t_vect v);
void	normalize(t_vect *u);
float	dot(t_vect a, t_vect b);
t_vect	add_vect(t_vect a, t_vect b);
t_vect	sub_vect(t_vect a, t_vect b);
t_vect	prod_vect(t_vect a, t_vect b);
int		color_convert(t_vect intensity);
void	maj_lum(t_vect *lum);
int		inter(t_vect ray, t_obj *objs, t_vect *p, t_vect *n, t_col *col, 
		t_obj *obj_inter, float *t);
int		is_save(char *s);

void	print_parsing(t_scene scene);

#endif
