/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_code.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <lle-briq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 22:13:39 by lle-briq          #+#    #+#             */
/*   Updated: 2021/01/08 21:36:38 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLX_CODE_H
# define MLX_CODE_H

# ifdef MAC
#  define DESTROY 10
# else
#  define DESTROY 33
# endif

# ifdef MAC
#  define S_KEY 1
# else
#  define S_KEY 115
# endif

# ifdef MAC
#  define W_KEY 13
# else
#  define W_KEY 122
# endif

# ifdef MAC
#  define SP_KEY 49
# else
#  define SP_KEY 32
# endif

# ifdef MAC
#  define ESC_KEY 53
# else
#  define ESC_KEY 65307
# endif

# ifdef MAC
#  define RIGHT_KEY 124
# else
#  define RIGHT_KEY 65363
# endif

# ifdef MAC
#  define LEFT_KEY 123
# else
#  define LEFT_KEY 65361
# endif

# ifdef MAC
#  define F_KEY 3
# else
#  define F_KEY 102
# endif

#endif
