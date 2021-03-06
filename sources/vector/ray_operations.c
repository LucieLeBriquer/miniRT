/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_operations.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <lle-briq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 05:30:32 by lle-briq          #+#    #+#             */
/*   Updated: 2021/01/07 15:42:02 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	init_ray_dir(t_ray *ray, double x, double y, double z)
{
	ray->dir.x = x;
	ray->dir.y = y;
	ray->dir.z = z;
	normalize(&(ray->dir));
}

void	init_ray_org(t_ray *ray, t_vect org)
{
	ray->org.x = org.x;
	ray->org.y = org.y;
	ray->org.z = org.z;
}

void	init_ray(t_ray *ray, t_vect org, t_vect dir)
{
	ray->org.x = org.x;
	ray->org.y = org.y;
	ray->org.z = org.z;
	ray->dir.x = dir.x;
	ray->dir.y = dir.y;
	ray->dir.z = dir.z;
	normalize(&(ray->dir));
}

void	init_rays_org(t_inter itr[4], t_vect org)
{
	init_ray_org(&(itr[0].ray), org);
	init_ray_org(&(itr[1].ray), org);
	init_ray_org(&(itr[2].ray), org);
	init_ray_org(&(itr[3].ray), org);
}
