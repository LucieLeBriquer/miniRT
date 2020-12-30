/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <lle-briq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 05:58:50 by lle-briq          #+#    #+#             */
/*   Updated: 2020/12/30 15:24:59 by lle-briq         ###   ########.fr       */
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
		printf("Error : Wrong number of arguments\n\tUse ./minirt scene.rt");
		printf(" or ./minirt scene.rt -save save_file\n");
	}
	else if (err == -3)
		printf("Error : %s\n", strerror(2));
	else if (err == -4)
		printf("Error : File is unreadable\n");
	else if (err == -5)
	{
		printf("Error : Wrong format\n");
		free_all(scene);
	}
	else if (err == -6)
	{
		printf("Error : Allocation's issues\n");
		free_all(scene);
	}
	exit(0);
	return (0);
}
