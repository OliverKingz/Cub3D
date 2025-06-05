/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozamora- <ozamora-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 19:11:12 by raperez-          #+#    #+#             */
/*   Updated: 2025/06/05 15:23:01 by ozamora-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_game(t_game *game)
{
	draw_bg(game);
	// draw_walls(game); //AKA draw textures
	draw_minimap(game);
}


void	draw_bg(t_game *game)
{
	int	x;
	int	y;

	game->graphs.bg = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	x = 0;
	while (x < WIDTH)
	{
		y = 0;
		while (y < HEIGHT / 2)
		{
			mlx_put_pixel(game->graphs.bg, x, y, LIGHT_BLUE);
			y++;
		}
		while (y < HEIGHT)
		{
			mlx_put_pixel(game->graphs.bg, x, y, DARK_GREY);
			y++;
		}
		x++;
	}
	mlx_image_to_window(game->mlx, game->graphs.bg, 0, 0);
}
