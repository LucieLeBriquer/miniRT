/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   progress.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <lle-briq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 05:58:50 by lle-briq          #+#    #+#             */
/*   Updated: 2021/01/11 21:33:45 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	progress(int i, int j, t_scene scn, int n_cam)
{
	static int	prog;
	int			new;

	if (i == 0)
		prog = 0;
	new = 100 * ((i * scn.w + j) % (scn.h * scn.w)) / (scn.h * scn.w);
	if (new > prog)
	{
		prog = new;
		if (scn.save)
			ft_printf("\rRendering view %2d/%-2d", n_cam + 1, 1);
		else
			ft_printf("\rRendering view %2d/%-2d", n_cam + 1, scn.nb_cam);
		ft_printf(" [%3d%%]", prog);
	}
}

void	progress_final(t_scene scn, int i)
{
	if (scn.save)
		ft_printf("\rRendering view %2d/%-2d [100%%]\n", i + 1, 1);
	else
		ft_printf("\rRendering view %2d/%-2d [100%%]\n", i + 1, scn.nb_cam);
}
