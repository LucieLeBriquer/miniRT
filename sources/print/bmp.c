/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <lle-briq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 01:04:20 by lle-briq          #+#    #+#             */
/*   Updated: 2021/01/10 01:10:40 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
# define HEADER_SIZE 122

void	fill_bmp(unsigned char *data, t_scene scn)
{
	int i;
	int j;
	int x;
	int y;

	i = HEADER_SIZE;
	y = scn.h;
	while (y--)
	{
		x = -1;
		while (++x < scn.w)
		{
			j = ((x * (scn.bpp / 8)) + (y * scn.size_line)) / 4;
			data[i++] = scn.img_data[0][j] % 256;
			data[i++] = (scn.img_data[0][j] / 256) % 256;
			data[i++] = ((scn.img_data[0][j] / 256) / 256) % 256;
		}
	}
}

void	header_bmp(unsigned char **data, t_scene scn)
{
	unsigned int size;

	size = scn.h * scn.w * 3;
	*(unsigned short *)*data = *(const unsigned int *)(unsigned long)"BM";
	*(unsigned int *)(*data + 2) = (size + HEADER_SIZE);
	*(unsigned int *)(*data + 6) = 0u;
	*(unsigned char *)(*data + 10) = HEADER_SIZE;
	*(unsigned int *)(*data + 14) = HEADER_SIZE - 14;
	*(unsigned int *)(*data + 18) = scn.w;
	*(unsigned int *)(*data + 22) = scn.h;
	*(unsigned short *)(*data + 26) = 1;
	*(unsigned short *)(*data + 28) = 24;
	*(unsigned int *)(*data + 30) = 0;
	*(unsigned int *)(*data + 34) = (unsigned int)size;
	*(unsigned int *)(*data + 38) = 3780;
	*(unsigned int *)(*data + 42) = 3780;
	*(int *)(*data + 46) = 0;
	*(int *)(*data + 50) = 0;
}

void	create_bmp(t_scene scn, char *filename)
{
	int				fd;
	unsigned int	size;
	unsigned int	i;
	unsigned char	*data;

	size = scn.h * scn.w * 3;
	if (!(data = malloc((size + HEADER_SIZE))))
		return ;
	i = 0;
	while (i < size + HEADER_SIZE)
		data[i++] = 0;
	header_bmp(&data, scn);
	fill_bmp(data, scn);
	if ((fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644)) <= 0)
		return ;
	write(fd, data, (size + HEADER_SIZE));
	close(fd);
}
