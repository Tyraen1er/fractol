/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eferrand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/29 23:23:07 by eferrand          #+#    #+#             */
/*   Updated: 2017/06/02 02:27:54 by eferrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		julia(int x, int y, double *coord)
{
	double	a;
	double	zr;
	double	zi;
	double	tmp;

	(void)coord;
	a = 0;
	zr = 0;
	zi = 0;
	while (++a < 100 && zr * zr + zi* zi < 4)
	{
		tmp = zr;
		zr = (zr * zr) - (zi * zi) + x;
		zi = (2 * zi * tmp) + y; 
		++a;
	}
	return (a);
}

int		perso(int x, int y, double *coord)
{
	(void)x;
	(void)y;
	(void)coord;
	return (0);
}

int		mandelbrot(double x, double y)
{
	double	a;
	double	zr;
	double	zi;
	double	tmp;

	a = 0;
	zr = 0;
	zi = 0;
	while (++a < 100 && zr * zr + zi* zi < 4)
	{
		tmp = zr;
		zr = zr * zr - zi * zi + x;
		zi = 2 * zi * tmp + y; 
		++a;
	}
	return (a);
}

int		ft_colorpoint(int i)
{
	if (i < 40)
		return (0xFF0000);
	if (i < 80)
		return (0xFFD700);
	if (i < 100)
		return (0x4169E1);
	return (0xFFFFFF);
}


/*
 ** coord[0] = x1 || coord[1] = x2 || coord[2] == y1 || coord[3] = y2
 */

void	dis_screen(int f, void **mlx, double *coord)
{
	double	x;
	double	y;
	double	zoomx;
	double	zoomy;

	zoomx = 1000 / (coord[1] - coord[0]);
	zoomy = 1000 / (coord[3] - coord[2]);
	y = -1;
	while (++y < 1000 && (x = -1))
		while (++x < 1000)
		{
			if (f == 1)
				((int*)mlx[3])[(int)(x + y * 1000)] =
					ft_colorpoint(julia(x / zoomx + coord[0], 
								y / zoomy + coord[1], coord));
			if (f == 2)
				((int*)mlx[3])[(int)(x + y * 1000)] =
					ft_colorpoint(mandelbrot(x / zoomx + coord[0],
								y / zoomx + coord[1]));
			if (f == 3)
				((int*)mlx[3])[(int)(x + y * 1000)] =
					ft_colorpoint(perso(x / zoomx + coord[0],
								y / zoomy + coord[1], coord));
		}
	mlx_put_image_to_window(mlx[0], mlx[1], mlx[2], 0, 0);
}

//	z[0] = '+' || '-'
//	z[1] = x de la pos souris
//	z[2] = y de la pos souris

void	init(int fractal, int *z, void **mlx)
{
	static int		f = 0;
	static double	*coord;

	if (fractal)
	{
		if ((f = fractal) == 1)
		{
			coord = (double[8]){-1, 1, -1.2F, 1.2F};
			if (z)
				z += (z[0] == '+') ? 10 : -10;
		}
		else if (f == 2)
		{
			coord = (double[8]){-2.1F, 0.6F, -1.2F, 1.2F};
			if (z)
				z += (z[0] == '+') ? 10 : -10;
		}
		else if (f == 3)
		{
			coord = (double[8]){-2.1F, 0.6F, -1.2F, 1.2F};
			if (z)
				z += (z[0] == '+') ? 10 : -10;
		}
	}
	dis_screen(f, mlx, coord);
}

int		my_key_fct(int keycode, void *ptr)
{
	(void)ptr;
	if (keycode == 53)
		exit(3);
	return (0);
}

int		mouse_event(int x, int y, void *mlx)
{
	static int oldx = 0;
	static int oldy = 0;

	(void)mlx;
	oldx = x;
	oldy = y;
	//	julia(x - oldx);
	/*	ft_putstr("x : ");
		ft_putnbr(x);
		write(1, "\n", 1);
		ft_putstr("y : ");
		ft_putnbr(y);
		write(1, "\n", 1);
		write(1, "\n", 1);
		*/	return (0);
}

// bouton 4 = dezoom
// bouton 5 == zoom

int		scroll(int button, int x, int y, void *mlx)
{
	int		*zoom;

	(void)mlx;
	zoom = NULL;
	if (button == 4 || button == 5)
	{
		zoom = (int[3]){0};
		zoom[0] = (button == 4) ? '-' : '+';
		zoom[1] = x;
		zoom[2] = y;
	}
	init(0, zoom, mlx);
	return (0);
}

int		ft_display(int fractal)
{
	void	*mlx[4];
	int		bpp = 0;
	int		s_l = 0;
	int		endian = 0;

	(void)fractal;
	if (!(mlx[0] = mlx_init()) ||
			!(mlx[1] = mlx_new_window(mlx[0], 1000, 1000, "fractal 42")) ||
			!(mlx[2] = mlx_new_image(mlx[0], 1000, 1000)) || !(mlx[3] =
				(void*)mlx_get_data_addr(mlx[2], &(bpp), &(s_l), &(endian))))
		exit(3);
	init(fractal, NULL, mlx);
	mlx_key_hook(mlx[1], my_key_fct, NULL);
	mlx_mouse_hook (mlx[1], scroll, mlx);
	mlx_hook(mlx[1], MotionNotify, PointerMotionMask, mouse_event, mlx);
	mlx_loop(mlx[0]);
	return (0);
}

int		main(int ac, char**av)
{
	if (ac != 2)
	{
		ft_putstr("usage: ./fractal [Julia / Mandelbrot / Perso]\n");
		return (0);
	}
	else
	{
		if (!ft_strcmp(av[1], "Julia"))
			ft_display(1);
		else if (!ft_strcmp(av[1], "Mandelbrot"))
			ft_display(2);
		else if (!ft_strcmp(av[1], "Perso"))
			ft_display(3);
		else
			ft_putstr("Cette fractal n est pas enregistrée.\n");
	}
	return (0);
}
