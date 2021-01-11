/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <lle-briq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 05:58:50 by lle-briq          #+#    #+#             */
/*   Updated: 2021/01/11 21:28:43 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static char	*bmp_filename(char *file, char dir[4], char ext[4])
{
	char	*filename;
	int		i;
	int		l;

	l = ft_strlen(file);
	filename = ft_calloc(l + 9, sizeof(char));
	if (!filename)
		return ("bmp/save.bmp");
	i = -1;
	while (++i < l)
		filename[4 + i] = file[i];
	i = -1;
	while (++i < 4)
	{
		filename[i] = dir[i];
		filename[l + 4 + i] = ext[i];
	}
	filename[l + 8] = '\0';
	return (filename);
}

static int	fill_save_options(t_scene *scn, char **argv, int argc, int i)
{
	scn->save = 1;
	if (i + 1 < argc && ft_strcmp("-a", argv[i + 1]) != 0)
	{
		scn->file_save = bmp_filename(argv[i + 1], "bmp/", ".bmp");
		scn->save = 2;
		return (i + 1);
	}
	return (i);
}

int			options(int argc, char **argv, t_scene *scn)
{
	int	i;

	if (argc < 2)
		return (-1);
	scn->file = argv[1];
	scn->file_save = "bmp/save.bmp";
	scn->aliasing = 0;
	scn->save = 0;
	i = 1;
	while (++i < argc)
	{
		if (ft_strcmp("-a", argv[i]) == 0)
			scn->aliasing = 1;
		else if (ft_strcmp("-save", argv[i]) == 0)
			i = fill_save_options(scn, argv, argc, i);
		else
			return (-1);
	}
	return (1);
}