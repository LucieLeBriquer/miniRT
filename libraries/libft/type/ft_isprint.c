/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <lle-briq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 10:20:56 by lle-briq          #+#    #+#             */
/*   Updated: 2020/12/30 14:37:46 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftfull.h"

int	ft_isprint(int c)
{
	return (c >= 32 && c < 127);
}
