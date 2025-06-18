/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_torch_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozamora- <ozamora-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 16:07:30 by ozamora-          #+#    #+#             */
/*   Updated: 2025/06/19 00:28:41 by ozamora-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	init_torch_textures(t_game *game)
{
	game->graphs.torch_t[0] = mlx_load_png("./assets/textures/torch1.png");
	game->graphs.torch_t[1] = mlx_load_png("./assets/textures/torch2.png");
	game->graphs.torch_t[2] = mlx_load_png("./assets/textures/torch3.png");
	game->graphs.torch_t[3] = mlx_load_png("./assets/textures/torch4.png");
	game->graphs.torch_t[4] = mlx_load_png("./assets/textures/torch5.png");
	game->graphs.torch_t[5] = mlx_load_png("./assets/textures/torch6.png");
	game->graphs.torch_t[6] = mlx_load_png("./assets/textures/torch7.png");
	game->graphs.torch_t[7] = mlx_load_png("./assets/textures/torch8.png");
	if (!game->graphs.torch_t[0] || !game->graphs.torch_t[1]
		|| !game->graphs.torch_t[2] || !game->graphs.torch_t[3]
		|| !game->graphs.torch_t[4] || !game->graphs.torch_t[5]
		|| !game->graphs.torch_t[6] || !game->graphs.torch_t[7])
		my_mlx_err(game, FAIL_TEXTURE);
}

void	init_torch_images(t_game *game)
{
	int				i;
	t_point			pos;

	pos.x = WIDTH - (game->graphs.torch_t[0]->width * 6.5) - 100;
	pos.y = HEIGHT - (game->graphs.torch_t[0]->height * 6.5) + 60;
	i = 0;
	while (i < 8)
	{
		game->graphs.torch[i] = mlx_texture_to_image(game->mlx,
				game->graphs.torch_t[i]);
		if (!game->graphs.torch[i])
			my_mlx_err(game, FAIL_IMAGES);
		mlx_image_to_window(game->mlx, game->graphs.torch[i], pos.x, pos.y);
		mlx_resize_image(game->graphs.torch[i],
			game->graphs.torch_t[0]->width * 6.5,
			game->graphs.torch_t[0]->height * 6.5);
		game->graphs.torch[i]->enabled = false;
		i++;
	}
	game->graphs.torch_screen = game->graphs.torch[0];
}

void	draw_torch(t_game *game)
{
	static double	frame = 0;
	int				idx = ((int)frame) % 8;
	t_point			pos;

	pos.x = WIDTH - (game->graphs.torch_t[0]->width * 6.5) - 100;
	pos.y = HEIGHT - (game->graphs.torch_t[0]->height * 6.5) + 60;
	game->graphs.torch_screen->enabled = false;
	game->graphs.torch_screen = game->graphs.torch[idx];
	game->graphs.torch_screen->enabled = true;
	mlx_image_to_window(game->mlx, game->graphs.torch_screen, pos.x, pos.y);
	frame += 0.3;
	if (frame >= 8.0)
		frame = 0.0;
}
