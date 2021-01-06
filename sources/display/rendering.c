/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <lle-briq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 05:58:50 by lle-briq          #+#    #+#             */
/*   Updated: 2021/01/06 18:05:18 by lle-briq         ###   ########.fr       */
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
		ft_printf("\rRendering view %-2d [%3d%%]", n_cam, prog);
		fflush(stdout);
	}
}

t_vect	create_ray(int i, int j, t_scene scn, int n_cam)
{
	double	real_fov;
	double	img_ratio;
	t_vect	dir;

	real_fov = tan(scn.cams[n_cam].fov * M_PI / 360);
	img_ratio = (double)scn.w / (double)scn.h;
	dir.x = (2 * ((double)(j + 0.5) / (double)scn.w) - 1) * img_ratio * real_fov;
	dir.y = (1 - 2 * ((double)(i + 0.5) / (double)scn.h)) * real_fov;
	dir.z = -1;
	normalize(&dir);
	return (dir);
}

void	draw(t_scene scn, int n_cam)
{
	t_inter	itr[4];
	t_base	base;
	int		i;
	int		j;

	i = -1;
	init_ray_org(&(itr[0].ray), scn.cams[n_cam].pos);
	init_ray_org(&(itr[1].ray), scn.cams[n_cam].pos);
	init_ray_org(&(itr[2].ray), scn.cams[n_cam].pos);
	init_ray_org(&(itr[3].ray), scn.cams[n_cam].pos);
	init_base(&base, scn.cams[n_cam].axe);
	while (++i < scn.h)
	{
		j = -1;
		while (++j < scn.w)
		{
			itr[0].ray.dir = create_ray(i - 0.25, j - 0.25, scn, n_cam);
			itr[1].ray.dir = create_ray(i - 0.25, j + 0.25, scn, n_cam);
			itr[2].ray.dir = create_ray(i + 0.25, j - 0.25, scn, n_cam);
			itr[3].ray.dir = create_ray(i + 0.25, j + 0.25, scn, n_cam);
			rotate(&(itr[0].ray.dir), base);
			rotate(&(itr[1].ray.dir), base);
			rotate(&(itr[2].ray.dir), base);
			rotate(&(itr[3].ray.dir), base);
			(scn.img_data[n_cam])[i * scn.w + j] = average_color(itr, scn);
			progress(i, j, scn, n_cam);
		}
	}
}

void	draw_noantialiasing(t_scene scn, int n_cam)
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
		ft_printf("\rRendering view %-2d [100%%]\n", i);
	}
}
