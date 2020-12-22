/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <lle-briq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 05:58:50 by lle-briq          #+#    #+#             */
/*   Updated: 2020/12/22 22:53:44 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int		init_image(t_scene *scene)
{
	int	bpp;
	int	size_line;
	int	endian;
	int	i;

	i = -1;
	scene->img_ptr = malloc(scene->nb_cam * sizeof(void *));
	scene->img_data = malloc(scene->nb_cam * sizeof(int *));
	if (!scene->img_ptr || !scene->img_data)
		return (-1);
	while (++i < scene->nb_cam)
	{
		scene->img_ptr[i] = mlx_new_image(scene->mlx, scene->w, scene->h);
		scene->img_data[i] = (int *)mlx_get_data_addr(scene->img_ptr[i],
				&bpp, &size_line, &endian);
	}
	return (1);
}

int		main(int argc, char **argv)
{
	t_scene	scene;

	scene.mlx = mlx_init();
	if (parse_file(argc, argv, &scene) < 0)
		return (-1);
	scene.win = mlx_new_window(scene.mlx, scene.w, scene.h, "Scene");
	if (init_image(&scene) < 0)
		return (printf("Error allocation\n"));
	print_parsing(scene);
	newline();
	render(scene);
	mlx_hook(scene.win, 2, 1L<<0, next_cam, &scene);
	mlx_hook(scene.win, 33, 0, exit_scene, &scene);
	mlx_loop(scene.mlx);
	return (0);
}
