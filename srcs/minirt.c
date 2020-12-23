/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <lle-briq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 05:58:50 by lle-briq          #+#    #+#             */
/*   Updated: 2020/12/23 14:13:21 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int		init_image(t_scene *scene)
{
	int	bpp;
	int	size_line;
	int	endian;
	int	i;

	i = -1;
	scene->img_ptr = malloc(scene->nb_cam * sizeof(void *));
	if (!scene->img_ptr)
		return (-1);
	scene->img_data = malloc(scene->nb_cam * sizeof(int *));
	if (!scene->img_data)
	{
		free(scene->img_ptr);
		return (-1);
	}
	while (++i < scene->nb_cam)
	{
		scene->img_ptr[i] = mlx_new_image(scene->mlx, scene->w, scene->h);
		scene->img_data[i] = (int *)mlx_get_data_addr(scene->img_ptr[i],
				&bpp, &size_line, &endian);
	}
	return (1);
}

int		print_errors(int err)
{
	if (err == -2)
	{
		printf("Error : Wrong number of arguments\n\tUse ./minirt scene.rt");
		printf(" or ./minirt scene.rt -save save_file\n");
	}
	else if (err == -3)
		printf("Error : %s\n", strerror(2));
	else if (err == -4)
		printf("Error : File is unreadable\n");
	else if (err == -5)
		printf("Error : Wrong format\n");
	return (0);
}

int		main(int argc, char **argv)
{
	t_scene	scene;
	int		error_parse;

	scene.mlx = mlx_init();
	error_parse = parse_file(argc, argv, &scene);
	if (error_parse < 0)
		return (print_errors(error_parse));
	scene.win = mlx_new_window(scene.mlx, scene.w, scene.h, argv[2]);
	if (init_image(&scene) < 0)
		return (printf("Error allocation\n"));
	print_parsing(scene);
	newline();
	render(scene);
	mlx_hook(scene.win, KEYPRESS, KEYPRESSMASK, next_cam, &scene);
	mlx_hook(scene.win, DESTROYNOTIFY, NOEVENTMASK, exit_scene, &scene);
	mlx_loop(scene.mlx);
	return (0);
}
