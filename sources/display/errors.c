/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <lle-briq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 05:58:50 by lle-briq          #+#    #+#             */
/*   Updated: 2021/01/03 16:08:02 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	free_all(t_scene scene)
{
	if (scene.cams)
		free(scene.cams);
	if (scene.lums)
		free(scene.lums);
	if (scene.objs)
		free(scene.objs);
}

int	print_errors_and_free(int err, t_scene scene)
{
	if (err == -2)
	{
		ft_printf("Error : Wrong number of arguments\n\tUse ./minirt scene.rt");
		ft_printf(" or ./minirt scene.rt -save save_file\n");
	}
	else if (err == -3)
		ft_printf("Error : %s\n", strerror(2));
	else if (err == -4)
		ft_printf("Error : File is unreadable\n");
	else if (err == -5)
	{
		ft_printf("Error : Wrong format\n");
		free_all(scene);
	}
	else if (err == -6)
	{
		ft_printf("Error : Allocation's issues\n");
		free_all(scene);
	}
	exit(0);
	return (0);
}
