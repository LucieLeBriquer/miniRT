/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <lle-briq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 05:58:50 by lle-briq          #+#    #+#             */
/*   Updated: 2020/12/26 14:26:35 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	progress(int i, int j, t_scene scn, int n_cam)
{
	static int	prog = 0;
	int			new;
	
	new = 100 * ((i * scn.w + j) % (scn.h * scn.w)) / (scn.h * scn.w);
	if (new > prog)
	{	
		prog = new;
		printf("\rRendering view %-2d [%3d%%]", n_cam, prog);
		fflush(stdout);
	}
}

void	draw(t_scene scn, int n_cam)
{
	t_inter	itr;
	t_base	base;
	int		i;
	int		j;

	i = -1;
	init_ray_org(&(itr.ray), scn.cams[n_cam].pos);
	init_base(&base, scn.cams[n_cam].axe);
	while (++i < scn.h)
	{z&<
		j = -1;
		while (++j < scn.w)
		{
			init_ray_dir(&(itr.ray), j - scn.w / 2, -i + scn.h / 2,
			(fmax(scn.w, scn.h) / (2 * tan(scn.cams[n_cam].fov * M_PI / 360))));
			rotate(&(itr.ray.dir), base);
			(scn.img_data[n_cam])[i * scn.w + j] = get_color(&itr, scn);
			progress(i, j, scn, n_cam);
		}
	}
}

void	render(t_scene scn)
{
	int	i;

	i = -1;
	while (++i < scn.nb_cam)
	{
		draw(scn, i);
		printf("\rRendering view %-2d [100%%]\n", i);
	}
	mlx_put_image_to_window(scn.mlx, scn.win, scn.img_ptr[0], 0, 0);
}
