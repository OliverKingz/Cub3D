/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozamora- <ozamora-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 19:38:28 by ozamora-          #+#    #+#             */
/*   Updated: 2025/06/15 15:32:04 by ozamora-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int32_t	main(int argc, char **argv)
{
	t_game	game;

	if (argc == 2)
	{
		if (ft_strlen(argv[1]) == 0)
			my_mlx_err(NULL, SCENE_EMPTY_ARG);
		game = init_game(&game, argv[1]);
		if (game.is_running == true)
		{
			mlx_key_hook(game.mlx, &key_hook, &game);
			mlx_close_hook(game.mlx, close_hook, &game);
			mlx_loop_hook(game.mlx, &loop_hook, &game);
			mlx_loop(game.mlx);
		}
		mlx_terminate(game.mlx);
	}
	else
		my_mlx_err(NULL, USAGE);
	return (EXIT_SUCCESS);
}
