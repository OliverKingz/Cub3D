/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozamora- <ozamora-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 17:35:09 by ozamora-          #+#    #+#             */
/*   Updated: 2025/06/06 18:49:21 by ozamora-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move(t_game *game, int dx, int dy, int dang)
{
	t_point new_pos;
	
	new_pos.x = game->player.pos.x + (dx * SPEED);
	new_pos.y = game->player.pos.y + (dy * SPEED);

	if (new_pos.x < 0 || new_pos.x >= game->scene.width_map
		|| new_pos.y < 0 || new_pos.y >= game->scene.height_map)
		return ;
	if (game->scene.map2d[(int)new_pos.y][(int)new_pos.x] == '1')
		return ;
	if (game->is_running == true)
	{
		game->player.pos.x = new_pos.x;
		game->player.pos.y = new_pos.y;
		game->player.mmap.x = game->player.pos.x * MAP_TILE;
		game->player.mmap.y = game->player.pos.y * MAP_TILE;
		game->player.angle = game->player.angle + (dang * ANGLE_SPEED);
		draw_bg(game);
		draw_minimap(game);
		draw_walls_and_rays(game);
		draw_player_mmap(game);
	}
}
