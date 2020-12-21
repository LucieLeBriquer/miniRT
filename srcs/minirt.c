/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <lle-briq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 05:58:50 by lle-briq          #+#    #+#             */
/*   Updated: 2020/12/21 21:23:39 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	init_image(t_scene *scene)
{
	int	bpp;
	int	size_line;
	int	endian;

	scene->img_ptr = mlx_new_image(scene->mlx, scene->w, scene->h);
	scene->img_data = (int *)mlx_get_data_addr(scene->img_ptr,
	&bpp, &size_line, &endian);
}

int		is_visible(t_inter itr, t_scene scn, int n_lum)
{
	t_inter	omb;
	t_vect	v;

	v = sub_vect(scn.lums[n_lum].pos, itr.p);
	init_ray(&(omb.ray), add_vect(itr.p, mul_vect(0.01, itr.n)), v);
	if (inter(&omb, scn) && omb.t * omb.t < norm(v))
		return (0);
	return (1);
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
			init_ray_dir(&(itr.ray), j - scn.w / 2, -i + scn.h / 2,
			(-scn.w) / (2 * tan(scn.cams[n_cam].fov * M_PI / 360)));
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
	free(scene->lums);
	free(scene->cams);
	free(scene->objs);
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
		return (-1);
	scene.win = mlx_new_window(scene.mlx, scene.w, scene.h, "Scene");
	init_image(&scene);
	print_parsing(scene);
	draw(scene, 0);
	mlx_hook(scene.win, 33, 0, exit_test, &scene);
	mlx_loop(scene.mlx);
	return (0);
}
