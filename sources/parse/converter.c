/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   converter.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <lle-briq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/20 16:22:00 by lle-briq          #+#    #+#             */
/*   Updated: 2021/01/10 21:38:38 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	size_of_int(int i)
{
	int	size;

	size = 0;
	if (i == 0)
		return (1);
	while (i > 0)
	{
		i = i / 10;
		size++;
	}
	return (size);
}

int	to_double(char *line, double *f)
{
	int		entiere;
	int		floating;
	int		sign;
	int		size;

	floating = 0;
	entiere = ft_atoi(line);
	sign = 1;
	if (*line == '-' && line++)
		sign = -1;
	while (ft_isdigit(*line))
		line++;
	if (*line == '.' && line++)
		floating = ft_atoi(line);
	size = size_of_int(floating);
	while (*line == '0' && line++)
		size++;
	if (floating < 0)
		return (-1);
	*f = entiere + sign * (double)(floating) * pow(0.1, size);
	return (1);
}

int	to_col(char *line, t_col *col)
{
	int		c;

	c = ft_atoi(line);
	if (c < 0 || c > 255)
		return (-1);
	col->r = c;
	while (ft_isdigit(*line))
		line++;
	if (*line != ',')
		return (-1);
	line++;
	c = ft_atoi(line);
	if (c < 0 || c > 255)
		return (-1);
	col->g = c;
	while (ft_isdigit(*line))
		line++;
	if (*line != ',')
		return (-1);
	line++;
	c = ft_atoi(line);
	if (c < 0 || c > 255)
		return (-1);
	col->b = c;
	return (1);
}

int	to_vect(char *line, t_vect *vect)
{
	double	c;

	if (to_double(line, &c) < 0)
		return (-1);
	line += skip_double(line);
	if (*line != ',')
		return (-1);
	vect->x = c;
	line++;
	if (to_double(line, &c) < 0)
		return (-1);
	line += skip_double(line);
	if (*line != ',')
		return (-1);
	vect->y = c;
	line++;
	if (to_double(line, &c) < 0)
		return (-1);
	vect->z = c;
	return (1);
}

int	to_vect_range(char *line, t_vect *vect)
{
	double	c;

	if (to_double(line, &c) < 0 || c < -1 || c > 1)
		return (-1);
	line += skip_double(line);
	if (*line != ',')
		return (-1);
	vect->x = c;
	line++;
	if (to_double(line, &c) < 0 || c < -1 || c > 1)
		return (-1);
	line += skip_double(line);
	if (*line != ',')
		return (-1);
	vect->y = c;
	line++;
	if (to_double(line, &c) < 0 || c < -1 || c > 1)
		return (-1);
	vect->z = c;
	normalize(vect);
	return (1);
}
