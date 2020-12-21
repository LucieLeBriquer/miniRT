/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <lle-briq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/20 16:26:57 by lle-briq          #+#    #+#             */
/*   Updated: 2020/12/21 03:00:38 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#define cyan "\033[36m"
#define white "\033[0m"

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

void	print_vect(t_vect vect)
{
	printf("\t%5.3f,%5.3f,%5.3f", vect.x, vect.y, vect.z);
}

void	print_float(float f)
{
	printf("\t%5.3f", f);
}

void	print_col(t_col col)
{
	printf("\t%d,%d,%d", col.r, col.g, col.b);
}

void	newline(void)
{
	printf("\n");
}

void	newtab(void)
{
	printf("\t");
}

void	print_cam(t_cam *cam, int nb_cam)
{
	int	i;

	i = 0;
	while (i < nb_cam)
	{
		printf("Cam %3d :", i);
		print_vect(cam[i].pos);
		print_vect(cam[i].axe);
		print_float(cam[i].fov);
		newline();
		i++;
	}
}

void	print_lum(t_lum *lum, int nb_lum)
{
	int	i;

	i = 0;
	while (i < nb_lum)
	{
		printf("Lum %3d :", i);
		print_vect(lum[i].pos);
		print_float(lum[i].ratio);
		print_col(lum[i].col);
		i++;
	}
}

void	print_sph(t_obj sph, int i)
{
	printf("[%02d]sph :", i);
	print_vect(sph.o);
	print_col(sph.col);
	print_float(sph.r);
	newline();
}

void	print_pln(t_obj pln, int i)
{
	printf("[%02d]pln :", i);
	print_vect(pln.o);
	print_vect(pln.axe);
	print_col(pln.col);
	newline();
}

void	print_sqr(t_obj sqr, int i)
{
	printf("[%02d]sqr :", i);
	print_vect(sqr.o);
	print_vect(sqr.axe);
	print_float(sqr.h); 
	print_col(sqr.col);
	newline();
}

void	print_cyl(t_obj cyl, int i)
{
	printf("[%02d]cyl :", i);
	print_vect(cyl.o);
	print_vect(cyl.axe);
	print_float(cyl.r); 
	print_col(cyl.col);
	newline();
}

void	print_trg(t_obj trg, int i)
{
	printf("[%02d]trg :", i);
	print_vect(trg.o);
	print_vect(trg.axe);
	newline();
	newtab();
	print_vect(trg.p);
	print_col(trg.col);
	newline();
}

void	print_obj(t_obj *obj, int nb_obj)
{
	int	i;

	i = 0;
	while (i < nb_obj)
	{
		if (obj[i].type == 0)
			print_sph(obj[i], i);
		else if (obj[i].type == 1)
			print_pln(obj[i], i);
		else if (obj[i].type == 2)
			print_sqr(obj[i], i);
		else if (obj[i].type == 3)
			print_cyl(obj[i], i);
		else if (obj[i].type == 4)
			print_trg(obj[i], i);
		i++;
	}
}

void	print_parsing(t_scene scene)
{
	printf("%s[configuration]%s\n", cyan, white);
	printf("Resolution :\t%d %d\n", scene.w, scene.h);
	printf("Ambiance   :\t%4.3f %d,%d,%d\n", scene.amb, scene.amb_col.r,
			scene.amb_col.g, scene.amb_col.b);
	printf("\n%s>> %d cams%s\n", cyan, scene.nb_cam, white);
	print_cam(scene.cams, scene.nb_cam);
	printf("\n%s>> %d lums%s\n", cyan, scene.nb_lum, white);
	print_lum(scene.lums, scene.nb_lum);
	printf("\n\n%s>> %d objs%s\n", cyan, scene.nb_obj, white);
	print_obj(scene.objs, scene.nb_obj);
}
