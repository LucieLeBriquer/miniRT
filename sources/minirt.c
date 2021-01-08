/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <lle-briq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 05:58:50 by lle-briq          #+#    #+#             */
/*   Updated: 2021/01/08 13:12:08 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	init_image(t_scene *scene)
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

void	render_case(t_scene *scene)
{
	mlx_put_image_to_window(scene->mlx, scene->win, (scene->img_ptr)[0], 0, 0);
	mlx_hook(scene->win, DESTROY, (1L << 17), exit_scene, scene);
	mlx_hook(scene->win, 2, (1L << 0), next_cam, scene);
	mlx_loop(scene->mlx);
}

void	save_case(t_scene *scene, char *file)
{
	(void)bmp_create(*scene, file);
}

int	options(int argc, char **argv, t_option *opt)
{
	int	i;

	i = 2;
	if (argc < 2)
		return (-1);
	opt->file = argv[1];
	opt->file_save = "save.bmp";
	opt->aliasing = 0;
	opt->save = 0;
	while (i < argc)
	{
		if (ft_strcmp("-a", argv[i]) == 0)
			opt->aliasing = 1;
		else if (ft_strcmp("-save", argv[i]) == 0 && ++i < argc)
		{
			opt->save = 1;
			opt->file_save = argv[i];
		}
		else
			return (-1);
		i++;
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_scene		scene;
	t_option	opt;
	int			error_parse;

	scene.mlx = mlx_init();
	if (options(argc, argv, &opt) < 0)
		return (print_errors_and_free(-2, scene));
	error_parse = parse_file(opt, &scene);
	if (error_parse < 0)
		return (print_errors_and_free(error_parse, scene));
	scene.win = mlx_new_window(scene.mlx, scene.w, scene.h, argv[1]);
	if (init_image(&scene) < 0)
	{
		exit_scene(&scene);
		return (ft_printf("Error : Allocation's issues\n"));
	}
	render(scene, 1);
	if (argc == 2)
		render_case(&scene);
	else if (argc == 3)
		save_case(&scene, "save.bmp");
	return (0);
}
