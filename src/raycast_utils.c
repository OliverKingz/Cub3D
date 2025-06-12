/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozamora- <ozamora-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 16:00:51 by ozamora-          #+#    #+#             */
/*   Updated: 2025/06/12 15:42:57 by ozamora-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	deg_to_rad(double angle_degs)
{
	return (angle_degs * PI / 180.0);
}

double	rad_to_deg(double angle_rads)
{
	return (angle_rads * 180.0 / PI);
}

t_point	rad_to_vector(double angle_rads)
{
	t_point	p;

	p.x = cos(angle_rads);
	p.y = sin(angle_rads);
	return (p);
}

double	get_distance_length(t_point start_pos, t_point end_pos)
{
	double	size_x;
	double	size_y;
	double	length;

	size_x = start_pos.x - end_pos.x;
	size_y = start_pos.y - end_pos.y;
	length = sqrt(size_x * size_x + size_y * size_y);
	return (length);
}
