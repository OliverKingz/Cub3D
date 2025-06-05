/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozamora- <ozamora-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 18:42:36 by ozamora-          #+#    #+#             */
/*   Updated: 2025/06/05 16:15:56 by ozamora-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_map_bg(t_game *game, int mmap_width, int mmap_height)
{
	int	y;
	int	x;

	y = 0;
	while (y < mmap_height)
	{
		x = 0;
		while (x < mmap_width)
		{
			mlx_put_pixel(game->graphs.minimap, x, y, BLACK);
			x++;
		}
		y++;
	}
}

static void	fill_cell(t_game *game, int x, int y, int color)
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

static void	draw_map_cells(t_game *game)
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
				fill_cell(game, x, y, WHITE);
			else if (game->scene.map2d[y][x] == '0')
				fill_cell(game, x, y, BLACK);
			x++;
		}
		y++;
	}
}

static void	draw_map_grid(t_game *game, int mmap_width, int mmap_height)
{
	int	x;
	int	y;

	// Draw vertical lines
	x = -1;
	while (++x < mmap_width)
	{
		y = -1;
		while (++y < mmap_height)
		{
			if (x % MAP_TILE == 0)
				mlx_put_pixel(game->graphs.minimap, x, y, LIGHT_GREY);
		}
	}
	// Draw horizontal lines
	y = -1;
	while (++y < mmap_height)
	{
		x = -1;
		while (++x < mmap_width)
		{
			if (y % MAP_TILE == 0)
				mlx_put_pixel(game->graphs.minimap, x, y, LIGHT_GREY);
		}
	}
}

void	draw_player_mmap(t_game *game, int radius, int mmap_width,
		int mmap_height)
{
	int	dy;
	int	dx;
	int	draw_x;
	int	draw_y;

	game->graphs.player_mmap = mlx_new_image(game->mlx, 2 * radius, 2 * radius);
	dy = -radius;
	while (dy <= radius)
	{
		dx = -radius;
		while (dx <= radius)
		{
			if (dx * dx + dy * dy <= radius * radius)
			{
				draw_x = game->player.mmap.x + dx;
				draw_y = game->player.mmap.y + dy;
				if (draw_x >= 0 && draw_x < mmap_width 
					&& draw_y >= 0 && draw_y < mmap_height)
					mlx_put_pixel(game->graphs.minimap, draw_x, draw_y, GREEN);
			}
			dx++;
		}
		dy++;
	}
	mlx_image_to_window(game->mlx, game->graphs.player_mmap, WIDTH - 10
		- mmap_width, HEIGHT - 10 - mmap_height);
}

void	draw_minimap(t_game *game, int mmap_width, int mmap_height)
{
	game->graphs.minimap = mlx_new_image(game->mlx, mmap_width, mmap_height);
	draw_map_bg(game, mmap_width, mmap_height);
	draw_map_cells(game);
	draw_map_grid(game, mmap_width, mmap_height);
	mlx_image_to_window(game->mlx, game->graphs.minimap, WIDTH - 10
		- mmap_width, HEIGHT - 10 - mmap_height);
}
