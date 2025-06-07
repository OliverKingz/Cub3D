/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozamora- <ozamora-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 12:27:32 by ozamora-          #+#    #+#             */
/*   Updated: 2025/06/07 12:32:51 by ozamora-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_minimap(t_game *game)
{
	draw_map_bg(game);
	draw_map_cells(game);
	draw_map_grid(game);
}

void	draw_ray(mlx_image_t *img, t_ray ray, int mult)
{
	int	x;
	int	y;

	ray.start_point.x *= mult;
	ray.start_point.y *= mult;
	ray.pos.x *= mult;
	ray.pos.y *= mult;
	x = ray.start_point.x;
	while ((ray.vector.x > 0 && x <= ray.pos.x) || (ray.vector.x < 0 && x >= ray.pos.x))
	{
		if (cos(ray.angle_radians) != 0)
		{
			y = tan(ray.angle_radians)*(x - ray.start_point.x) + ray.start_point.y;
			mlx_put_pixel(img, x, y, BLUE);
			//printf("(%d, %d)\n", x, y);
		}
		x += ray.step.x;
	}
	y = ray.start_point.y;
	while ((ray.vector.y > 0 && y <= ray.pos.y) || (ray.vector.y < 0 && y >= ray.pos.y))
	{
		if (cos(ray.angle_radians) != 0 && tan(ray.angle_radians) != 0)
		{
			x = ((y - ray.start_point.y) / tan(ray.angle_radians)) + ray.start_point.x;
			mlx_put_pixel(img, x, y, BLUE);
			//printf("(%d, %d)\n", x, y);
		}
		y += ray.step.y;
	}
}

void	draw_player_mmap(t_game *game)
{
	int	dy;
	int	dx;
	int	draw_x;
	int	draw_y;

	dy = -PMAP_RADIUS;
	while (dy <= PMAP_RADIUS)
	{
		dx = -PMAP_RADIUS;
		while (dx <= PMAP_RADIUS)
		{
			if (dx * dx + dy * dy <= PMAP_RADIUS * PMAP_RADIUS)
			{
				draw_x = game->player.mmap.x + dx;
				draw_y = game->player.mmap.y + dy;
				if (draw_x >= 0 && draw_x < game->scene.w_mmap && draw_y >= 0
					&& draw_y < game->scene.h_mmap)
					mlx_put_pixel(game->graphs.minimap, draw_x, draw_y, GREEN);
			}
			dx++;
		}
		dy++;
	}
}
