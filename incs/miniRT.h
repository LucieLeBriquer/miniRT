#ifndef MINIRT_H
# define MINIRT_H
# include "mlx.h"
# include "get_next_line.h"
# include "libft.h"
# include <math.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

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

typedef struct
{
	t_vect	org;
	t_vect	dir;
}			t_ray;

typedef struct
{
	t_vect	pos;
	t_vect	axe;
	float	fov;
}			t_cam;

typedef struct
{
	float	ratio;
	t_vect	pos;
	t_col	col;
}			t_lum;

typedef struct
{
	int		type;
	t_vect	o;
	t_vect	axe;
	t_vect	p;
	t_col	col;
	float	r;
	float	h;
}			t_obj;

typedef struct
{
	t_ray	ray;
	t_ray	ray_light;
	t_vect	p;
	t_vect	n;
	t_obj	obj_inter;
	float	t;
}			t_inter;

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
	t_obj	*objs;
	void	*img_ptr;
	int		*img_data;
	void	*mlx;
	void	*win;
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
void	reverse(t_vect *a);
int		inter(t_inter *itr, t_scene scene);
void	print_parsing(t_scene scene);
int		is_save(char *s);
int		parse_trg(int fd, t_scene *scene, char *line, int nb);
int		parse_cyl(int fd, t_scene *scene, char *line, int nb);
int		parse_sqr(int fd, t_scene *scene, char *line, int nb);
int		parse_pln(int fd, t_scene *scene, char *line, int nb);
int		parse_sph(int fd, t_scene *scene, char *line, int nb);
int		skip_float(char *line);
int		skip_vect(char *line);
int		to_float(char *line, float *f);
int		to_vect(char *line, t_vect *vect);
int		to_col(char *line, t_col *col);
int		parse_obj(int fd, t_scene *scene, char *line);
int		parse_lum(int fd, t_scene *scene, char *line);
int		parse_cam(int fd, t_scene *scene, char *line);
int		parse_amb(int fd, t_scene *scene, char *line);
int		parse_res(int fd, t_scene *scene, char *line);
int		parse_file(int argc, char **argv, t_scene *scene);
void	init_ray_dir(t_ray *ray, float x, float y, float z);
void	init_ray_org(t_ray *ray, t_vect org);

#endif
