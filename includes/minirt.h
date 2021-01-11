/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <lle-briq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 21:52:50 by lle-briq          #+#    #+#             */
/*   Updated: 2021/01/11 13:08:10 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <errno.h>
# include <math.h>
# include "mlx.h"
# include "mlx_code.h"
# include "libftfull.h"
# define CYAN "\033[36m"
# define WHITE "\033[0m"
# define SPHERE 0
# define PLANE 1
# define SQUARE 2
# define CYLINDER 3
# define TRIANGLE 4
# define CONE 5
# define CIRCLE 6
# define FILTERS 6
# define HEADER_SIZE 122
# include <stdio.h>

typedef struct	s_vect
{
	double	x;
	double	y;
	double	z;
}				t_vect;

typedef struct	s_col
{
	int		r;
	int		g;
	int		b;
}				t_col;

typedef struct	s_ray
{
	t_vect	org;
	t_vect	dir;
}				t_ray;

typedef struct	s_base
{
	t_vect	x_axis;
	t_vect	y_axis;
	t_vect	z_axis;
}				t_base;

typedef struct	s_cam
{
	t_vect	pos;
	t_vect	axe;
	double	fov;
}				t_cam;

typedef struct	s_lum
{
	double	ratio;
	t_vect	pos;
	t_col	col;
}				t_lum;

typedef struct	s_obj
{
	int		type;
	t_vect	o;
	t_vect	p;
	t_vect	q;
	t_vect	axe;
	t_col	col;
	double	r;
	double	h;
}				t_obj;

typedef struct	s_inter
{
	t_ray	ray;
	t_ray	ray_light;
	t_vect	p;
	t_vect	n;
	t_obj	obj_inter;
	double	t;
}				t_inter;

typedef struct	s_scene
{
	int		w;
	int		h;
	int		nb_cam;
	int		nb_lum;
	int		nb_obj;
	double	amb;
	t_col	amb_col;
	t_cam	*cams;
	t_lum	*lums;
	t_obj	*objs;
	void	**img_ptr;
	int		**img_data;
	void	**img_ptr_nb;
	int		**img_data_nb;
	void	*mlx;
	void	*win;
	int		error_line;
	int		endian;
	int		bpp;
	int		size_line;
}				t_scene;

typedef struct	s_option
{
	char	*file;
	char	*file_save;
	int		aliasing;
	int		save;
}				t_option;

typedef double	(*t_interfunc)(t_ray, t_obj);

/*
** Rendering and display
*/

void			render(t_scene scn, int antialiasing);
void			init_base(t_base *base, t_vect c_axe);
void			rotate(t_vect *rayd, t_base base);
int				exit_scene(t_scene *scene);
int				next_cam(int keynote, t_scene *scn);
void			free_all(t_scene scene);
int				print_errors_and_free(int err, t_scene scene);
void			progress(int i, int j, t_scene scn, int n_cam);
void			progress_final(t_scene scn, int i);
int				init_image(t_scene *scene);
void			put_legend(t_scene scene);

/*
** Vector functions
*/

void			init_vect(t_vect *v, double x, double y, double z);
void			init_col(t_col *col, int r, int g, int b);
t_vect			mul_vect(double t, t_vect a);
t_vect			mul_col(double t, t_col a);
t_vect			min_col(t_col col1, t_col col2);
t_vect			div_vect(double t, t_vect a);
double			norm2(t_vect v);
double			norm(t_vect v);
void			normalize(t_vect *u);
void			normalize_and_reverse(t_vect *u);
double			dot(t_vect a, t_vect b);
t_vect			add_vect(t_vect a, t_vect b);
t_vect			sub_vect(t_vect a, t_vect b);
t_vect			prod_vect(t_vect a, t_vect b);
void			init_ray_dir(t_ray *ray, double x, double y, double z);
void			init_ray_org(t_ray *ray, t_vect org);
void			init_rays_org(t_inter itr[4], t_vect org);
void			init_ray(t_ray *ray, t_vect org, t_vect dir);
void			rotate_rays(t_inter itr[4], t_base base);

/*
** Pixel's color calculation
*/

double			inter_0sphere(t_ray ray, t_obj obj);
double			inter_1plane(t_ray ray, t_obj obj);
double			inter_2square(t_ray ray, t_obj obj);
double			inter_3cylindre(t_ray ray, t_obj obj);
double			inter_4triangle(t_ray ray, t_obj obj);
double			inter_5cone(t_ray ray, t_obj obj);
double			inter_6circle(t_ray ray, t_obj obj);
int				inter(t_inter *itr, t_scene scene);
int				get_color(t_inter *itr, t_scene scn);
t_vect			get_colors(t_inter *itr, t_scene scn);
int				average_color(t_inter *itr, t_scene scn);
int				color_vect_ftoi(t_vect color);
int				is_visible(t_inter itr, t_scene scn, int n_lum);
int				black_white(int color);
int				sepia(int color);
int				compo(int color, int i);

/*
** Parsing
*/

int				parse_trg(t_scene *scene, char *line, int nb);
int				parse_cyl(t_scene *scene, char *line, int nb);
int				parse_sqr(t_scene *scene, char *line, int nb);
int				parse_pln(t_scene *scene, char *line, int nb);
int				parse_sph(t_scene *scene, char *line, int nb);
int				parse_con(t_scene *scene, char *line, int nb);
int				parse_cir(t_scene *scene, char *line, int nb);
int				skip_double(char *line);
int				skip_vect(char *line);
int				to_double(char *line, double *f);
int				to_vect(char *line, t_vect *vect);
int				to_vect_range(char *line, t_vect *vect);
int				to_col(char *line, t_col *col);
int				parse_obj(t_scene *scene, char *line);
int				parse_lum(t_scene *scene, char *line);
int				parse_cam(t_scene *scene, char *line);
int				parse_amb(t_scene *scene, char *line);
int				parse_res(t_scene *scene, char *line);
int				parse_file(t_option opt, t_scene *scene);
int				options(int argc, char **argv, t_option *opt);

/*
** Print A CLEAN
*/

void			print_parsing(t_scene scene);
void			print_vect(t_vect v);
void			print_double(double f);
void			print_col(t_col col);
void			newline(void);
void			newtab(void);
void			print_sph(t_obj sph, int i);
void			print_pln(t_obj pln, int i);
void			print_sqr(t_obj sqr, int i);
void			print_cyl(t_obj cyl, int i);
void			print_trg(t_obj trg, int i);

/*
** BMP save
*/

int				create_bmp(t_scene scn, char *file);

#endif
