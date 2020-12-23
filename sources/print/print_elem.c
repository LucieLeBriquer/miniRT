/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_elem.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <lle-briq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/20 16:26:57 by lle-briq          #+#    #+#             */
/*   Updated: 2020/12/21 05:34:15 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
