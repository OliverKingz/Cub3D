/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozamora- <ozamora-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 19:11:12 by raperez-          #+#    #+#             */
/*   Updated: 2025/06/16 18:18:07 by ozamora-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_frame(t_game *game)
{
	draw_screen_bg(game);
	if (USE_MINIMAP)
		draw_player_bg(game);
	draw_walls_and_rays(game);
	if (USE_MINIMAP)
		draw_player(game);
}

void	draw_screen_bg(t_game *game)
{
	draw_rectangle(game->graphs.screen, (t_point){0, 0},
		(t_point){WIDTH, HEIGHT / 2}, game->scene.ceil_rgb);
	draw_rectangle(game->graphs.screen, (t_point){0, HEIGHT / 2},
		(t_point){WIDTH, HEIGHT}, game->scene.floor_rgb);
}

void	draw_player_bg(t_game *game)
{
	draw_rectangle(game->graphs.player, (t_point){0, 0},
		(t_point){game->scene.w_mmap, game->scene.h_mmap}, CLEAR);
}
