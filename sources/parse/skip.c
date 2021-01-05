/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <lle-briq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/20 16:26:21 by lle-briq          #+#    #+#             */
/*   Updated: 2020/12/30 15:27:41 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	skip_double(char *line)
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

int	skip_double_ns(char *line)
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

int	skip_vect(char *line)
{
	int	i;

	i = skip_double_ns(line);
	i++;
	i += skip_double_ns(line + i);
	i++;
	i += skip_double_ns(line + i);
	while (ft_isspace(line[i]))
		i++;
	return (i);
}
