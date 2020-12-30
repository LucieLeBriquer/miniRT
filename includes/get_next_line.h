/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <lle-briq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 17:54:58 by lle-briq          #+#    #+#             */
/*   Updated: 2020/12/30 15:01:27 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 32
# endif

typedef struct s_buffer
{
	int		size;
	char	content[BUFFER_SIZE + 1];
}			t_buffer;

char	*join_and_realloc(char *s, char *buf, int size);
int		find_char_index(char *str, char c);
int		get_next_line(int fd, char **line);

#endif
