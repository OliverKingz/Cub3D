/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozamora- <ozamora-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 18:42:36 by ozamora-          #+#    #+#             */
/*   Updated: 2025/06/10 01:39:50 by ozamora-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_map_bg(t_game *game)
{
	int	y;
	int	x;

	y = 0;
	while (y < game->scene.h_mmap)
	{
		x = 0;
		while (x < game->scene.w_mmap)
		{
			mlx_put_pixel(game->graphs.minimap, x, y, MMAP_EMPTY_COLOR);
			x++;
		}
		y++;
	}
}

void	draw_fill_tile(t_game *game, int x, int y, int color)
{
	int	py;
	int	px;

	py = y * MMAP_TILE;
	while (py < (y + 1) * MMAP_TILE)
	{
		px = x * MMAP_TILE;
		while (px < (x + 1) * MMAP_TILE)
		{
			if (px >= 0 && px < MMAP_TILE * game->scene.width_map && py >= 0
				&& py < MMAP_TILE * game->scene.height_map)
				mlx_put_pixel(game->graphs.minimap, px, py, color);
			px++;
		}
		py++;
	}
}

void	draw_minimap_tiles(t_game *game)
{
	int	y;
	int	x;

	y = 0;
	while (y < game->scene.height_map)
	{
		x = 0;
		while (x < game->scene.width_map)
		{
			if (game->scene.map2d[y][x] == WALL)
				draw_rectangle(game->graphs.minimap, (t_point){x * MMAP_TILE, y
					* MMAP_TILE}, (t_point){MMAP_TILE, MMAP_TILE},
					MMAP_WALL_COLOR);
			else
				draw_rectangle(game->graphs.minimap, (t_point){x * MMAP_TILE, y
					* MMAP_TILE}, (t_point){MMAP_TILE, MMAP_TILE},
					MMAP_EMPTY_COLOR);
			x++;
		}
		y++;
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
