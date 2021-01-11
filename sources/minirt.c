/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <lle-briq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 05:58:50 by lle-briq          #+#    #+#             */
/*   Updated: 2021/01/11 12:39:42 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void		put_legend(t_scene scene)
{
	mlx_string_put(scene.mlx, scene.win, 10, 20, 16777215,
			"<- -> to switch camera");
	mlx_string_put(scene.mlx, scene.win, 10, 35, 16777215,
			"f to change filter");
	mlx_string_put(scene.mlx, scene.win, 10, 50, 16777215,
			"ESC to quit");
}

static void	render_case(t_scene *scene, int aliasing)
{
	render(*scene, aliasing);
	mlx_put_image_to_window(scene->mlx, scene->win, (scene->img_ptr)[0], 0, 0);
	put_legend(*scene);
	mlx_hook(scene->win, DESTROY, (1L << 17), exit_scene, scene);
	mlx_hook(scene->win, 2, (1L << 0), next_cam, scene);
	mlx_loop(scene->mlx);
}

static void	save_case(t_scene *scene, t_option opt)
{
	int	err_bmp;

	render(*scene, opt.aliasing);
	err_bmp = create_bmp(*scene, opt.file_save);
	if (err_bmp == -1)
		ft_printf("Error : Allocation's issues\n");
	else if (err_bmp == -2)
		ft_printf("Error : Cannot write on %s\n", opt.file_save);
	if (opt.save == 2)
		free(opt.file_save);
	exit_scene(scene);
}

static void	create_window(t_scene *scene, t_option opt)
{
	int	height;
	int	width;

	//mlx_get_screen_size(scene->mlx, &width, &height);
	width = scene->w;
	height = scene->h;
	if (opt.save == 0)
	{
		scene->w = fmin(scene->w, width);
		scene->h = fmin(scene->h, height);
		scene->win = mlx_new_window(scene->mlx, scene->w, scene->h, opt.file);
	}
	else
		scene->win = mlx_new_window(scene->mlx, 1, 1, opt.file);
}

int			main(int argc, char **argv)
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
	create_window(&scene, opt);
	if (init_image(&scene) == 0)
	{
		exit_scene(&scene);
		return (ft_printf("Error : Allocation's issues\n"));
	}
	if (opt.save == 0)
		render_case(&scene, opt.aliasing);
	else if (opt.save > 0)
		save_case(&scene, opt);
	return (0);
}
