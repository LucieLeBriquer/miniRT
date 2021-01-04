/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_code.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <lle-briq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 22:13:39 by lle-briq          #+#    #+#             */
/*   Updated: 2021/01/04 17:17:55 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLX_CODE_H
# define MLX_CODE_H

# define N_KEY 45
# define O_KEY 31
# define P_KEY 35
# define Q_KEY 12
# define R_KEY 15
# ifndef MAC
#  define S_KEY 115
# else
#  define S_KEY 1
# endif
# define T_KEY 17
# define U_KEY 32
# define V_KEY 9
# ifndef MAC
#  define W_KEY 119
# else
#  define W_KEY 13
# endif
# define X_KEY 7
# define Y_KEY 16
# define Z_KEY 6

# define K1_KEY 18
# define K2_KEY 19
# define K3_KEY 20
# define K4_KEY 21
# define K5_KEY 23
# define K6_KEY 22
# define K7_KEY 26
# define K8_KEY 28
# define K9_KEY 25
# define K0_KEY 29

# ifndef MAC
#  define SP_KEY 32
# else
#  define SP_KEY 49
# endif
# define BQ_KEY 50
# define MN_KEY 27
# define PL_KEY 24
# define SBO_KEY 33
# define SBC_KEY 30
# define BSL_KEY 42
# define SC_KEY 41
# define SQ_KEY 39
# define CM_KEY 43
# define PT_KEY 47
# define SL_KEY 44

# define F1_KEY 122
# define F2_KEY 120
# define F3_KEY 99
# define F4_KEY 118
# define F5_KEY 96
# define F6_KEY 97
# define F7_KEY 98
# define F8_KEY 100
# define F9_KEY 101
# define F10_KEY 109
# define F11_KEY 110
# define F12_KEY 111
# define F13_KEY 105
# define F14_KEY 107
# define F15_KEY 113
# define F16_KEY 106
# define F17_KEY 64
# define F18_KEY 79
# define F19_KEY 80

# ifndef MAC
#  define ESC_KEY 65307
# else
#  define ESC_KEY 53
# endif
# define TAB_KEY 48
# define CL_KEY 272
# define LSFT_KEY 65505
# define LCTRL_KEY 256
# define LOPT_KEY 261
# define LCMD_KEY 259
# define LDEL_KEY 51
# define RTN_KEY 36
# define RSFT_KEY 258
# define RCTRL_KEY 269
# define ROPT_KEY 262
# define RCMD_KEY 260
# define EJ_KEY
# define FN_KEY 279
# define RDEL_KEY 117
# define HOME_KEY 115
# define END_KEY 119
# define PUP_KEY 116
# define PDOWN_KEY 121
# define CLR_KEY 71

# define UP_KEY 126
# define DOWN_KEY 125
# ifndef MAC
#  define RIGHT_KEY 65363
# else
#  define RIGHT_KEY 124
# endif
# ifndef MAC
#  define LEFT_KEY 65361
# else
#  define LEFT_KEY 123
# endif

#endif
