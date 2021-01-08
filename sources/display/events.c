/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <lle-briq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 05:58:50 by lle-briq          #+#    #+#             */
/*   Updated: 2021/01/08 16:12:50 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	exit_scene(t_scene *scene)
{
	int	i;

	i = -1;
	free_all(*scene);
	if (scene->img_ptr)
	{
		while (++i < scene->nb_cam)
			mlx_destroy_image(scene->mlx, scene->img_ptr[i]);
		free(scene->img_ptr);
	}
	if (scene->img_data)
		free(scene->img_data);
	mlx_destroy_window(scene->mlx, scene->win);
	exit(0);
	return (1);
}

int	next_cam(int keynote, t_scene *scn)
{
	static int	i;

	if (keynote == ESC_KEY)
		return (exit_scene(scn));
	if (keynote == SP_KEY || keynote == W_KEY || keynote == RIGHT_KEY)
	{
		i = ((i / FILTERS) * FILTERS + FILTERS) % (FILTERS * scn->nb_cam);
		mlx_put_image_to_window(scn->mlx, scn->win, scn->img_ptr[i], 0, 0);
	}
	else if (keynote == S_KEY || keynote == LEFT_KEY)
	{
		if (i == 0)
			i = FILTERS * scn->nb_cam - FILTERS;
		else
			i = i - FILTERS;
		mlx_put_image_to_window(scn->mlx, scn->win, scn->img_ptr[i], 0, 0);
	}
	else if (keynote == F_KEY)
	{
		if ((i + 1) % FILTERS != 0)
			i = i + 1;
		else
			i = (i / FILTERS) * FILTERS;
		mlx_put_image_to_window(scn->mlx, scn->win, scn->img_ptr[i], 0, 0);
	}
	return (1);
}
