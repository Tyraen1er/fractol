/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eferrand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/07 06:49:50 by eferrand          #+#    #+#             */
/*   Updated: 2017/06/14 05:44:02 by eferrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		ft_display(int fractal)
{
	void	*mlx[4];
	int		bpp;
	int		s_l;
	int		endian;

	bpp = 0;
	s_l = 0;
	endian = 0;
	if (!(mlx[0] = mlx_init()) ||
			!(mlx[1] = mlx_new_window(mlx[0], 1000, 1000, "fractal 42")) ||
			!(mlx[2] = mlx_new_image(mlx[0], 1000, 1000)) ||
			!(mlx[3] =
				(void*)mlx_get_data_addr(mlx[2], &(bpp), &(s_l), &(endian))))
		exit(3);
	init(fractal, NULL, mlx);
	mlx_key_hook(mlx[1], my_key_fct, mlx);
	mlx_mouse_hook(mlx[1], scroll, mlx);
	mlx_hook(mlx[1], MotionNotify, PointerMotionMask, mouse_event, mlx);
	mlx_loop(mlx[0]);
	return (0);
}

int		my_key_fct(int keycode, void **mlx)
{
	int	z[3];

	if (keycode == 53)
		exit(3);
	if (keycode == 36)
		mouse_event(-3000, 0, mlx);
	z[0] = 0;
	z[1] = (keycode == 123 || keycode == 124) ? keycode : 0;
	z[2] = (keycode == 125 || keycode == 126) ? keycode : 0;
	init(-1, z, mlx);
	return (0);
}

int		scroll(int button, int x, int y, void **mlx)
{
	static int	zoom[3];

	zoom[0] = (button == 4) ? '-' : '+';
	zoom[1] = x;
	zoom[2] = y;
	init(-1, zoom, mlx);
	return (0);
}

void	dis_screen(int fractal, void **mlx, t_quad coord, t_point cst)
{
	t_point			z;
	static t_quad	coo = {.tl = {0, 0}, .br = {0, 0}};
	static t_point	c = {0, 0};
	static int		f = 0;
	static int		(*func[3])(t_point, t_point) = {julia, mandelbrot, b_ship};

	if (coord.tl.x != 0 && coord.tl.y != 0 && coord.br.x != 0 &&
			coord.br.y != 0)
		coo = coord;
	if (cst.x != 5)
		c = cst;
	f = (fractal != -1) ? fractal : f;
	z.y = -1;
	while (++z.y < 1000 && (z.x = -1))
		while (++z.x < 1000)
		{
			((int*)(mlx[3]))[(int)(z.x + z.y * 1000)] = ft_colorpoint(
			func[f](ft_point_change_quad(z, (t_quad){{0, 0}, {1000, 1000}},
					coo), c));
		}
	mlx_put_image_to_window(mlx[0], mlx[1], mlx[2], 0, 0);
}
