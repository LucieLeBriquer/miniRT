/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <lle-briq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 05:58:50 by lle-briq          #+#    #+#             */
/*   Updated: 2021/01/09 21:49:49 by lle-briq         ###   ########.fr       */
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
	double	step;

	step = 0.25;
	itr[0].ray.dir = create_ray(p[0] - step, p[1] - step, scn, p[2]);
	itr[1].ray.dir = create_ray(p[0] - step, p[1] + step, scn, p[2]);
	itr[2].ray.dir = create_ray(p[0] + step, p[1] - step, scn, p[2]);
	itr[3].ray.dir = create_ray(p[0] + step, p[1] + step, scn, p[2]);
	rotate(&(itr[0].ray.dir), base);
	rotate(&(itr[1].ray.dir), base);
	rotate(&(itr[2].ray.dir), base);
	rotate(&(itr[3].ray.dir), base);
}

static void	draw(t_scene scn, int n_cam)
{
	t_inter	itr[4];
	t_base	base;
	int		p[3];
	int		color;

	p[0] = -1;
	p[2] = n_cam / FILTERS;
	init_rays_org(itr, scn.cams[p[2]].pos);
	init_base(&base, scn.cams[p[2]].axe);
	while (++p[0] < scn.h)
	{
		p[1] = -1;
		while (++p[1] < scn.w)
		{
			create_rays(itr, base, scn, p);
			color = average_color(itr, scn);
			(scn.img_data[n_cam])[p[0] * scn.w + p[1]] = color;
			(scn.img_data[n_cam + 1])[p[0] * scn.w + p[1]] = black_white(color);
			(scn.img_data[n_cam + 2])[p[0] * scn.w + p[1]] = sepia(color);
			(scn.img_data[n_cam + 3])[p[0] * scn.w + p[1]] = compo(color, 0);
			(scn.img_data[n_cam + 4])[p[0] * scn.w + p[1]] = compo(color, 1);
			(scn.img_data[n_cam + 5])[p[0] * scn.w + p[1]] = compo(color, 2);
			progress(p[0], p[1], scn, n_cam);
		}
	}
}

static void	draw_aliasing(t_scene scn, int n_cam)
{
	t_inter	itr;
	t_base	base;
	int		i;
	int		j;
	int		color;

	i = -1;
	init_ray_org(&(itr.ray), scn.cams[n_cam / FILTERS].pos);
	init_base(&base, scn.cams[n_cam / FILTERS].axe);
	while (++i < scn.h)
	{
		j = -1;
		while (++j < scn.w)
		{
			itr.ray.dir = create_ray(i, j, scn, n_cam / FILTERS);
			rotate(&(itr.ray.dir), base);
			color = get_color(&itr, scn);
			(scn.img_data[n_cam])[i * scn.w + j] = color;
			(scn.img_data[n_cam + 1])[i * scn.w + j] = black_white(color);
			(scn.img_data[n_cam + 2])[i * scn.w + j] = sepia(color);
			(scn.img_data[n_cam + 3])[i * scn.w + j] = compo(color, 0);
			(scn.img_data[n_cam + 4])[i * scn.w + j] = compo(color, 1);
			(scn.img_data[n_cam + 5])[i * scn.w + j] = compo(color, 2);
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
		if (aliasing == 1)
			draw_aliasing(scn, i * FILTERS);
		else
			draw(scn, i * FILTERS);
		progress_final(scn, i);
	}
}
