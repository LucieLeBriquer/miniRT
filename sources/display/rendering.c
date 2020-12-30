/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <lle-briq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 05:58:50 by lle-briq          #+#    #+#             */
/*   Updated: 2020/12/30 22:46:41 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	progress(int i, int j, t_scene scn, int n_cam)
{
	static int	prog;
	int			new;

	if (i == 0)
		prog = 0;
	new = 100 * ((i * scn.w + j) % (scn.h * scn.w)) / (scn.h * scn.w);
	if (new > prog)
	{
		prog = new;
		printf("\rRendering view %-2d [%3d%%]", n_cam, prog);
		fflush(stdout);
	}
}

t_vect	create_ray(int i, int j, t_scene scn, int n_cam)
{
	float	real_fov;
	float	img_ratio;
	t_vect	dir;

	real_fov = tan(scn.cams[n_cam].fov * M_PI / 360);
	img_ratio = (float)scn.w / (float)scn.h;
	dir.x = (1 - 2 * ((float)(j + 0.5) / (float)scn.w)) * img_ratio * real_fov;
	dir.y = (1 - 2 * ((float)(i + 0.5) / (float)scn.h)) * real_fov;
	dir.z = 1;
	normalize(&dir);
	return (dir);
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
	{
		j = -1;
		while (++j < scn.w)
		{
			itr.ray.dir = create_ray(i, j, scn, n_cam);
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
