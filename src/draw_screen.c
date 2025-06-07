/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_screen.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozamora- <ozamora-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 12:25:19 by ozamora-          #+#    #+#             */
/*   Updated: 2025/06/07 12:30:48 by ozamora-         ###   ########.fr       */
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

void	draw_rectangle(mlx_image_t *img, int x, int y, int height)
{
	int j;
	int	width;

	width = x + WIDTH / FOV;
	height += y;
	while (x < width)
	{
		j = y;
		while (j < height)
		{
			if (j >= 0 && j < HEIGHT)
				mlx_put_pixel(img, x, j, GREEN);
			j++;
		} 
		x++;
	}
}
