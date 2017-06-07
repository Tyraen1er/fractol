/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_point_change_quad.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eferrand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/05 21:40:28 by eferrand          #+#    #+#             */
/*   Updated: 2017/06/05 23:29:29 by eferrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_point	ft_point_change_quad(t_point point, t_quad fst, t_quad scd)
{
	return (ft_point_ratio_to_quad(ft_point_in_quad_to_ratio(fst, point), scd));
}
