#include "miniRT.h"

int		color_convert(t_vect intensity)
{
	int	res;
	int	r;
	int	g;
	int	b;

	r = fmin(255, fmax(intensity.x, 0)); 
	g = fmin(255, fmax(intensity.y, 0)); 
	b = fmin(255, fmax(intensity.z, 0)); 
	res = 256 * 256 * r + 256 * g + b;
	return (res);
}

t_vect	intensity_calculator(float t, t_vect p, t_vect n, t_obj obj, float intensity)
{
	if (obj.type == 0)
		return (mul_col(fmax(0, dot(p, n)) * intensity / norm2(p), obj.col));
	if (obj.type == 3)
		return (mul_col(intensity / (t * 100), obj.col));
}

void	draw(void *mlx, void *win, t_obj *objs, t_scn scn)
{
	t_vect		ray;
	t_vect		p;
	t_vect		n;
	t_vect		intens;
	t_obj		obj_inter;
	t_col		col;
	int			i;
	int			j;
	float		t;
	int     bpp;
	int     size_line;
	int     endian;
	void    *img_ptr = mlx_new_image(mlx, W, H);
	int		*img_data = (int *)mlx_get_data_addr(img_ptr, &bpp, &size_line, &endian);
	
	i = -1;
	while (++i < H)
	{
		j = -1;
		while (++j < W)
		{
			init_vect(&ray, j - W / 2, i - H / 2, (-W) / (2 * tan(FOV / 2)));
			normalize(&ray);
			// faire une fonction pour le rayon, i, j
			if (inter(ray, objs, &p, &n, &col, &obj_inter, &t))
			{
				p = sub_vect(scn.lum, p);
				normalize(&p);
				// same ici en normalisant
				//fonction pour l'intensite aussi
				intens = mul_col(fabs(dot(p, n)) * scn.intensity + scn.amb, obj_inter.col);
				if (dot(p, n) <= 0 && obj_inter.type == 0)
					intens = mul_col(scn.amb, obj_inter.col);
				img_data[i * W + j] = color_convert(intens);
			}
			else
				img_data[i * W + j] = 0xFFFFFF;
		}
	}
	mlx_put_image_to_window(mlx, win, img_ptr, 0, 0);
}

t_scn	*new_scn()
{
	t_scn	*scn;
	t_vect	lum;

	scn = malloc(sizeof(scn));
	if (!scn)
		return (NULL);
	init_vect(&lum, 0, 0, 0);
	scn->lum = lum;
	scn->intensity = 0.6;
	scn->amb = 0.1;
	return (scn);
}

void	add_all_objs(t_obj **objs)
{
	t_obj	*obj_new;
	t_vect	o1;
	t_vect	o2;
	t_vect	o3;
	t_vect	axe;
	t_col	col1;
	t_col	col2;
	t_col	col3;
	t_col	col4;

	init_col(&col1, 160, 97, 209); // color of the Assembly
	init_col(&col2, 255, 105, 80); // color of the Order
	init_col(&col3, 65, 128, 219); // color of the Federation
	init_col(&col4, 51, 196, 127); // color of the Alliance
	init_vect(&o1, 0, 0, -55);
	*objs = new_obj(0, o1, o1, col1, 12, 0);
	init_vect(&o2, 5, -10, -35);
	obj_new = new_obj(0, o2, o2, col2, 4, 0);
	ft_addobj(objs, obj_new);
	init_vect(&o2, -12, 0, -55);
	obj_new = new_obj(0, o2, o2, col4, 4, 0);
	ft_addobj(objs, obj_new);
	init_vect(&axe, 0, 0, 1);
	init_vect(&o3, 0, 0, -200);
	obj_new = new_obj(3, o3, axe, col3, 0, 0);
	ft_addobj(objs, obj_new);
	init_vect(&axe, 1, 0, 0);
	init_vect(&o3, -60, 0, 0);
	obj_new = new_obj(3, o3, axe, col3, 0, 0);
	ft_addobj(objs, obj_new);
	init_vect(&axe, 0, 1, 0);
	init_vect(&o3, 0, -30, 0);
	obj_new = new_obj(3, o3, axe, col3, 0, 0);
	ft_addobj(objs, obj_new);
}

typedef struct
{
	void	*win;
	void	*mlx;
}			t_img;

int		exit_test(t_img *img)
{
	mlx_clear_window(img->mlx, img->win);
	mlx_destroy_window(img->mlx, img->win);
	exit(0);
	return (1);
}

int		main()
{
	t_obj	*objs;
	t_scn	*scn;
	t_img	img;

	img.mlx = mlx_init();
	img.win = mlx_new_window(img.mlx, W, H, "Scene");
	add_all_objs(&objs);
	scn = new_scn();
	draw(img.mlx, img.win, objs, *scn);
	mlx_hook(img.win, 33, 0, exit_test, &img);
	mlx_loop(img.mlx);
	return (0);
}
