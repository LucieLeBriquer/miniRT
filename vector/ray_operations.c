#include "miniRT.h"

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
