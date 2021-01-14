/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <lle-briq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 05:58:50 by lle-briq          #+#    #+#             */
/*   Updated: 2021/01/11 21:34:16 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	render_case(t_scene *scene, int aliasing)
{
	render(*scene, aliasing, scene->nb_cam);
	display(scene);
	put_legend(*scene);
	mlx_hook(scene->win, DESTROY, (1L << 17), exit_scene, scene);
	mlx_hook(scene->win, 2, (1L << 0), next_cam, scene);
	mlx_hook(scene->win, 12, (1L << 15), display, scene);
	mlx_loop(scene->mlx);
}

static void	save_case(t_scene *scene)
{
	int	err_bmp;

	render(*scene, scene->aliasing, 1);
	err_bmp = create_bmp(*scene, scene->file_save);
	if (err_bmp == -1)
		ft_printf("Error : Allocation's issues\n");
	else if (err_bmp == -2)
		ft_printf("Error : Cannot write on %s\n", scene->file_save);
	if (scene->save == 2)
		free(scene->file_save);
	exit_scene(scene);
}

static void	create_window(t_scene *scene)
{
	int	height;
	int	width;

	mlx_get_screen_size(scene->mlx, &width, &height);
	if (scene->save == 0)
	{
		scene->w = fmin(scene->w, width);
		scene->h = fmin(scene->h, height);
		scene->win = mlx_new_window(scene->mlx, scene->w,
			scene->h, scene->file);
	}
	else
		scene->win = mlx_new_window(scene->mlx, 1, 1, scene->file);
}

int			main(int argc, char **argv)
{
	t_scene		scene;
	int			error_parse;

	scene.mlx = mlx_init();
	error_parse = options(argc, argv, &scene);
	if (error_parse == -1)
		return (print_errors_and_free(-2, scene));
	else if (error_parse == -2)
		return (print_errors_and_free(-7, scene));
	error_parse = parse_file(&scene);
	if (error_parse < 0)
		return (print_errors_and_free(error_parse, scene));
	create_window(&scene);
	if (init_image(&scene) == 0)
	{
		exit_scene(&scene);
		return (ft_printf("Error : Allocation's issues\n"));
	}
	if (scene.save == 0)
		render_case(&scene, scene.aliasing);
	else if (scene.save > 0)
		save_case(&scene);
	return (0);
}
