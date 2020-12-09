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

int		draw(void *mlx, void *win, t_obj *objs, t_scn scn)
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

	i = -1;
	while (++i <= H)
	{
		j = -1;
		while (++j <= W)
		{
			init_vect(&ray, j - W / 2, i - H / 2, (-W) / (2 * tan(FOV / 2)));
			normalize(&ray);
			if (inter(ray, objs, &p, &n, &col, &obj_inter, &t))
			{
				p = sub_vect(scn.lum, p);
				normalize(&p);
				intens = mul_col(fmax(0, dot(p, n)) * scn.intensity, obj_inter.col);
				mlx_pixel_put(mlx, win, j, i, color_convert(intens));
			}
		}
	}
}

t_scn	*new_scn()
{
	t_scn	*scn;
	t_vect	lum;

	scn = malloc(sizeof(scn));
	if (!scn)
		return (NULL);
	init_vect(&lum, 15, -20, -20);
	scn->lum = lum;
	scn->intensity = 0.6;
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

	init_vect(&o1, 0, 0, -55);
	init_col(&col1, 250, 20, 230);
	init_col(&col2, 20, 250, 230);
	*objs = new_obj(0, o1, o1, col1, 12, 0);
	init_vect(&o2, 5, 0, -35);
	obj_new = new_obj(0, o2, o2, col2, 4, 0);
	ft_addobj(objs, obj_new);
	init_vect(&axe, 0, 0, 1);
	init_vect(&o3, 0, 0, -200);
	obj_new = new_obj(3, o3, axe, col2, 0, 0);
	ft_addobj(objs, obj_new);
	init_vect(&axe, 1, 0, 0);
	init_vect(&o3, -60, 0, 0);
	obj_new = new_obj(3, o3, axe, col2, 0, 0);
	ft_addobj(objs, obj_new);
	init_vect(&axe, 0, 1, 0);
	init_vect(&o3, 0, -60, 0);
	obj_new = new_obj(3, o3, axe, col2, 0, 0);
	ft_addobj(objs, obj_new);
	init_vect(&axe, 0, 1, 0);
	init_vect(&o3, 0, 40, 0);
	obj_new = new_obj(3, o3, axe, col2, 0, 0);
	ft_addobj(objs, obj_new);
}

int		main()
{
	void	*mlx;
	void	*win;
	t_obj	*objs;
	t_scn	*scn;

	mlx = mlx_init();
	win = mlx_new_window(mlx, W, H, "Scene");
	add_all_objs(&objs);
	scn = new_scn();
	draw(mlx, win, objs, *scn);
	mlx_loop(mlx);
	return (0);
}

