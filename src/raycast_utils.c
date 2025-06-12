/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozamora- <ozamora-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 16:00:51 by ozamora-          #+#    #+#             */
/*   Updated: 2025/06/12 02:01:19 by ozamora-         ###   ########.fr       */
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
