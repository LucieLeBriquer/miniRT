/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 15:57:09 by lle-briq          #+#    #+#             */
/*   Updated: 2021/01/11 15:57:17 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	parse_trg(t_scene *scene, char *line, int *nb)
{
	t_obj	trg;

	while (ft_isspace(*line))
		line++;
	if (to_vect(line, &(trg.o)) == -1)
		return (-1);
	line += skip_vect(line);
	if (to_vect(line, &(trg.q)) == -1)
		return (-1);
	line += skip_vect(line);
	if (to_vect(line, &(trg.p)) == -1)
		return (-1);
	line += skip_vect(line);
	if (to_col(line, &(trg.col)) == -1)
		return (-1);
	trg.type = TRIANGLE;
	trg.axe = prod_vect(sub_vect(trg.q, trg.o), sub_vect(trg.p, trg.o));
	normalize(&(trg.axe));
	(scene->objs)[*nb] = trg;
	*nb += 1;
	return (1);
}
