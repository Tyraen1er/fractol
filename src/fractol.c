/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eferrand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/29 23:23:07 by eferrand          #+#    #+#             */
/*   Updated: 2017/06/05 08:08:10 by eferrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <stdio.h>

t_point	ft_point_in_quad_to_ratio(t_quad quad, t_point point)
{
	t_point	ratio;

	ratio.x = (point.x - quad.tl.x) / (quad.br.x - quad.tl.x);
	ratio.y = (point.y - quad.tl.y) / (quad.br.y - quad.tl.y);
	return (ratio);
}

t_point	ft_point_ratio_to_quad(t_point ratio, t_quad quad)
{
	t_point	point;

	ratio.x = point.x * (quad.br.x - quad.tl.x) + quad.tl.x;
	ratio.y = point.y * (quad.br.y - quad.tl.y) + quad.tl.y;
	return (ratio);
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

int		julia(t_point z, t_point *c)
{
	int		a;
	double	tmp;

	a = -1;
	while (++a < 100 && z.x * z.x + z.y * z.y < 4)
	{
		tmp = z.x;
		z.x = (z.x * z.x) - (z.y * z.y) + c->x;
		z.y = (2 * z.y * tmp) + c->y; 
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


/*
** coord[0] = x1 || coord[1] = x2 || coord[2] == y1 || coord[3] = y2
*/

void	dis_screen(int fractal, void **mlx, t_quad *coord, t_point *cst)
{
	t_point			z;
	static t_quad	*coo = NULL;
	static t_point	c = {0.0, 0.0};
	static int		f = 0;
	static int		(*func[3])(t_point, t_point*) = {julia, mandelbrot, perso};
	
	z.y = -1;
	coo = (coord) ? coord : coo;
	f = (fractal) ? fractal : f;
	if (c.y && ((c.x = cst->x) || 1))
		c.y = cst->y;
	while (++z.y < 1000 && (z.x = -1))
		while (++z.x < 1000)
			((int*)mlx[3])[(int)(z.x + z.y * 1000)] = ft_colorpoint(func[f](
				ft_point_ratio_to_quad(ft_point_in_quad_to_ratio(
						(t_quad){{0, 0}, {1000, 1000}}, z), *coo), &c)); 
		mlx_put_image_to_window(mlx[0], mlx[1], mlx[2], 0, 0);
}

//	z[0] = '+' || '-'
//	z[1] = x de la pos souris
//	z[2] = y de la pos souris
//	coord[0] = dimension largeur et limite gauche
//	coord[1] = limite droite
//	coord[2] = dimension limite haute ?
//	coord[3] = limite basse

void	init(int fractal, int *z, void **mlx)
{
	static int		f = 0;
	static t_quad	screen = {.tl = {0, 0}, .br = {1000, 1000}};
	static t_quad	frac;

	(void)z;
	(void)screen;
	if ((f = (fractal) ? fractal : f) == 0)
		frac = (t_quad){{-2.5, 1.2}, {-1.2, 1.2}};
	else if (f == 1)
		frac = (t_quad){{-2.5, 0.5}, {-1.2, 1.2}};
	else if (f == 2)
		frac = (t_quad){{-2.5, 0.4}, {-1.8, 0.6}};
	dis_screen(f, mlx, &frac, NULL);
}

int		my_key_fct(int keycode, void **mlx)
{
	if (keycode == 53)
		exit(3);
	if (keycode == 36)
		mouse_event(-3000, 0, mlx);
	return (0);
}

int		mouse_event(int x, int y, void **mlx)
{
	static int		on = -1;
	static t_point	c = {-0.9, -0.9};

	if (x == -3000)
		on = -on;
	if (on == -1 || x == -3000)
		return (0);
	if ((0 < x && x < 1000) && (0 < y && y < 1000))
	{
		c.x = (double)x / 416  - 1.8;
		c.y = (double)y / 555 - 0.8;
	}
	dis_screen(0, mlx, NULL, &c);
	return (0);
}

// bouton 4 == dezoom
// bouton 5 == zoom

int		scroll(int button, int x, int y, void **mlx)
{
static int	zoom[3];

	zoom[0] = x;
	zoom[1] = y;
	zoom[2] = button;
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
