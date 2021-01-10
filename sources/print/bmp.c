/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <lle-briq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 01:04:20 by lle-briq          #+#    #+#             */
/*   Updated: 2021/01/10 14:43:32 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	fill_unsigned_int(unsigned char *data_ptr, unsigned int i)
{
	data_ptr[0] = (unsigned char)(i);
	data_ptr[1] = (unsigned char)(i >> 8);
	data_ptr[2] = (unsigned char)(i >> 16);
	data_ptr[3] = (unsigned char)(i >> 24);
}

static void	fill_unsigned_short(unsigned char *data_ptr, unsigned short i)
{
	data_ptr[0] = (unsigned char)(i);
	data_ptr[1] = (unsigned char)(i >> 8);
}

static void	fill_data(unsigned char *data, t_scene scn)
{
	int	i;
	int	j;
	int	p;
	int	k;

	k = HEADER_SIZE;
	i = scn.h;
	while (i--)
	{
		j = -1;
		while (++j < scn.w)
		{
			p = ((j * (scn.bpp / 8)) + (i * scn.size_line)) / 4;
			data[k] = scn.img_data[0][p] % 256;
			data[k + 1] = (scn.img_data[0][p] / 256) % 256;
			data[k + 2] = ((scn.img_data[0][p] / 256) / 256) % 256;
			k += 3;
		}
	}
}

static void	header(unsigned char *data, t_scene scn, unsigned int size)
{
	data[0] = 'B';
	data[1] = 'M';
	fill_unsigned_int(data + 2, size + HEADER_SIZE);
	fill_unsigned_int(data + 10, HEADER_SIZE);
	fill_unsigned_int(data + 14, HEADER_SIZE - 14);
	fill_unsigned_int(data + 18, scn.w);
	fill_unsigned_int(data + 22, scn.h);
	fill_unsigned_short(data + 26, 1);
	fill_unsigned_short(data + 28, 24);
	fill_unsigned_int(data + 34, size);
	fill_unsigned_int(data + 38, 3780);
	fill_unsigned_int(data + 42, 3780);
}

int	create_bmp(t_scene scn, char *file)
{
	int				fd;
	unsigned int	size;
	unsigned char	*data;

	size = scn.h * scn.w * 3;
	data = ft_calloc(size + HEADER_SIZE, sizeof(unsigned char));
	if (!data)
		return (-1);
	header(data, scn, size);
	fill_data(data, scn);
	fd = open(file, O_CREAT | O_TRUNC | O_RDWR, 0644);
	if (fd <= 0)
	{
		free(data);
		return (-2);
	}
	write(fd, data, (size + HEADER_SIZE));
	free(data);
	return (close(fd));
}
