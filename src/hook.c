/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozamora- <ozamora-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 19:13:36 by ozamora-          #+#    #+#             */
/*   Updated: 2025/06/06 17:41:25 by ozamora-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	key_hook(mlx_key_data_t keydata, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)
	{
		if (keydata.key == MLX_KEY_ESCAPE)
			close_hook(game);
		if (keydata.key == MLX_KEY_W)
			move(game, 0, -1, 0);
		if (keydata.key == MLX_KEY_S)
			move(game, 0, 1, 0);
		if (keydata.key == MLX_KEY_A)
			move(game, -1, 0, 0);
		if (keydata.key == MLX_KEY_D)
			move(game, 1, 0, 0);
		if (keydata.key == MLX_KEY_LEFT)
			move(game, 0, 0, -1);
		if (keydata.key == MLX_KEY_RIGHT)
			move(game, 0, 0, 1);
	}
}

void	close_hook(void *param)
{
	t_game	*game;

	game = param;
	mlx_close_window(game->mlx);
	//free_game(game);
}
