/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozamora- <ozamora-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 19:13:36 by ozamora-          #+#    #+#             */
/*   Updated: 2025/06/06 21:42:14 by ozamora-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	key_hook(mlx_key_data_t keydata, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (keydata.action == MLX_PRESS)
	{
		if (keydata.key == MLX_KEY_ESCAPE)
			close_hook(game);
		if (keydata.key == MLX_KEY_W)
			(printf("Pressed W "), move(game, 0, -1, 0));
		if (keydata.key == MLX_KEY_S)
			(printf("Pressed S "), move(game, 0, 1, 0));
		if (keydata.key == MLX_KEY_A)
			(printf("Pressed A "), move(game, -1, 0, 0));
		if (keydata.key == MLX_KEY_D)
			(printf("Pressed D "), move(game, 1, 0, 0));
		if (keydata.key == MLX_KEY_LEFT)
			(printf("Pressed <- "), move(game, 0, 0, -1));
		if (keydata.key == MLX_KEY_RIGHT)
			(printf("Pressed -> "), move(game, 0, 0, 1));
	}
}

void	close_hook(void *param)
{
	t_game	*game;

	game = param;
	mlx_close_window(game->mlx);
	free_game(game);
}
