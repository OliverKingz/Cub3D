/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   background.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozamora- <ozamora-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 19:11:12 by raperez-          #+#    #+#             */
/*   Updated: 2025/06/04 19:36:11 by ozamora-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

void	draw_minimap(t_game *game)
{
	int	x;
	int	y;
	int	mm_w;
	int	mm_h;

	mm_w = HEIGHT / 4;
	mm_h = HEIGHT / 4;
	game->graphs.minimap = mlx_new_image(game->mlx, mm_w, mm_h);
	x = 0;
	while (x < mm_w)
	{
		y = 0;
		while (y < mm_h)
		{
			mlx_put_pixel(game->graphs.minimap, x, y, 0x000000FF);
			y++;
		}
		x++;
	}
	//mlx_image_to_window(game->mlx, game->graphs.minimap, 10, 10);
	mlx_image_to_window(game->mlx, game->graphs.minimap, WIDTH - 10 - mm_w, HEIGHT - 10 - mm_h);
}
