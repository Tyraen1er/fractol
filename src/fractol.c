/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eferrand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/29 23:23:07 by eferrand          #+#    #+#             */
/*   Updated: 2017/06/13 06:54:03 by eferrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <stdio.h>

int		julia(t_point z, t_point c)
{
	int		a;
	double	tmp;

	a = -1;
	while (++a < 100 && z.x * z.x + z.y * z.y < 4)
	{
		tmp = z.x;
		z.x = (z.x * z.x) - (z.y * z.y) + c.x;
		z.y = (2 * z.y * tmp) + c.y;
	}
	return (a);
}

int		mandelbrot(t_point z, t_point c)
{
	int		a;
	double	zr;
	double	zi;
	double	tmp;

	a = 0;
	zr = 0;
	zi = 0;
	(void)z;
	while (++a < 100 && zr * zr + zi * zi < 4)
	{
		tmp = zr;
		zr = zr * zr - zi * zi + c.x;
		zi = 2 * zi * tmp + c.y;
	}
	return (a);
}

int		perso(t_point z, t_point c)
{
	int		a;
	double	zr;
	double	zi;
	double	tmp;

	a = 0;
	zr = 0;
	zi = 0;
	(void)z;
	while (++a < 100 && zr * zr + zi * zi < 4)
	{
		tmp = zr;
		zr = fabs(zr * zr - zi * zi) + c.x;
		zi = fabs(2 * zi * tmp) + c.y;
	}
	return (a);
}

void	init(int fractal, int *z, void **mlx)
{
	static int		f = -1;
	static t_quad	frac;

	(void)z;
	if (f == -1 || (z && z[0] == 0 && z[1] == 0 && z[2] == 0))
	{
		if ((f = fractal) == 0)
			frac = (t_quad){.tl = {-1.7, -1.5}, .br = {1.7, 1.7}};
		else if (f == 1)
			frac = (t_quad){.tl = {-2.1, -1.2}, .br = {1.2, 0.6}};
		else if (f == 2)
			frac = (t_quad){.tl = {-2.5, 1.8}, .br = {-0.4, 0.6}};
	}
	if (z && z[0])
		frac = ft_zoom_apply(frac, z);
	else if (z && (z[1] || z[2]))
		frac = ft_move_apply(frac, z);
	dis_screen(f, mlx, frac, (t_point){5, 5});
}

int		main(int ac, char **av)
{
	if (ac != 2)
	{
		ft_putstr("usage: ./fractal [Julia / Mandelbrot / Perso]\n");
		return (0);
	}
	else
	{
		if (!ft_strcmp(av[1], "Julia"))
			ft_display(0);
		else if (!ft_strcmp(av[1], "Mandelbrot"))
			ft_display(1);
		else if (!ft_strcmp(av[1], "Perso"))
			ft_display(2);
		else
			ft_putstr("Cette fractal n est pas enregistrée.\n");
	}
	return (0);
}
