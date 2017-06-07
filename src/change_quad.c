/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_quad.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eferrand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/07 07:15:03 by eferrand          #+#    #+#             */
/*   Updated: 2017/06/07 08:12:35 by eferrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

t_quad	ft_move_apply(t_quad quad, int *move)
{
	double	shift;

	if (z[1])
	{
		shift = (quad.br.x - quad.tl.x) / 10;
		quad.tl.x += (z[1] == 123) ? -shift : shift;
		quad.br.x += (z[1] == 123) ? -shift : shift;
	}
	if (z[2])
	{
		shift = (quad.br.y - quad.tl.y) / 10;
		quad.tl.y += (z[1] == 125) ? -shift : shift;
		quad.br.y += (z[1] == 125) ? -shift : shift;
	}
}

t_quad	ft_zoom_apply(t_quad quad, int *zoom)
{
	t_point	x;
	t_point	y;


	quad.tl.x += z * ft_point_in_quad_to_ratio();
	quad.br.x += z;
}
