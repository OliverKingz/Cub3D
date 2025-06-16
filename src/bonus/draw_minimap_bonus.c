/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozamora- <ozamora-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 12:27:32 by ozamora-          #+#    #+#             */
/*   Updated: 2025/06/16 15:56:55 by ozamora-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	draw_minimap_tiles(t_game *game)
{
	t_point	pos;
	t_point	tile_size;
	t_point	tile_pos;
	int		color;

	pos.y = -1;
	while (++pos.y < game->scene.height_map)
	{
		pos.x = -1;
		while (++pos.x < game->scene.width_map)
		{
			tile_size = (t_point){MMAP_TILE, MMAP_TILE};
			tile_pos = (t_point){pos.x * MMAP_TILE, pos.y * MMAP_TILE};
			color = MMAP_EMPTY_COLOR;
			if (game->scene.map2d[(int)pos.y][(int)pos.x] == WALL)
				color = MMAP_WALL_COLOR;
			else if (ft_strchr("Dd", game->scene.map2d[(int)pos.y][(int)pos.x]))
				color = MMAP_DOOR_COLOR;
			else if (game->scene.map2d[(int)pos.y][(int)pos.x] == SPACE)
				continue ;
			draw_rectangle(game->graphs.minimap, tile_pos, tile_size, color);
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

void	draw_player(t_game *game)
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
					mlx_put_pixel(game->graphs.player, draw_x, draw_y,
						MMAP_PLAYER_COLOR);
			}
			dx++;
		}
		dy++;
	}
}
