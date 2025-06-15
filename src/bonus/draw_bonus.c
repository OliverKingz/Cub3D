/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozamora- <ozamora-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 19:11:12 by raperez-          #+#    #+#             */
/*   Updated: 2025/06/15 15:31:30 by ozamora-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

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
	int	x;
	int	y;

	x = 0;
	while (x < WIDTH)
	{
		y = 0;
		while (y < HEIGHT / 2)
		{
			mlx_put_pixel(game->graphs.screen, x, y, game->scene.ceil_rgb);
			y++;
		}
		while (y < HEIGHT)
		{
			mlx_put_pixel(game->graphs.screen, x, y, game->scene.floor_rgb);
			y++;
		}
		x++;
	}
}

void	draw_player_bg(t_game *game)
{
	draw_rectangle(game->graphs.player, (t_point){0, 0},
		(t_point){game->scene.w_mmap, game->scene.h_mmap}, CLEAR);
}
