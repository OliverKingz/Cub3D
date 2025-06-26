/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_torch_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozamora- <ozamora-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 16:07:30 by ozamora-          #+#    #+#             */
/*   Updated: 2025/06/26 22:52:32 by ozamora-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	init_torch_textures(t_game *game)
{
	game->graphs.torch_t[0] = mlx_load_png("./assets/textures/torch-1.png");
	game->graphs.torch_t[1] = mlx_load_png("./assets/textures/torch-2.png");
	game->graphs.torch_t[2] = mlx_load_png("./assets/textures/torch-3.png");
	game->graphs.torch_t[3] = mlx_load_png("./assets/textures/torch-4.png");
	game->graphs.torch_t[4] = mlx_load_png("./assets/textures/torch-5.png");
	game->graphs.torch_t[5] = mlx_load_png("./assets/textures/torch-6.png");
	game->graphs.torch_t[6] = mlx_load_png("./assets/textures/torch-7.png");
	game->graphs.torch_t[7] = mlx_load_png("./assets/textures/torch-8.png");
	if (!game->graphs.torch_t[0] || !game->graphs.torch_t[1]
		|| !game->graphs.torch_t[2] || !game->graphs.torch_t[3]
		|| !game->graphs.torch_t[4] || !game->graphs.torch_t[5]
		|| !game->graphs.torch_t[6] || !game->graphs.torch_t[7])
		my_mlx_err(game, FAIL_TEXTURE);
}

void	draw_torch(t_game *game)
{
	static double	frame = 0;
	t_point			pos;

	pos.x = WIDTH - (game->graphs.torch_t[0]->width * 6.5) - 100;
	pos.y = HEIGHT - (game->graphs.torch_t[0]->height * 6.5) + 60;
	my_delete_image(game->mlx, game->graphs.torch);
	game->graphs.torch = mlx_texture_to_image(game->mlx,
			game->graphs.torch_t[(int)frame]);
	mlx_image_to_window(game->mlx, game->graphs.torch, pos.x, pos.y);
	mlx_resize_image(game->graphs.torch, game->graphs.torch_t[0]->width * 6.5,
		game->graphs.torch_t[0]->height * 6.5);
	frame = (frame + 0.3);
	if (frame > 8.0)
		frame = 0.0;
	game->graphs.torch->enabled = true;
}
