/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_torch_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozamora- <ozamora-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 16:07:30 by ozamora-          #+#    #+#             */
/*   Updated: 2025/06/15 23:50:19 by ozamora-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// # include "cub3d_bonus.h"

// void init_torch_textures(t_game *game)
// {
	// game->graphs.torch_t[0] = mlx_load_png("./assets/textures/torch1.png");
	// game->graphs.torch_t[1] = mlx_load_png("./assets/textures/torch2.png");
	// game->graphs.torch_t[2] = mlx_load_png("./assets/textures/torch3.png");
	// game->graphs.torch_t[3] = mlx_load_png("./assets/textures/torch4.png");
	// game->graphs.torch_t[4] = mlx_load_png("./assets/textures/torch5.png");
	// game->graphs.torch_t[5] = mlx_load_png("./assets/textures/torch6.png");
	// game->graphs.torch_t[6] = mlx_load_png("./assets/textures/torch7.png");
	// game->graphs.torch_t[7] = mlx_load_png("./assets/textures/torch8.png");
	// if (!game->graphs.torch_t[0] || !game->graphs.torch_t[1]
	// 	|| !game->graphs.torch_t[2] || !game->graphs.torch_t[3]
	// 	|| !game->graphs.torch_t[4] || !game->graphs.torch_t[5]
	// 	|| !game->graphs.torch_t[6] || !game->graphs.torch_t[7])
	// 	my_mlx_err(game, "Failed loading torch textures");
// }

// void draw_torch(t_game *game)
// {
// 	static int	frame = 0;
// 	t_point pos;

// 	pos.x = WIDTH - (game->graphs.torch_t[0]->width);
// 	pos.y = HEIGHT - (game->graphs.torch_t[0]->height);
// 	game->graphs.torch = mlx_texture_to_image(game->mlx, game->graphs.torch_t[frame]);
// 	mlx_image_to_window(game->mlx, game->graphs.torch, pos.x, pos.y);
// 	frame = (frame + 1) % 8;
// }