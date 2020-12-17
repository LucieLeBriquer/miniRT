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

void	print_parsing(t_scene scene)
{
	printf("Resolution : %d %d\n", scene.W, scene.H);
	printf("Ambiante : %.10f %d,%d,%d\n", scene.amb, scene.amb_col.r,
	scene.amb_col.g, scene.amb_col.b);
}
