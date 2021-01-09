/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 15:28:41 by lle-briq          #+#    #+#             */
/*   Updated: 2021/01/09 23:43:46 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	black_white(int color)
{
	int	rgb[3];
	int	moy;

	rgb[0] = (color / 256 / 256);
	rgb[1] = ((color / 256) % 256);
	rgb[2] = (color % 256);
	moy = (rgb[0] + rgb[1] + rgb[2]) / 3;
	return (moy * 65793);
}

int	sepia(int color)
{
	int		rgb[3];
	double	sep[3];
	int		res[3];

	rgb[0] = (color / 256 / 256);
	rgb[1] = ((color / 256) % 256);
	rgb[2] = (color % 256);
	sep[0] = 0.393 * rgb[0] + 0.769 * rgb[1] + 0.189 * rgb[2];
	sep[1] = 0.349 * rgb[0] + 0.686 * rgb[1] + 0.168 * rgb[2];
	sep[2] = 0.272 * rgb[0] + 0.534 * rgb[1] + 0.131 * rgb[2];
	res[0] = fmin(255, fmax(floor(sep[0]), 0));
	res[1] = fmin(255, fmax(floor(sep[1]), 0));
	res[2] = fmin(255, fmax(floor(sep[2]), 0));
	return (256 * 256 * res[0] + 256 * res[1] + res[2]);
}

int	compo(int color, int i)
{
	if (i == 0)
		return (256 * 256 * (color / 256 / 256));
	if (i == 1)
		return (256 * ((color / 256) % 256));
	return (color % 256);
}
