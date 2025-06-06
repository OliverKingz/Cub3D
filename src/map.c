/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozamora- <ozamora-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 18:42:36 by ozamora-          #+#    #+#             */
/*   Updated: 2025/06/06 18:25:04 by ozamora-         ###   ########.fr       */
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

void	draw_fill_cell(t_game *game, int x, int y, int color)
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

void	draw_map_cells(t_game *game)
{
	int	y;
	int	x;

	// Draw map cells: fill white if '1'
	y = 0;
	while (y < game->scene.height_map)
	{
		x = 0;
		while (x < game->scene.width_map)
		{
			if (game->scene.map2d[y][x] == '1')
				draw_fill_cell(game, x, y, WHITE);
			else if (game->scene.map2d[y][x] == '0')
				draw_fill_cell(game, x, y, BLACK);
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
	mlx_image_to_window(game->mlx, game->graphs.player_mmap, WIDTH - 10
		- game->scene.w_mmap, HEIGHT - 10 - game->scene.h_mmap);
}

void	draw_minimap(t_game *game)
{
	draw_map_bg(game);
	draw_map_cells(game);
	draw_map_grid(game);
	mlx_image_to_window(game->mlx, game->graphs.minimap, WIDTH - 10
		- game->scene.w_mmap, HEIGHT - 10 - game->scene.h_mmap);
}
