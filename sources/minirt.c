/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <lle-briq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 05:58:50 by lle-briq          #+#    #+#             */
/*   Updated: 2021/01/10 01:08:41 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	render_case(t_scene *scene, int aliasing)
{
	render(*scene, aliasing);
	mlx_put_image_to_window(scene->mlx, scene->win, (scene->img_ptr)[0], 0, 0);
	mlx_hook(scene->win, DESTROY, (1L << 17), exit_scene, scene);
	mlx_hook(scene->win, 2, (1L << 0), next_cam, scene);
	mlx_loop(scene->mlx);
}

static void	save_case(t_scene *scene, char *file, int aliasing)
{
	mlx_destroy_display(scene->mlx);
	render(*scene, aliasing);
	(void)create_bmp_image(*scene, file);
}

static int	options(int argc, char **argv, t_option *opt)
{
	int	i;

	i = 2;
	if (argc < 2)
		return (-1);
	opt->file = argv[1];
	opt->file_save = "bmp/save.bmp";
	opt->aliasing = 0;
	opt->save = 0;
	while (i < argc)
	{
		if (ft_strcmp("-a", argv[i]) == 0)
			opt->aliasing = 1;
		else if (ft_strcmp("-save", argv[i]) == 0)
		{
			opt->save = 1;
			if (i + 1 < argc && ft_strcmp("-a", argv[i + 1]) != 0)
				opt->file_save = ft_strjoin("bmp/", argv[++i]);
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
	scene.win = mlx_new_window(scene.mlx, scene.w, scene.h, opt.file);
	if (init_image(&scene) == 0)
	{
		exit_scene(&scene);
		return (ft_printf("Error : Allocation's issues\n"));
	}
	if (opt.save == 0)
		render_case(&scene, opt.aliasing);
	else if (opt.save == 1)
		save_case(&scene, opt.file_save, opt.aliasing);
	return (0);
}
