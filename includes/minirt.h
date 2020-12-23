#ifndef MINIRT_H
# define MINIRT_H
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <errno.h>
# include <math.h>
# include "mlx.h"
# include "get_next_line.h"
# include "libft.h"
# include "mlx_code.h"
# define CYAN "\033[36m"
# define WHITE "\033[0m"
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
	t_vect	x_axis;
	t_vect	y_axis;
	t_vect	z_axis;
}			t_base;

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
	t_vect	p;
	t_vect	q;
	t_vect	axe;
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
	void	**img_ptr;
	int		**img_data;
	void	*mlx;
	void	*win;
	int		prog;
}			t_scene;

/*
** Rendering and display
*/

void	draw(t_scene scn, int n_cam);
void	render(t_scene scn);
void	init_base(t_base *base, t_vect c_axe);
void	rotate(t_vect *rayd, t_base base);
int		exit_scene(t_scene *scene);
int		next_cam(int keynote, t_scene *scn);

/*
** Vector functions
*/

void	init_vect(t_vect *v, float x, float y, float z);
void	init_col(t_col *col, int r, int g, int b);
t_vect	mul_vect(float t, t_vect a);
t_vect	mul_col(float t, t_col a);
t_vect	min_col(t_col col1, t_col col2);
t_vect	div_vect(float t, t_vect a);
float	norm2(t_vect v);
float	norm(t_vect v);
void	normalize(t_vect *u);
float	dot(t_vect a, t_vect b);
t_vect	add_vect(t_vect a, t_vect b);
t_vect	sub_vect(t_vect a, t_vect b);
t_vect	prod_vect(t_vect a, t_vect b);
void	init_ray_dir(t_ray *ray, float x, float y, float z);
void	init_ray_org(t_ray *ray, t_vect org);
void	init_ray(t_ray *ray, t_vect org, t_vect dir);

/*
** Pixel's color calculation
*/

float	inter_0sphere(t_ray ray, t_obj obj);
float	inter_1plane(t_ray ray, t_obj obj);
float	inter_2square(t_ray ray, t_obj obj);
float	inter_3cylindre(t_ray ray, t_obj obj);
float	inter_4triangle(t_ray ray, t_obj obj);
int		inter(t_inter *itr, t_scene scene);
int		get_color(t_inter *itr, t_scene scn);
int		color_vect_ftoi(t_vect color);
int		is_visible(t_inter itr, t_scene scn, int n_lum);

/*
** Parsing
*/

int		parse_trg(t_scene *scene, char *line, int nb);
int		parse_cyl(t_scene *scene, char *line, int nb);
int		parse_sqr(t_scene *scene, char *line, int nb);
int		parse_pln(t_scene *scene, char *line, int nb);
int		parse_sph(t_scene *scene, char *line, int nb);
int		skip_float(char *line);
int		skip_vect(char *line);
int		to_float(char *line, float *f);
int		to_vect(char *line, t_vect *vect);
int		to_col(char *line, t_col *col);
int		parse_obj(t_scene *scene, char *line);
int		parse_lum(t_scene *scene, char *line);
int		parse_cam(t_scene *scene, char *line);
int		parse_amb(t_scene *scene, char *line);
int		parse_res(t_scene *scene, char *line);
int		parse_file(int argc, char **argv, t_scene *scene);

/*
** Print
*/

void	print_parsing(t_scene scene);
int		is_save(char *s);
void	print_vect(t_vect v);
void	print_float(float f);
void	print_col(t_col col);
void	newline(void);
void	newtab(void);
void	print_sph(t_obj sph, int i);
void	print_pln(t_obj pln, int i);
void	print_sqr(t_obj sqr, int i);
void	print_cyl(t_obj cyl, int i);
void	print_trg(t_obj trg, int i);

#endif