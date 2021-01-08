/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <lle-briq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 05:58:50 by lle-briq          #+#    #+#             */
/*   Updated: 2021/01/08 13:18:25 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_vect	create_ray(int i, int j, t_scene scn, int n_cam)
{
	double	real_fov;
	double	img_ratio;
	t_vect	dir;

	real_fov = tan(scn.cams[n_cam].fov * M_PI / 360);
	img_ratio = (double)scn.w / (double)scn.h;
	dir.x = (2 * ((double)(j + 0.5) / (double)scn.w) - 1) * img_ratio
		* real_fov;
	dir.y = (1 - 2 * ((double)(i + 0.5) / (double)scn.h)) * real_fov;
	dir.z = -1;
	normalize(&dir);
	return (dir);
}

static void	create_rays(t_inter itr[4], t_base base, t_scene scn, int p[3])
{
	itr[0].ray.dir = create_ray(p[0] - 0.25, p[1] - 0.25, scn, p[2]);
	itr[1].ray.dir = create_ray(p[0] - 0.25, p[1] + 0.25, scn, p[2]);
	itr[2].ray.dir = create_ray(p[0] + 0.25, p[1] - 0.25, scn, p[2]);
	itr[3].ray.dir = create_ray(p[0] + 0.25, p[1] + 0.25, scn, p[2]);
	rotate(&(itr[0].ray.dir), base);
	rotate(&(itr[1].ray.dir), base);
	rotate(&(itr[2].ray.dir), base);
	rotate(&(itr[3].ray.dir), base);
}

static void	draw(t_scene scn, int n_cam)
{
	t_inter	itr[4];
	t_base	base;
	int		param[3];

	param[0] = -1;
	param[2] = n_cam;
	init_rays_org(itr, scn.cams[n_cam].pos);
	init_base(&base, scn.cams[n_cam].axe);
	while (++param[0] < scn.h)
	{
		param[1] = -1;
		while (++param[1] < scn.w)
		{
			create_rays(itr, base, scn, param);
			(scn.img_data[n_cam])[param[0] * scn.w + param[1]]
				= average_color(itr, scn);
			progress(param[0], param[1], scn, n_cam);
		}
	}
}

static void	draw_aliasing(t_scene scn, int n_cam)
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

void	render(t_scene scn, int aliasing)
{
	int	i;

	i = -1;
	while (++i < scn.nb_cam)
	{
		if (aliasing == 0)
			draw_aliasing(scn, i);
		else
			draw(scn, i);
		progress_final(scn, i);
	}
}
