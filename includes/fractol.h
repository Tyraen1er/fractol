/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eferrand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/11 08:36:27 by eferrand          #+#    #+#             */
/*   Updated: 2017/06/14 05:44:11 by eferrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H
# include "libft.h"
# include "mlx.h"
# include <math.h>
# include <stdio.h>

# define ESCAPE 53
# define ENTER 36
# define MotionNotify 6
# define PointerMotionMask (1L<<6)

t_quad	ft_zoom_apply(t_quad, int *z);
t_quad	ft_move_apply(t_quad, int *z);
int		scroll(int, int, int, void**);
int		mouse_event(int, int, void**);
int		my_key_fct(int, void**);
int		julia(t_point, t_point);
int		mandelbrot(t_point, t_point);
int		newton(t_point, t_point);
int		b_ship(t_point, t_point);
int		ft_colorpoint(int);
void	dis_screen(int, void**, t_quad, t_point);
void	init(int, int*, void**);
int		ft_display(int);

#endif
