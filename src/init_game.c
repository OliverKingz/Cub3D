/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raperez- <raperez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 19:52:22 by ozamora-          #+#    #+#             */
/*   Updated: 2025/06/07 11:54:25 by raperez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_game	init_game(t_game *game, const char *scene_dir)
{
	ft_memset((void *)game, 0, sizeof(t_game));
	init_scene(game, scene_dir);
	init_mlx(game);
	init_images(game);
	game->is_running = true;
	init_draw_to_window(game);
	return (*game);
}

void	init_images(t_game *game)
{
	game->graphs.east = mlx_texture_to_image(game->mlx, game->graphs.east_t);
	game->graphs.north = mlx_texture_to_image(game->mlx, game->graphs.north_t);
	game->graphs.south = mlx_texture_to_image(game->mlx, game->graphs.south_t);
	game->graphs.west = mlx_texture_to_image(game->mlx, game->graphs.west_t);

	game->graphs.screen = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	game->graphs.minimap = mlx_new_image(game->mlx, game->scene.w_mmap, game->scene.h_mmap);

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
	mlx_set_window_limit(game->mlx, WIDTH / 3, HEIGHT / 3, WIDTH * 5, HEIGHT * 5);
}
