/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_obj.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <lle-briq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/20 16:26:57 by lle-briq          #+#    #+#             */
/*   Updated: 2020/12/22 15:28:09 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	print_sph(t_obj sph, int i)
{
	printf("[%02d]sph :", i);
	print_vect(sph.o);
	print_col(sph.col);
	print_float(sph.r);
	newline();
}

void	print_pln(t_obj pln, int i)
{
	printf("[%02d]pln :", i);
	print_vect(pln.o);
	print_vect(pln.axe);
	print_col(pln.col);
	newline();
}

void	print_sqr(t_obj sqr, int i)
{
	printf("[%02d]sqr :", i);
	print_vect(sqr.o);
	print_vect(sqr.axe);
	print_float(sqr.h);
	print_col(sqr.col);
	newline();
}

void	print_cyl(t_obj cyl, int i)
{
	printf("[%02d]cyl :", i);
	print_vect(cyl.o);
	print_vect(cyl.axe);
	print_float(cyl.r);
	print_col(cyl.col);
	newline();
}

void	print_trg(t_obj trg, int i)
{
	printf("[%02d]trg :", i);
	print_vect(trg.o);
	print_vect(trg.p);
	newline();
	newtab();
	print_vect(trg.q);
	print_vect(trg.axe);
	print_col(trg.col);
	newline();
}
