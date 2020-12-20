/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <lle-briq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/20 16:26:57 by lle-briq          #+#    #+#             */
/*   Updated: 2020/12/20 16:26:58 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		printf("Cam %d  : %f,%f,%f\t%f,%f,%f\t%f\n", i, cam[i].pos.x, cam[i].pos.y,
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
		printf("Lum %d  : %f,%f,%f\t%f\t%d,%d,%d\n", i, lum[i].pos.x, lum[i].pos.y,
		lum[i].pos.z, lum[i].ratio, lum[i].col.r, lum[i].col.g, lum[i].col.b);
		i++;
	}
}

void	print_sph(t_obj2 sph, int i)
{
		printf("[%d]sph : %f,%f,%f\t\t%d,%d,%d\t%f\n", i, sph.o.x,
		sph.o.y, sph.o.z, sph.col.r, sph.col.g, sph.col.b, sph.r);
}

void	print_pln(t_obj2 pln, int i)
{
		printf("[%d]pln : %f,%f,%f\t%f,%f,%f\t%d,%d,%d\n", i, pln.o.x,
		pln.o.y, pln.o.z, pln.axe.x, pln.axe.y, pln.axe.z, pln.col.r, pln.col.g,
		pln.col.b);
}

void	print_sqr(t_obj2 sqr, int i)
{
		printf("[%d]sqr : %f,%f,%f\t%f,%f,%f\t%f\t%d,%d,%d\n", i, sqr.o.x,
		sqr.o.y, sqr.o.z, sqr.axe.x, sqr.axe.y, sqr.axe.z, sqr.h, sqr.col.r, sqr.col.g,
		sqr.col.b);
}

void	print_cyl(t_obj2 cyl, int i)
{
		printf("[%d]cyl : %f,%f,%f\t%f,%f,%f\t%f  %f\t%d,%d,%d\n", i, cyl.o.x,
		cyl.o.y, cyl.o.z, cyl.axe.x, cyl.axe.y, cyl.axe.z, cyl.h, cyl.r,
		cyl.col.r, cyl.col.g, cyl.col.b);
}

void	print_trg(t_obj2 trg, int i)
{
		printf("[%d]trg : %f,%f,%f\t%f,%f,%f\t%f,%f,%f\t%d,%d,%d\n", i, trg.o.x,
		trg.o.y, trg.o.z, trg.axe.x, trg.axe.y, trg.axe.z, trg.p.x, trg.p.y,
		trg.p.z, trg.col.r, trg.col.g, trg.col.b);
}

void	print_obj(t_obj2 *obj, int nb_obj)
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
	printf("Resol. : %d %d\n", scene.w, scene.h);
	printf("Ambia. : %.10f %d,%d,%d\n", scene.amb, scene.amb_col.r,
	scene.amb_col.g, scene.amb_col.b);
	printf("----  %d cam  ----\n", scene.nb_cam);
	print_cam(scene.cams, scene.nb_cam);
	printf("----  %d lum  ----\n", scene.nb_lum);
	print_lum(scene.lums, scene.nb_lum);
	printf("----  %d objs ----\n", scene.nb_obj);
	print_obj(scene.objs, scene.nb_obj);
}
