/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <lle-briq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 05:58:50 by lle-briq          #+#    #+#             */
/*   Updated: 2020/12/22 23:30:59 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int		exit_scene(t_scene *scene)
{
	free(scene->lums);
	free(scene->cams);
	free(scene->objs);
	mlx_clear_window(scene->mlx, scene->win);
	mlx_destroy_window(scene->mlx, scene->win);
	exit(0);
	return (1);
}

int		next_cam(int keynote, t_scene *scn)
{
	static int	i;

	if (keynote == ESC_KEY)
		return (exit_scene(scn));
	if (keynote != SP_KEY)
		return (-1);
	i = (i + 1) % scn->nb_cam;
	mlx_put_image_to_window(scn->mlx, scn->win, scn->img_ptr[i], 0, 0);
	return (1);
}
