/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <lle-briq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/20 16:22:39 by lle-briq          #+#    #+#             */
/*   Updated: 2021/01/11 12:57:26 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	parse_res(t_scene *scene, char *line)
{
	int		width;
	int		height;

	line++;
	while (ft_isspace(*line))
		line++;
	width = ft_atoi(line);
	if (width <= 0)
		return (-1);
	scene->w = width;
	while (ft_isdigit(*line))
		line++;
	while (ft_isspace(*line))
		line++;
	height = ft_atoi(line);
	if (height <= 0)
		return (-1);
	scene->h = height;
	return (1);
}

int	parse_amb(t_scene *scene, char *line)
{
	double	amb;
	t_col	col;

	while (ft_isspace(*line))
		line++;
	if (to_double(line, &amb) < 0 || amb < 0 || amb > 1)
		return (-1);
	scene->amb = amb;
	line += skip_double(line);
	if (to_col(line, &col) == -1)
		return (-1);
	while (ft_isdigit(*line) || *line == ',')
		line++;
	scene->amb_col = col;
	return (1);
}

int	parse_cam(t_scene *scene, char *line)
{
	static int	nb;
	t_cam		cam;

	while (ft_isspace(*line))
		line++;
	if (to_vect(line, &(cam.pos)) == -1)
		return (-1);
	line += skip_vect(line);
	if (to_vect_range(line, &(cam.axe)) == -1)
		return (-1);
	normalize_and_reverse(&(cam.axe));
	line += skip_vect(line);
	cam.fov = ft_atoi(line);
	if (cam.fov < 0 || cam.fov > 180)
		return (-1);
	(scene->cams)[nb] = cam;
	nb++;
	return (1);
}

int	parse_lum(t_scene *scene, char *line)
{
	static int	nb;
	t_lum		lum;

	while (ft_isspace(*line))
		line++;
	if (to_vect(line, &(lum.pos)) == -1)
		return (-1);
	line += skip_vect(line);
	if (to_double(line, &(lum.ratio)) == -1 || lum.ratio < 0 || lum.ratio > 1)
		return (-1);
	line += skip_double(line);
	if (to_col(line, &(lum.col)) == -1)
		return (-1);
	(scene->lums)[nb] = lum;
	nb++;
	return (1);
}

int	parse_obj(t_scene *scene, char *line)
{
	static int	nb;

	nb++;
	if (line[0] == 's' && line[1] == 'p')
		return (parse_sph(scene, line + 2, nb));
	if (line[0] == 'p' && line[1] == 'l')
		return (parse_pln(scene, line + 2, nb));
	if (line[0] == 's' && line[1] == 'q')
		return (parse_sqr(scene, line + 2, nb));
	if (line[0] == 'c' && line[1] == 'y')
		return (parse_cyl(scene, line + 2, nb));
	if (line[0] == 't' && line[1] == 'r')
		return (parse_trg(scene, line + 2, nb));
	if (line[0] == 'c' && line[1] == 'o')
		return (parse_con(scene, line + 2, nb));
	if (line[0] == 'c' && line[1] == 'i')
		return (parse_cir(scene, line + 2, nb));
	return (-1);
}
