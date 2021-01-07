/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 17:16:32 by lle-briq          #+#    #+#             */
/*   Updated: 2021/01/07 15:51:30 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	fill_colors(unsigned char col[3], int color)
{
	col[0] = (unsigned char)(((color / 256) / 256) % 256);
	col[1] = (unsigned char)((color / 256) % 256);
	col[2] = (unsigned char)(color % 256);
}

void	write_char_by_char(int fd, unsigned int n, int i)
{
	unsigned char	c[4];

	if (i != 6)
	{
		c[0] = (unsigned char)((((n / 256) / 256) / 256) % 256);
		c[1] = (unsigned char)(((n / 256) / 256) % 256 );
		c[2] = (unsigned char)((n / 256) % 256 );
		c[3] = (unsigned char)(n % 256);
	}
	else
	{
		c[0] = 1;
		c[1] = 0;
		c[2] = 24;
		c[3] = 0;
	}
	write(fd, c, 4);
}

void	write_header(int fd, t_scene scene)
{
	unsigned int	header[13];
	int				size_img;
	int				i;

	write(fd, "BM", 2);
	size_img = 4 * scene.w * scene.h;
	header[0] = size_img + 54;
	header[1] = 0;
	header[2] = 54;
	header[3] = 40;
	header[4] = scene.w;
	header[5] = scene.h;
	header[7] = size_img;
	header[8] = 0;
	header[9] = 0;
	header[10] = 0;
	header[11] = 0;
	header[12] = 0;
	i = -1;
	while (++i < 13)
		write_char_by_char(fd, header[i], i);
}

int	bmp_create(t_scene scene, char *file)
{
	int				fd;
	int				i;
	int				j;
	unsigned char	col[3];

	fd = open(file, O_CREAT | O_WRONLY | O_TRUNC);
	if (fd < 0)
		return (-1);
	i = -1;
	write_header(fd, scene);
	while (++i <= scene.h)
	{
		j = -1;
		while (++j <= scene.w)
		{
			fill_colors(col, (scene.img_data[0])[i * scene.w + j]);
			write(fd, col, 3);
			write(fd, "0", 1);
		}
	}
	close(fd);
	return (0);
}
