/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <lle-briq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/20 16:26:57 by lle-briq          #+#    #+#             */
/*   Updated: 2021/01/11 13:04:53 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	print_cam(t_cam *cam, int nb_cam)
{
	int	i;

	i = 0;
	while (i < nb_cam)
	{
		printf("Cam %3d :", i);
		print_vect(cam[i].pos);
		print_vect(cam[i].axe);
		print_double(cam[i].fov);
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
		print_double(lum[i].ratio);
		print_col(lum[i].col);
		newline();
		i++;
	}
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
		else if (obj[i].type == 2 || obj[i].type == 6)
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
	printf("%s[configuration]%s\n", CYAN, WHITE);
	printf("Resolution :\t%d %d\n", scene.w, scene.h);
	printf("Ambiance   :\t%4.3f %d,%d,%d\n", scene.amb, scene.amb_col.r,
			scene.amb_col.g, scene.amb_col.b);
	printf("\n%s>> %d cams%s\n", CYAN, scene.nb_cam, WHITE);
	print_cam(scene.cams, scene.nb_cam);
	printf("\n%s>> %d lums%s\n", CYAN, scene.nb_lum, WHITE);
	print_lum(scene.lums, scene.nb_lum);
	printf("\n\n%s>> %d objs%s\n", CYAN, scene.nb_obj, WHITE);
	print_obj(scene.objs, scene.nb_obj);
}
