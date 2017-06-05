/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eferrand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/29 23:23:07 by eferrand          #+#    #+#             */
/*   Updated: 2017/06/05 02:43:41 by eferrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"


int		julia(double x, double y, double *c)
{
	int		a;
	double	tmp;

	a = -1;
	while (++a < 100 && x * x + y * y < 4)
	{
		tmp = x;
		x = (x * x) - (y * y) + c[0];
		y = (2 * y * tmp) + c[1]; 
		++a;
	}
	return (a);
}

int		mandelbrot(double x, double y)
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
		zr = zr * zr - zi * zi + x;
		zi = 2 * zi * tmp + y; 
		++a;
	}
	return (a);
}

/*
int		perso(double x, double y)
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
		zr = zr * zr * zr - 3 * zr * zi * zi + x;
		zi = 3 * tmp * tmp * zi - 3 * zi  + y; 
		++a;
	}
	return (a);
}
*/


int		perso(double x, double y) 
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
		zr = fabs(zr * zr - zi * zi) + x;
		zi = fabs(2 * zi * tmp) + y; 
		++a;
	}
	return (a);
}


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


/*
** coord[0] = x1 || coord[1] = x2 || coord[2] == y1 || coord[3] = y2
*/

void	dis_screen(int fractal, void **mlx, double *coord, double *cri)
{
	double			x;
	double			y;
	static double	*coo = NULL;
	static double	c[2] = {0.285F, 0.01F};
	static int		f = 0;
	
	y = -1;
	coo = (coord) ? coord : coo;
	f = (fractal) ? fractal : f;
	if (cri && ((c[0] = cri[0]) || 1))
		c[1] = cri[1];
	while (++y < 1000 && (x = -1))
		while (++x < 1000)
		{
			if (f == 1)
				((int*)mlx[3])[(int)(x + y * 1000)] = ft_colorpoint(julia(
						coo[0] + (coo[1] - coo[0] / 1000 * x),
						coo[2] + (coo[3] - coo[2]) / 1000 * y, c));
			if (f == 2)
				((int*)mlx[3])[(int)(x + y * 1000)] = ft_colorpoint(mandelbrot(
						coo[0] + (coo[1] - coo[0] / 1000 * x),
						coo[2] + (coo[3] - coo[2]) / 1000 * y));
			if (f == 3)
				((int*)mlx[3])[(int)(x + y * 1000)] = ft_colorpoint(perso(
						coo[0] + (coo[1] - coo[0] / 1000 * x),
						coo[2] + (coo[3] - coo[2]) / 1000 * y));
		}
	mlx_put_image_to_window(mlx[0], mlx[1], mlx[2], 0, 0);
}

//	z[0] = '+' || '-'
//	z[1] = x de la pos souris
//	z[2] = y de la pos souris
//	coord[0] = dimension largeur et limite gauche
//	coord[1] = limite droite
//	coord[2] = dimension limite haute ?
//	coord[3] = limite basse


void	init(int fractal, double *z, void **mlx)
{
	static int		f = 0;
	static double	coord[4];

	if ((f = (fractal) ? fractal : f) == 1)
	{
		coord[0] = (z) ? -2.5F : -2.5F;
		coord[1] = (z) ? 1.2F : 1.2F;
		coord[2] = (z) ? -1.2F : -1.2F;
		coord[3] = (z) ? 1.2F : 1.2F;
	}
	else if (f == 2)
	{
		coord[0] = (z) ? -2.5F : -2.5F;
		coord[1] = (z) ? 0.5F : 0.5F;
		coord[2] = (z) ? -1.2F : -1.2F;
		coord[3] = (z) ? 1.2F : 1.2F;
	}
	else if (f == 3)
	{
		coord[0] = (z) ? -2.5F : -2.5F;
		coord[1] = (z) ? 0.4F : 0.4F;
		coord[2] = (z) ? -1.8F : -1.8F;
		coord[3] = (z) ? 0.6F : 0.6F;
	}
	dis_screen(f, mlx, coord, NULL);
}

int		my_key_fct(int keycode, void *mlx)
{
	if (keycode == 53)
		exit(3);
	if (keycode == 36)
		mouse_event(-3000, 0, mlx);
	return (0);
}

int		mouse_event(int x, int y, void *mlx)
{
	static int		on = 1;
	static double	cri[2] = {-0.9, -0.9};

	if (x == -3000)
		on = -on;
	if (on == -1 || x == -3000)
		return (0);
	if ((0 < x && x < 1000) && (0 < y && y < 1000))
	{
		cri[0] = ((double)x / 416)  - 1.8;
		cri[1] = ((double)y / 555) - 0.8;
	}
	dis_screen(0, (void**)mlx, NULL, cri);
	return (0);
}

// bouton 4 = dezoom
// bouton 5 == zoom

int		scroll(int button, int x, int y, void *mlx)
{
	static double	*zoom;

	(void)mlx;
	zoom = NULL;
	if ((button == 4 || button == 5) && 0 < x && x < 1000 && 0 < y && y < 1000)
	{
		zoom = (double[4]){1, 1, 1, 1};
//		zoom[0] = (button == 4) ? '-' : '+';
//		zoom[1] = (button == 4) ? ;
//		zoom[2] = (button == 4) ? ;
//		zoom[3] = (button == 4) ? 
	}
	init(0, zoom, mlx);
	return (0);
}

int		ft_display(int fractal)
{
	void			*mlx[4];
	int				bpp = 0;
	int				s_l = 0;
	int				endian = 0;

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
