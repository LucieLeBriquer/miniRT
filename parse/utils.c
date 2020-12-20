#include "miniRT.h"

int		ft_strcmp(const char *s1, const char *s2)
{
	int				i;
	unsigned char	*str1;
	unsigned char	*str2;

	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	i = 0;
	while (str1[i] && str2[i] && str1[i] == str2[i])
		i++;
	return (str1[i] - str2[i]);
}

int		is_save(char *s)
{
	if (ft_strcmp(s, "-save") == 0)
		return (1);
	return (0);
}

void	print_cam(t_cam *cam, int nb_cam)
{
	int	i;

	i = 0;
	while (i < nb_cam)
	{
		printf("Cam %d : %f,%f,%f\t%f,%f,%f\t%f\n", i, cam[i].pos.x, cam[i].pos.y,
		cam[i].pos.z, cam[i].axe.x, cam[i].axe.y, cam[i].axe.z, cam[i].fov);
		i++;
	}
}

void	print_lum(t_lum *lum, int nb_lum)
{
	int	i;

	i = 0;
	while (i < nb_lum)
	{
		printf("Lum %d : %f,%f,%f\t%f\t%d,%d,%d\n", i, lum[i].pos.x, lum[i].pos.y,
		lum[i].pos.z, lum[i].ratio, lum[i].col.r, lum[i].col.g, lum[i].col.b);
		i++;
	}
}

void	print_parsing(t_scene scene)
{
	printf("Resolution : %d %d\n", scene.w, scene.h);
	printf("Ambiante : %.10f %d,%d,%d\n", scene.amb, scene.amb_col.r,
	scene.amb_col.g, scene.amb_col.b);
	print_cam(scene.cams, scene.nb_cam);
	print_lum(scene.lums, scene.nb_lum);
}
