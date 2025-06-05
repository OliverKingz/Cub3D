/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozamora- <ozamora-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 19:52:22 by ozamora-          #+#    #+#             */
/*   Updated: 2025/06/05 15:18:12 by ozamora-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_game	init_game(t_game *game, const char *scene_dir)
{
	init_scene(game, scene_dir);
	init_mlx(game);
	init_images(game);
	game->is_running = true;
	return (*game);
}

void	init_images(t_game *game)
{
	game->graphs.east = mlx_texture_to_image(game->mlx, game->graphs.east_t);
	game->graphs.north = mlx_texture_to_image(game->mlx, game->graphs.north_t);
	game->graphs.south = mlx_texture_to_image(game->mlx, game->graphs.south_t);
	game->graphs.west = mlx_texture_to_image(game->mlx, game->graphs.west_t);
	if (!game->graphs.east || !game->graphs.north || !game->graphs.south
		|| !game->graphs.west)
		ft_mlx_err(FAIL_IMAGES);
}

void	init_mlx(t_game *game)
{
	mlx_set_setting(MLX_STRETCH_IMAGE, true);
	game->mlx = mlx_init(WIDTH, HEIGHT, "Cub3D", true);
	if (!game->mlx)
		ft_mlx_err(FAIL_MLX);
	mlx_set_window_size(game->mlx, WIDTH * 2, HEIGHT * 2);
	mlx_set_icon(game->mlx, game->graphs.icon_t);
	mlx_set_window_limit(game->mlx, WIDTH / 5, HEIGHT / 5, WIDTH * 3, HEIGHT * 3);
}
