/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_4int.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <lle-briq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 21:51:09 by lle-briq          #+#    #+#             */
/*   Updated: 2020/12/30 15:08:06 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftfull.h"

int	print_4int(t_print param, va_list args)
{
	int		nb;
	int		size;
	char	*nb_itoa;
	char	*to_print;

	nb = va_arg(args, int);
	nb_itoa = ft_itoa(nb);
	if (nb == 0 && param.precision == 0)
		nb_itoa[0] = '\0';
	size = size_int(param, nb_itoa);
	to_print = malloc(size * sizeof(char));
	if (!to_print)
		return (0);
	fill_int(&to_print, nb_itoa, param, size);
	free(nb_itoa);
	ft_putstr(to_print);
	free(to_print);
	return (size - 1);
}
