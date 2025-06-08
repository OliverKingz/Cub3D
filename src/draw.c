/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozamora- <ozamora-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 19:11:12 by raperez-          #+#    #+#             */
/*   Updated: 2025/06/08 14:07:18 by ozamora-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_frame(t_game *game)
{
	draw_screen_bg(game);
	draw_minimap(game);
	draw_walls_and_rays(game);
	draw_player_mmap(game);
}

static double	fisheye_correction_ray_size(double ray_angle,
		double player_angle, double ray_size)
{
	double	ray_angle_rad;
	double	player_angle_rad;
	double	corrected;

	ray_angle_rad = degrees_to_radians(ray_angle);
	player_angle_rad = degrees_to_radians(player_angle);
	corrected = ray_size * cos(ray_angle_rad - player_angle_rad);
	if (corrected < 0.0001)
		corrected = 0.0001;
	return (corrected);
}

void	draw_walls_and_rays(t_game *game)
{
	double	ray_angle;
	int		wall_x;
	int		wall_height;
	t_ray	ray;
	double	corrected_dist;

	ray_angle = game->player.angle - FOV / 2;
	wall_x = 0;
	while (ray_angle < game->player.angle + FOV / 2)
	{
		ray = launch_ray(game, ray_angle);
		draw_ray(game->graphs.minimap, ray, MMAP_TILE);
		corrected_dist = fisheye_correction_ray_size(ray_angle,
				game->player.angle, ray.size);
		wall_height = HEIGHT / corrected_dist;
		draw_rectangle(game->graphs.screen, wall_x, (HEIGHT / 2) - (wall_height
				/ 2), wall_height);
		wall_x += WIDTH / FOV;
		ray_angle += 1;
	}
}
