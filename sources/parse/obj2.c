/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <lle-briq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/20 16:26:39 by lle-briq          #+#    #+#             */
/*   Updated: 2021/01/07 14:38:24 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	parse_con(t_scene *scene, char *line, int nb)
{
	t_obj	con;

	while (ft_isspace(*line))
		line++;
	if (to_vect(line, &(con.o)) == -1)
		return (-1);
	line += skip_vect(line);
	if (to_vect_range(line, &(con.axe)) == -1)
		return (-1);
	line += skip_vect(line);
	if (to_double(line, &(con.r)) == -1)
		return (-1);
	con.r = con.r / 2;
	line += skip_double(line);
	if (to_double(line, &(con.h)) == -1)
		return (-1);
	line += skip_double(line);
	if (to_col(line, &(con.col)) == -1)
		return (-1);
	con.type = CONE;
	(scene->objs)[nb - 1] = con;
	return (1);
}
