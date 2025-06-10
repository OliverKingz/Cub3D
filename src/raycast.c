/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozamora- <ozamora-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 14:35:02 by raperez-          #+#    #+#             */
/*   Updated: 2025/06/10 16:04:32 by ozamora-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_ray(t_game *game, t_ray *ray, double angle)
{
	ray->angle_radians = degrees_to_radians(angle);
	ray->vector = angle_to_vector(ray->angle_radians);
		// Calculo el vector direccion
	ray->start_pos.x = game->player.pos.x;
	ray->start_pos.y = game->player.pos.y;
	ray->end_pos.x = game->player.pos.x;
	ray->end_pos.y = game->player.pos.y;
	ray->collision_dir = NONE;
	get_delta(ray);
	if (ray->vector.x > 0)
		ray->step.x = 1;
	else if (ray->vector.x < 0)
		ray->step.x = -1;
	else
		ray->step.x = 0;
	if (ray->vector.y > 0)
		ray->step.y = 1;
	else if (ray->vector.y < 0)
		ray->step.y = -1;
	else
		ray->step.y = 0;
}

// Lanza un rayo desde la posición inicial (xO, yO) con el angulo (angle)
// Retorna la distancia que recorrió el rayo
t_ray	cast_ray(t_game *game, double angle)
{
	t_ray	ray;

	init_ray(game, &ray, angle);
	while (!ray.collision_dir)
	{
		get_ray_to_axis_distance(&ray);
		move_ray_to_next_axis(&ray);
		check_axis_is_wall_collision(&ray, &(game->scene));
	}
	ray.length = get_ray_length(ray);
	return (ray);
}

double	get_ray_length(t_ray ray)
{
	double	size_x;
	double	size_y;

	size_x = ray.start_pos.x - ray.end_pos.x;
	size_y = ray.start_pos.y - ray.end_pos.y;
	return (sqrt(size_x * size_x + size_y * size_y));
}
