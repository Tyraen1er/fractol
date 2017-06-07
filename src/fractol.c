/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eferrand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/29 23:23:07 by eferrand          #+#    #+#             */
/*   Updated: 2017/06/07 07:24:21 by eferrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <stdio.h>

int		ft_colorpoint(int i)
{
	if (i < 8)
		return (0);
	if (i < 16)
		return (0x330099);
	if (i < 24)
		return (0x333399);
	if (i < 33)
		return (0x339999);
	if (i < 41)
		return (0x33CC99);
	if (i < 49)
		return (0x33FF99);
	if (i < 57)
		return (0x33FFCC);
	if (i < 66)
		return (0x33FFFF);
	if (i < 74)
		return (0x66FFFF);
	if (i < 82)
		return (0x99FFFF);
	if (i < 90)
		return (0xCCFFFF);
	if (i < 100)
		return (0xDDDDDD);
	return (0xFFFFFF);
}

int		julia(t_point z, t_point *c)
{
	int		a;
	double	tmp;

	a = -1;
	while (++a < 100 && z.x * z.x + z.y * z.y < 4)
	{
		tmp = z.x;
		z.x = (z.x * z.x) - (z.y * z.y) + ((c) ? c->x : 0.0);
		z.y = (2 * z.y * tmp) + ((c) ? c->y : 0.0);
		++a;
	}
	return (a);
}

int		mandelbrot(t_point z, t_point *c)
{
	int		a;
	double	zr;
	double	zi;
	double	tmp;

	a = 0;
	zr = 0;
	zi = 0;
	while (++a < 100 && zr * zr + zi* zi < 4)
	{
		tmp = zr;
		zr = zr * zr - zi * zi + ((c) ? c->x : z.x);
		zi = 2 * zi * tmp + ((c) ? c->y : z.y);
		++a;
	}
	return (a);
}

int		perso(t_point z, t_point *c)
{
	int		a;
	double	zr;
	double	zi;
	double	tmp;

	a = 0;
	zr = 0;
	zi = 0;
	while (++a < 100 && zr * zr + zi* zi < 4)
	{
		tmp = zr;
		zr = fabs(zr * zr - zi * zi) + ((c) ? c->x : z.x);
		zi = fabs(2 * zi * tmp) + ((c) ? c->y : z.y);
		++a;
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
		if ((f = (fractal) ? fractal : f) == 0)
			frac = (t_quad){.tl = {-1.7, -1.5}, .br = {1.7, 0.9}};
		else if (f == 1)
			frac = (t_quad){.tl = {-2.1, -1.2}, .br = {1.2, 0.6}};
		else if (f == 2)
			frac = (t_quad){.tl = {-2.5, 1.8}, .br = {-0.4, 0.6}};
	}
	if (z && z[0])
	{

		frac = ft_zoom_apply();
//		z[0] type zoom ||| z[1] pos x ||| z[2] pos y
	}
	else if (z && (z[1] || z[2]))
	{
		frac = ft_move_apply();
//		123 = gauche ||| 124 = droite ||| 125 = bas ||| 126 = haut
//		z[1] = translation x ||| z[2] = translation y
	}
	dis_screen(f, mlx, &frac, NULL);
}

int		main(int ac, char**av)
{
	t_point	z = {11, 5000};
	t_point	a = {11, 5000};
	if (ac != 2)
	{
		a = ft_point_in_quad_to_ratio((t_quad){{0, 0}, {1000, 700}}, a);
		printf("a.x = %f a.y = %f\n", a.x, a.y);
		a = ft_point_ratio_to_quad(a, (t_quad){{-3.0, 1.2}, {-1.2, 1.2}});
		printf("a.x = %f a.y = %f\n", a.x, a.y);
		z = ft_point_change_quad(z, (t_quad){{0, 0}, {1000, 700}}, (t_quad){{-3.0, 1.2}, {-1.2, 1.2}});
		printf("z.x = %f x.y = %f\n", z.x, z.y);
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
