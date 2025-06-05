/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raperez- <raperez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 19:38:28 by ozamora-          #+#    #+#             */
/*   Updated: 2025/06/05 16:01:49 by raperez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int32_t	main(int argc, char **argv)
{
	t_game	game;

	if (argc == 2)
	{
		if (ft_strlen(argv[1]) == 0)
			ft_mlx_err(SCENE_EMPTY);
		game = init_game(&game, argv[1]);
		draw_game(&game);
		if (game.is_running == true)
		{
			mlx_key_hook(game.mlx, &key_hook, &game);
			mlx_close_hook(game.mlx, close_hook, &game);
			mlx_loop(game.mlx);
		}
		mlx_terminate(game.mlx);
	}
	else
		ft_mlx_err(USAGE);
	return (EXIT_SUCCESS);
}
