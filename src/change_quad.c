/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_quad.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eferrand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/07 07:15:03 by eferrand          #+#    #+#             */
/*   Updated: 2017/06/13 06:52:17 by eferrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

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
		c.x = (double)x / 416 - 1.8;
		c.y = (double)y / 555 - 0.8;
	}
	dis_screen(-1, mlx, (t_quad){{0, 0}, {0, 0}}, c);
	return (0);
}

t_quad	ft_move_apply(t_quad quad, int *move)
{
	double	shift;

	if (move[1])
	{
		shift = (quad.br.x - quad.tl.x) / 10;
		quad.tl.x += (move[1] == 123) ? shift : -shift;
		quad.br.x += (move[1] == 123) ? shift : -shift;
	}
	if (move[2])
	{
		shift = (quad.br.y - quad.tl.y) / 10;
		quad.tl.y += (move[2] == 125) ? -shift : shift;
		quad.br.y += (move[2] == 125) ? -shift : shift;
	}
	return (quad);
}

t_quad	ft_zoom_apply(t_quad quad, int *z)
{
	double	ratio;
	double	offset;
	t_point	point;

	point.x = z[1];
	point.y = z[2];
	point = ft_point_change_quad(point, (t_quad){{0, 0}, {1000, 1000}}, quad);
	ratio = ((z[0] == '-') ? 0.9 : 1.1);
	offset = point.x * (1 - ratio);
	quad = (t_quad){{quad.tl.x * ratio + offset, quad.tl.y},
		{quad.br.x * ratio + offset, quad.br.y}};
	offset = point.y * (1 - ratio);
	quad = (t_quad){{quad.tl.x, quad.tl.y * ratio + offset},
		{quad.br.x, quad.br.y * ratio + offset}};
	return (quad);
}
