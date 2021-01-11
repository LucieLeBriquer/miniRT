/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <lle-briq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 05:58:50 by lle-briq          #+#    #+#             */
/*   Updated: 2021/01/11 17:18:16 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int			exit_scene(t_scene *scene)
{
	int	i;

	i = -1;
	free_all(*scene);
	if (scene->img_ptr)
	{
		while (++i < scene->nb_cam * FILTERS)
			mlx_destroy_image(scene->mlx, scene->img_ptr[i]);
		free(scene->img_ptr);
	}
	if (scene->img_data)
	{
		while (++i < scene->nb_cam * FILTERS)
			free(scene->img_data[i]);
		free(scene->img_data);
	}
	mlx_destroy_window(scene->mlx, scene->win);
	//mlx_destroy_display(scene->mlx);
	free(scene->mlx);
	exit(0);
	return (1);
}

static int	previous_camera_index(int i, t_scene scn)
{
	if (i < FILTERS)
		return (FILTERS * (scn.nb_cam - 1));
	else
		return (FILTERS * (i / FILTERS) - FILTERS);
}

static int	next_filter_index(int i)
{
	if ((i + 1) % FILTERS != 0)
		return (i + 1);
	else
		return (FILTERS * (i / FILTERS));
}

int			display(t_scene *scn)
{
	mlx_put_image_to_window(scn->mlx, scn->win, scn->img_ptr[0], 0, 0);
	(void)scn;
	return (1);
}

int			next_cam(int keynote, t_scene *scn)
{
	static int	i;

	if (keynote == ESC_KEY)
		return (exit_scene(scn));
	if (keynote == SP_KEY || keynote == W_KEY || keynote == RIGHT_KEY)
	{
		i = (FILTERS * (i / FILTERS) + FILTERS) % (FILTERS * scn->nb_cam);
		mlx_put_image_to_window(scn->mlx, scn->win, scn->img_ptr[i], 0, 0);
		put_legend(*scn);
	}
	else if (keynote == S_KEY || keynote == LEFT_KEY)
	{
		i = previous_camera_index(i, *scn);
		mlx_put_image_to_window(scn->mlx, scn->win, scn->img_ptr[i], 0, 0);
		put_legend(*scn);
	}
	else if (keynote == F_KEY)
	{
		i = next_filter_index(i);
		mlx_put_image_to_window(scn->mlx, scn->win, scn->img_ptr[i], 0, 0);
		put_legend(*scn);
	}
	return (1);
}
