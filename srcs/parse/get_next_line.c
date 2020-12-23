/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <lle-briq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 17:54:41 by lle-briq          #+#    #+#             */
/*   Updated: 2020/12/23 14:05:12 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	check_errors(int fd, char **line, int size, int is_start)
{
	if (BUFFER_SIZE <= 0)
		return (0);
	if (is_start)
		*line = malloc(sizeof(char));
	if (!(*line))
		return (0);
	if (size < 0 || fd < 0)
	{
		free(*line);
		*line = 0;
		return (0);
	}
	if (is_start)
		(*line)[0] = '\0';
	return (1);
}

int			maj_buffer(char *buf, int i)
{
	int		j;

	j = 0;
	while (j < BUFFER_SIZE - i)
	{
		buf[j] = buf[i + 1 + j];
		j++;
	}
	i = j;
	while (j <= BUFFER_SIZE)
	{
		buf[j] = '\0';
		j++;
	}
	return (i);
}

int			get_next_line(int fd, char **line)
{
	static t_buffer	buff;
	int				i;

	if (!line || !check_errors(fd, line, 1, 1))
		return (-1);
	if (buff.size <= 0)
	{
		buff.size = read(fd, buff.content, BUFFER_SIZE);
		buff.content[buff.size < 0 ? 0 : buff.size] = '\0';
	}
	while (buff.size > 0)
	{
		i = find_char_index(buff.content, '\n');
		if (i >= 0)
		{
			*line = join_and_realloc(*line, buff.content, i);
			buff.size = maj_buffer(buff.content, i);
			return (check_errors(fd, line, 1, 0));
		}
		*line = join_and_realloc(*line, buff.content, BUFFER_SIZE + 1);
		buff.size = read(fd, buff.content, BUFFER_SIZE);
		buff.content[buff.size < 0 ? 0 : buff.size] = '\0';
	}
	return (check_errors(fd, line, buff.size, 0) - 1);
}
