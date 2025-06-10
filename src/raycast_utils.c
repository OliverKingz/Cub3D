/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozamora- <ozamora-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 16:00:51 by ozamora-          #+#    #+#             */
/*   Updated: 2025/06/10 16:07:41 by ozamora-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	degrees_to_radians(double angle_degs)
{
	return (angle_degs * PI / 180.0);
}

t_point	radians_to_vector(double angle_rads)
{
	t_point	p;

	p.x = cos(angle_rads);
	p.y = sin(angle_rads);
	return (p);
}
