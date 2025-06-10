/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_screen.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozamora- <ozamora-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 12:25:19 by ozamora-          #+#    #+#             */
/*   Updated: 2025/06/10 00:57:47 by ozamora-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
