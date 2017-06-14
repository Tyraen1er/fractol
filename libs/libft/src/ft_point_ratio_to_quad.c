/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_point_ratio_to_quad.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eferrand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/05 21:34:57 by eferrand          #+#    #+#             */
/*   Updated: 2017/06/15 01:03:51 by eferrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

t_point	ft_point_ratio_to_quad(t_point ratio, t_quad quad)
{
	ratio.x = (ratio.x * (quad.br.x - quad.tl.x)) + quad.tl.x;
	ratio.y = (ratio.y * (quad.br.y - quad.tl.y)) + quad.tl.y;
	return (ratio);
}
