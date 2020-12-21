/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <lle-briq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/20 16:26:39 by lle-briq          #+#    #+#             */
/*   Updated: 2020/12/21 17:09:48 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int		parse_sph(t_scene *scene, char *line, int nb)
{
	t_obj	sph;

	while (ft_isspace(*line))
		line++;
	if (to_vect(line, &(sph.o)) == -1)
		return (-1);
	line += skip_vect(line);
	if (to_float(line, &(sph.r)) == -1)
		return (-1);
	line += skip_float(line);
	if (to_col(line, &(sph.col)) == -1)
		return (-1);
	sph.type = 0;
	sph.r = sph.r / 2;
	(scene->objs)[nb - 1] = sph;
	return (1);
}

int		parse_pln(t_scene *scene, char *line, int nb)
{
	t_obj	pln;

	while (ft_isspace(*line))
		line++;
	if (to_vect(line, &(pln.o)) == -1)
		return (-1);
	line += skip_vect(line);
	if (to_vect(line, &(pln.axe)) == -1)
		return (-1);
	line += skip_vect(line);
	if (to_col(line, &(pln.col)) == -1)
		return (-1);
	pln.type = 1;
	(scene->objs)[nb - 1] = pln;
	return (1);
}

int		parse_sqr(t_scene *scene, char *line, int nb)
{
	t_obj	sqr;

	while (ft_isspace(*line))
		line++;
	if (to_vect(line, &(sqr.o)) == -1)
		return (-1);
	line += skip_vect(line);
	if (to_vect(line, &(sqr.axe)) == -1)
		return (-1);
	line += skip_vect(line);
	if (to_float(line, &(sqr.h)) == -1)
		return (-1);
	line += skip_float(line);
	if (to_col(line, &(sqr.col)) == -1)
		return (-1);
	sqr.type = 2;
	(scene->objs)[nb - 1] = sqr;
	return (1);
}

int		parse_cyl(t_scene *scene, char *line, int nb)
{
	t_obj	cyl;

	while (ft_isspace(*line))
		line++;
	if (to_vect(line, &(cyl.o)) == -1)
		return (-1);
	line += skip_vect(line);
	if (to_vect(line, &(cyl.axe)) == -1)
		return (-1);
	line += skip_vect(line);
	if (to_float(line, &(cyl.r)) == -1)
		return (-1);
	line += skip_float(line);
	if (to_float(line, &(cyl.h)) == -1)
		return (-1);
	line += skip_float(line);
	if (to_col(line, &(cyl.col)) == -1)
		return (-1);
	cyl.type = 3;
	(scene->objs)[nb - 1] = cyl;
	return (1);
}

int		parse_trg(t_scene *scene, char *line, int nb)
{
	t_obj	trg;

	while (ft_isspace(*line))
		line++;
	if (to_vect(line, &(trg.o)) == -1)
		return (-1);
	line += skip_vect(line);
	if (to_vect(line, &(trg.axe)) == -1)
		return (-1);
	line += skip_vect(line);
	if (to_vect(line, &(trg.p)) == -1)
		return (-1);
	line += skip_vect(line);
	if (to_col(line, &(trg.col)) == -1)
		return (-1);
	trg.type = 4;
	(scene->objs)[nb - 1] = trg;
	return (1);
}
