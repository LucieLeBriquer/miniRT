/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <lle-briq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/20 16:26:21 by lle-briq          #+#    #+#             */
/*   Updated: 2020/12/20 16:26:22 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int		skip_float(char *line)
{
	int	i;

	i = 0;
	if (line[i] == '-')
		i++;
	while (ft_isdigit(line[i]))
		i++;
	if (line[i] == '.')
		i++;
	while (ft_isdigit(line[i]))
		i++;
	while (ft_isspace(line[i]))
		i++;
	return (i);
}

int		skip_float_ns(char *line)
{
	int	i;

	i = 0;
	if (line[i] == '-')
		i++;
	while (ft_isdigit(line[i]))
		i++;
	if (line[i] == '.')
		i++;
	while (ft_isdigit(line[i]))
		i++;
	return (i);
}

int		skip_vect(char *line)
{
	int	i;

	i = skip_float_ns(line);
	i++;
	i += skip_float_ns(line + i);
	i++;
	i += skip_float_ns(line + i);
	while (ft_isspace(line[i]))
		i++;
	return (i);
}
