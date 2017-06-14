/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eferrand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/11 08:36:27 by eferrand          #+#    #+#             */
/*   Updated: 2017/06/15 01:22:07 by eferrand         ###   ########.fr       */
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
# define MOTIONNOTIFY 6
# define POINTERMOTIONMASK	(1L<<6)

t_quad	ft_zoom_apply(t_quad a, int *z);
t_quad	ft_move_apply(t_quad a, int *z);
int		scroll(int a, int b, int d, void **c);
int		mouse_event(int a, int b, void **c);
int		my_key_fct(int a, void **b);
int		julia(t_point a, t_point b);
int		mandelbrot(t_point a, t_point b);
int		newton(t_point a, t_point b);
int		b_ship(t_point a, t_point b);
int		ft_colorpoint(int a);
void	dis_screen(int a, void **b, t_quad c, t_point d);
void	init(int c, int *a, void **b);
int		ft_display(int a);

#endif
