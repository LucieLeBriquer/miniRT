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

static void	fill_str(char *str_cam)
{
	str_cam[0] = 'c';
	str_cam[1] = 'a';
	str_cam[2] = 'm';
	str_cam[3] = ' ';
}

static char	*create_str_cam(t_scene scene, int *s)
{
	char	*str_cam;
	int		size;
	int		cam;
	int		i;

	size = 0;
	cam = scene.cam / FILTERS;
	if (cam == 0)
		size = 1;
	while (cam > 0 && size++)
		cam = cam / 10;
	str_cam = ft_calloc(size + 5, sizeof(char));
	if (!str_cam)
		return (NULL);
	cam = scene.cam / FILTERS;
	i = -1;
	while (++i < size)
	{
		str_cam[size + 3 - i] = (cam % 10) + '0';
		cam = cam / 10;
	}
	fill_str(str_cam);
	*s = size + 5;
	return (str_cam);
}

void		put_legend(t_scene scene)
{
	int		col;
	char	*str_cam;
	int		size;

	col = 0xffffff - scene.img_data[0][0];
	mlx_string_put(scene.mlx, scene.win, 5, 15, col, "<- -> to switch camera");
	mlx_string_put(scene.mlx, scene.win, 5, 30, col, "f to change filter");
	mlx_string_put(scene.mlx, scene.win, 5, 45, col, "ESC to quit");
	str_cam = create_str_cam(scene, &size);
	if (str_cam)
	{
		mlx_string_put(scene.mlx, scene.win, scene.w - (size + 1) * 5, 15,
			col, str_cam);
		free(str_cam);
	}
}
