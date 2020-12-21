#include "miniRT.h"

void	init_image(t_scene *scene)
{
	int     bpp;
	int     size_line;
	int     endian;

	scene->img_ptr = mlx_new_image(scene->mlx, scene->w, scene->h);
	scene->img_data = (int *)mlx_get_data_addr(scene->img_ptr, 
	&bpp, &size_line, &endian);
}

int		color_vect_ftoi(t_vect color)
{
	int	res;
	int	r;
	int	g;
	int	b;

	r = fmin(255, fmax(color.x, 0)); 
	g = fmin(255, fmax(color.y, 0)); 
	b = fmin(255, fmax(color.z, 0)); 
	res = 256 * 256 * r + 256 * g + b;
	return (res);
}

int		get_color(t_inter itr, t_scene scn)
{
	t_vect	light;
	float	intensity;
	float	sc;
	t_vect	color_final;

	light = sub_vect(scn.lums[0].pos, itr.p);
	normalize(&light);
	sc = dot(light, itr.n);
	intensity = fabs(sc) * scn.lums[0].ratio;
	if (sc <= 0 && itr.obj_inter.type == 0)
		return (0);
	color_final = mul_col(intensity, itr.obj_inter.col);
	return (color_vect_ftoi(color_final));
}

void	draw(t_scene scn, int n_cam)
{
	t_inter	itr;
	int		i;
	int		j;
	
	i = -1;
	init_ray_org(&(itr.ray), scn.cams[n_cam].pos); 
	while (++i < scn.h)
	{
		j = -1;
		while (++j < scn.w)
		{
			init_ray_dir(&(itr.ray), j - scn.w / 2, i - scn.h / 2, 
			(-scn.w) / (2 * tan(scn.cams[n_cam].fov / 2)));
			if (inter(&itr, scn))
				(scn.img_data)[i * scn.w + j] = get_color(itr, scn); 	
			else
				(scn.img_data)[i * scn.w + j] = 0x000000; 
		}
	}
	mlx_put_image_to_window(scn.mlx, scn.win, scn.img_ptr, 0, 0);
}

int		exit_test(t_scene *scene)
{
	mlx_clear_window(scene->mlx, scene->win);
	mlx_destroy_window(scene->mlx, scene->win);
	exit(0);
	return (1);
}

int		main(int argc, char **argv)
{
	t_scene	scene;

	scene.mlx = mlx_init();
	if (parse_file(argc, argv, &scene) < 0)
		return (-1); //+ fermer le mlx avec un exit
	scene.win = mlx_new_window(scene.mlx, scene.w, scene.h, "Scene");
	init_image(&scene);
	print_parsing(scene);
	draw(scene, 0);
	mlx_hook(scene.win, 33, 0, exit_test, &scene);
	mlx_loop(scene.mlx);
	return (0);
}
