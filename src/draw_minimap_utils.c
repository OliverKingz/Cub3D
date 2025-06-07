/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozamora- <ozamora-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 18:42:36 by ozamora-          #+#    #+#             */
/*   Updated: 2025/06/08 01:36:00 by ozamora-         ###   ########.fr       */
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
			mlx_put_pixel(game->graphs.minimap, x, y, BLACK);
			x++;
		}
		y++;
	}
}

void	draw_fill_tile(t_game *game, int x, int y, int color)
{
	int	py;
	int	px;

	py = y * MAP_TILE;
	while (py < (y + 1) * MAP_TILE)
	{
		px = x * MAP_TILE;
		while (px < (x + 1) * MAP_TILE)
		{
			if (px >= 0 && px < MAP_TILE * game->scene.width_map && py >= 0
				&& py < MAP_TILE * game->scene.height_map)
				mlx_put_pixel(game->graphs.minimap, px, py, color);
			px++;
		}
		py++;
	}
}

void	draw_map_all_tiles(t_game *game)
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
				draw_fill_tile(game, x, y, WHITE);
			else if (game->scene.map2d[y][x] == EMPTY)
				draw_fill_tile(game, x, y, BLACK);
			x++;
		}
		y++;
	}
}

void	draw_map_grid(t_game *game)
{
	int	x;
	int	y;

	// Draw vertical lines
	x = -1;
	while (++x < game->scene.w_mmap)
	{
		y = -1;
		while (++y < game->scene.h_mmap)
		{
			if (x % MAP_TILE == 0)
				mlx_put_pixel(game->graphs.minimap, x, y, LIGHT_GREY);
		}
	}
	// Draw horizontal lines
	y = -1;
	while (++y < game->scene.h_mmap)
	{
		x = -1;
		while (++x < game->scene.w_mmap)
		{
			if (y % MAP_TILE == 0)
				mlx_put_pixel(game->graphs.minimap, x, y, LIGHT_GREY);
		}
	}
}

