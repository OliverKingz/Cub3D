/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozamora- <ozamora-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 12:27:32 by ozamora-          #+#    #+#             */
/*   Updated: 2025/06/10 17:49:26 by ozamora-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// void	draw_minimap(t_game *game)
// {
// 	//draw_map_bg(game);
// 	draw_minimap_tiles(game);
// 	draw_minimap_grid(game);
// }

void	draw_minimap_tiles(t_game *game)
{
	int		y;
	int		x;
	t_point	tile_size;
	t_point	tile_pos;

	y = -1;
	while (++y < game->scene.height_map)
	{
		x = -1;
		while (++x < game->scene.width_map)
		{
			tile_size = (t_point){MMAP_TILE, MMAP_TILE};
			tile_pos = (t_point){x * MMAP_TILE, y * MMAP_TILE};
			if (game->scene.map2d[y][x] == WALL)
				draw_rectangle(game->graphs.minimap, tile_pos, tile_size,
					MMAP_WALL_COLOR);
			else if (game->scene.map2d[y][x] == SPACE)
				draw_rectangle(game->graphs.minimap, tile_pos, tile_size,
					CLEAR);
			else
				draw_rectangle(game->graphs.minimap, tile_pos, tile_size,
					MMAP_EMPTY_COLOR);
		}
	}
}

void	draw_minimap_grid(t_game *game)
{
	int	x;
	int	y;

	x = -1;
	while (++x < game->scene.w_mmap)
	{
		y = -1;
		while (++y < game->scene.h_mmap)
		{
			if (x % MMAP_TILE == 0)
				mlx_put_pixel(game->graphs.minimap, x, y, MMAP_GRID_COLOR);
		}
	}
	y = -1;
	while (++y < game->scene.h_mmap)
	{
		x = -1;
		while (++x < game->scene.w_mmap)
		{
			if (y % MMAP_TILE == 0)
				mlx_put_pixel(game->graphs.minimap, x, y, MMAP_GRID_COLOR);
		}
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
