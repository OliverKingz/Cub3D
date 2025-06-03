/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozamora- <ozamora-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 19:13:36 by ozamora-          #+#    #+#             */
/*   Updated: 2025/06/03 20:36:39 by ozamora-         ###   ########.fr       */
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
			printf("W\n");
		if (keydata.key == MLX_KEY_S)
			printf("S\n");
		if (keydata.key == MLX_KEY_A)
			printf("A\n");
		if (keydata.key == MLX_KEY_D)
			printf("D\n");
		if (keydata.key == MLX_KEY_LEFT)
			printf("<--\n");
		if (keydata.key == MLX_KEY_RIGHT)
			printf("-->\n");
	}
}

void	close_hook(void *param)
{
	t_game	*game;

	game = param;
	mlx_close_window(game->mlx);
	//free_game(game);
}
