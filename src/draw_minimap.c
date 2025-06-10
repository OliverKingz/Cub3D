/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozamora- <ozamora-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 12:27:32 by ozamora-          #+#    #+#             */
/*   Updated: 2025/06/11 00:16:42 by ozamora-         ###   ########.fr       */
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
				continue ;
			else
				draw_rectangle(game->graphs.minimap, tile_pos, tile_size,
					MMAP_EMPTY_COLOR);
		}
	}
}

void	draw_minimap_grid_vertical(t_game *game)
{
	int	x;
	int	y;
	int	tile_x;

	x = 0;
	tile_x = 0;
	while (tile_x < game->scene.width_map)
	{
		x = tile_x * MMAP_TILE;
		if (x >= game->scene.w_mmap)
			break ;
		y = 0;
		while (y < game->scene.h_mmap && y < MMAP_TILE * game->scene.height_map)
		{
			if (game->scene.map2d[y / MMAP_TILE][tile_x] != SPACE)
				mlx_put_pixel(game->graphs.minimap, x, y, MMAP_GRID_COLOR);
			y++;
		}
		tile_x++;
	}
}

void	draw_minimap_grid_horizontal(t_game *game)
{
	int	y;
	int	x;
	int	tile_y;

	y = 0;
	tile_y = 0;
	while (tile_y < game->scene.height_map)
	{
		y = tile_y * MMAP_TILE;
		if (y >= game->scene.h_mmap)
			break ;
		x = 0;
		while (x < game->scene.w_mmap && x < MMAP_TILE * game->scene.width_map)
		{
			if (game->scene.map2d[tile_y][x / MMAP_TILE] != SPACE)
				mlx_put_pixel(game->graphs.minimap, x, y, MMAP_GRID_COLOR);
			x++;
		}
		tile_y++;
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
