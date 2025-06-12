/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozamora- <ozamora-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 14:35:02 by raperez-          #+#    #+#             */
/*   Updated: 2025/06/12 15:42:45 by ozamora-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_ray(t_game *game, t_ray *ray, double angle)
{
	ray->angle_rads = deg_to_rad(angle);
	ray->vector = rad_to_vector(ray->angle_rads);
	ray->start_pos.x = game->player.pos.x;
	ray->start_pos.y = game->player.pos.y;
	ray->end_pos.x = game->player.pos.x;
	ray->end_pos.y = game->player.pos.y;
	ray->collision_dir = NONE;
	get_delta(ray);
	if (ray->vector.x > 0)
		ray->step_dir.x = 1;
	else if (ray->vector.x < 0)
		ray->step_dir.x = -1;
	else
		ray->step_dir.x = 0;
	if (ray->vector.y > 0)
		ray->step_dir.y = 1;
	else if (ray->vector.y < 0)
		ray->step_dir.y = -1;
	else
		ray->step_dir.y = 0;
}

/**
 * Casts a ray from the player's position at a given angle using DDA.
 *
 * Initializes a ray from the player's position and steps through the map
 * grid at the given angle. Uses the DDA algorithm to find the first wall
 * collision and returns the ray with collision info and distance.
 *
 * @param game Pointer to the game state.
 * @param angle Angle (in radians) to cast the ray.
 * @return t_ray Ray info including length and collision details.
 */
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
	ray.length = get_distance_length(ray.start_pos, ray.end_pos);
	ray.corrected_len = correct_raylen_fisheye(&ray, game->player.angle);
	return (ray);
}

double	correct_raylen_fisheye(t_ray *ray, double player_angle)
{
	double	player_angle_rad;
	double	corrected;

	player_angle_rad = deg_to_rad(player_angle);
	corrected = ray->length * cos(ray->angle_rads - player_angle_rad);
	if (corrected < 0.0001)
		corrected = 0.0001;
	return (corrected);
}
