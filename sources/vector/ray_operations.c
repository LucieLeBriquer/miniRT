/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_operations.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <lle-briq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 05:30:32 by lle-briq          #+#    #+#             */
/*   Updated: 2020/12/21 16:24:11 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	init_ray_dir(t_ray *ray, float x, float y, float z)
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
