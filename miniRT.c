#include "miniRT.h"

int		color_convert(t_vect intensity)
{
	/*int	res;
	int	r;
	int	g;
	int	b;

	r = (int)fmin(255, fmax(255 * intensity.x, 0)); 
	g = (int)fmin(255, fmax(255 * intensity.y, 0)); 
	b = (int)fmin(255, fmax(255 * intensity.z, 0)); 
	res = 256 * 256 * r + 256 * g + b;
	return (res);*/
	(void)intensity;
	return (WHITE);
}

int		draw(void *mlx, void *win, t_obj *objs, t_scn *scn)
{
	t_vect		ray;
	t_vect		p;
	t_vect		n;
	t_vect		intens;
	t_col		col;
	int			i;
	int			j;

	i = -1;
	while (++i <= H)
	{
		j = -1;
		while (++j <= W)
		{
			init_vect(&ray, j - W / 2, i - H / 2, (-W) / (2 * tan(FOV / 2)));
			normalize(&ray);
			if (inter(ray, objs, &p, &n, &col))
			{
				p = sub_vect(scn->lum, p);
				normalize(&p);
				intens = mul_col(fmax(0, dot(p, n)) * scn->intensity / norm2(p), col);
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
	init_vect(&lum, 15, 20, -20);
	scn->lum = lum;
	scn->intensity = 1;
	return (scn);
}

int		main()
{
	void	*mlx;
	void	*win;
	t_obj	*objs;
	t_obj	*obj_new;
	t_vect	o1;
	t_col	col1;
	t_scn	*scn;

	mlx = mlx_init();
	win = mlx_new_window(mlx, W, H, "sphere");
	init_vect(&o1, 2.1, 3.4, -1.2);
	init_col(&col1, 23, 10, 240);
	objs = new_obj(0, o1, col1, 2, 3);
	obj_new = new_obj(2, o1, col1, 4, 0);
	ft_addobj(&objs, obj_new);
	obj_new = new_obj(3, o1, col1, 2, -1);
	ft_addobj(&objs, obj_new);
	scn = new_scn();
	draw(mlx, win, objs, scn);
	mlx_loop(mlx);
	return (0);
}

