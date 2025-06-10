/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozamora- <ozamora-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 12:27:32 by ozamora-          #+#    #+#             */
/*   Updated: 2025/06/10 01:36:22 by ozamora-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// void	draw_minimap(t_game *game)
// {
// 	//draw_map_bg(game);
// 	draw_minimap_tiles(game);
// 	draw_minimap_grid(game);
// }

void	draw_ray(mlx_image_t *img, t_ray ray, int mult)
{
	double	x;
	double	y;

	x = ray.start_point.x;
	while ((ray.vector.x > 0 && x <= ray.pos.x) 
		|| (ray.vector.x < 0 && x >= ray.pos.x))
	{
		if (cos(ray.angle_radians) != 0)
		{
			y = tan(ray.angle_radians) * (x - ray.start_point.x)
				+ ray.start_point.y;
			mlx_put_pixel(img, x * mult, y * mult, MMAP_RAY_COLOR);
		}
		x += ray.step.x * 0.02;
	}
	y = ray.start_point.y;
	while ((ray.vector.y > 0 && y <= ray.pos.y) 
		|| (ray.vector.y < 0 && y >= ray.pos.y))
	{
		if (cos(ray.angle_radians) != 0 && tan(ray.angle_radians) != 0)
		{
			x = ((y - ray.start_point.y) / tan(ray.angle_radians))
				+ ray.start_point.x;
			mlx_put_pixel(img, x * mult, y * mult, MMAP_RAY_COLOR);
		}
		y += ray.step.y * 0.02;
	}
}

void	draw_minimap_player(t_game *game)
{
	int	dy;
	int	dx;
	int	draw_x;
	int	draw_y;

	dy = -MMAP_PLAYER_RADIUS;
	while (dy <= MMAP_PLAYER_RADIUS)
	{
		dx = -MMAP_PLAYER_RADIUS;
		while (dx <= MMAP_PLAYER_RADIUS)
		{
			if (dx * dx + dy * dy <= MMAP_PLAYER_RADIUS * MMAP_PLAYER_RADIUS)
			{
				draw_x = game->player.mmap.x + dx;
				draw_y = game->player.mmap.y + dy;
				if (draw_x >= 0 && draw_x < game->scene.w_mmap && draw_y >= 0
					&& draw_y < game->scene.h_mmap)
					mlx_put_pixel(game->graphs.minimap, draw_x, draw_y,
						MMAP_PLAYER_COLOR);
			}
			dx++;
		}
		dy++;
	}
}
