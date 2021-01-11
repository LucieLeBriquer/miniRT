/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <lle-briq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 05:58:50 by lle-briq          #+#    #+#             */
/*   Updated: 2021/01/11 23:18:22 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static char	*bmp_filename(char *file, char *dir, char *ext)
{
	char	*filename;
	int		i;
	int		l;
	int		l_dir;
	int		l_ext;

	l = ft_strlen(file);
	l_dir = ft_strlen(dir);
	l_ext = ft_strlen(ext);
	filename = ft_calloc(l + l_dir + l_ext + 1, sizeof(char));
	if (!filename)
		return (NULL);
	i = -1;
	while (++i < l_dir)
		filename[i] = dir[i];
	i = -1;
	while (++i < l)
		filename[i + l_dir] = file[i];
	i = -1;
	while (++i < l_ext)
		filename[i + l_dir + l] = ext[i];
	filename[l_dir + l + l_ext] = '\0';
	return (filename);
}

static int	fill_save_options(t_scene *scn, char **argv, int argc, int i)
{
	scn->save = 1;
	if (i + 1 < argc && ft_strcmp("-a", argv[i + 1]) != 0)
	{
		scn->file_save = bmp_filename(argv[i + 1], "bitmap/", ".bmp");
		if (!(scn->file_save))
		{
			scn->file_save = "bitmap/save.bmp";
			scn->save = 1;
		}
		else
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
	scn->file_save = "bitmap/save.bmp";
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
