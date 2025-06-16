/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_scene_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozamora- <ozamora-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 15:07:34 by ozamora-          #+#    #+#             */
/*   Updated: 2025/06/16 15:58:15 by ozamora-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

t_game	init_scene(t_game *game, const char *scene_dir)
{
	parser(game, scene_dir);
	init_texture(game);
	init_remaining_map_vars(game);
	return (*game);
}

void	init_player(t_game *game, char angle, double x, double y)
{
	if (angle == EA_PLAYER)
		game->player.angle = 0;
	else if (angle == SO_PLAYER)
		game->player.angle = 90;
	else if (angle == WE_PLAYER)
		game->player.angle = 180;
	else if (angle == NO_PLAYER)
		game->player.angle = 270;
	game->player.pos.x = x;
	game->player.pos.y = y;
	game->player.mmap.x = game->player.pos.x * MMAP_TILE;
	game->player.mmap.y = game->player.pos.y * MMAP_TILE;
}

void	init_remaining_map_vars(t_game *game)
{
	game->scene.ratio_map = (double)game->scene.width_map
		/ (double)game->scene.height_map;
	game->scene.h_mmap = game->scene.height_map * MMAP_TILE;
	game->scene.w_mmap = game->scene.width_map * MMAP_TILE;
	if (game->scene.w_mmap > WIDTH - 20 || game->scene.h_mmap > HEIGHT - 20)
		return (my_err_clean(game, FAIL_MINIMAP_TOO_BIG, false));
}
