/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozamora- <ozamora-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 19:52:22 by ozamora-          #+#    #+#             */
/*   Updated: 2025/06/15 23:40:11 by ozamora-         ###   ########.fr       */
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
	print_debug_info(game);
	return (*game);
}

void	init_mlx(t_game *game)
{
	mlx_set_setting(MLX_STRETCH_IMAGE, true);
	game->mlx = mlx_init(WIDTH, HEIGHT, "Cub3D", true);
	if (!game->mlx)
		my_mlx_err(game, FAIL_MLX);
	mlx_set_window_pos(game->mlx, 0, 0);
	mlx_set_icon(game->mlx, game->graphs.icon_t);
	mlx_set_window_limit(game->mlx, WIDTH / 2, HEIGHT / 2, WIDTH * 3, HEIGHT
		* 3);
}

void	init_images(t_game *game)
{
	game->graphs.screen = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	if (!game->graphs.screen)
		my_mlx_err(game, FAIL_IMAGES);
	if (USE_MINIMAP)
	{
		game->graphs.minimap = mlx_new_image(game->mlx, game->scene.w_mmap,
				game->scene.h_mmap);
		game->graphs.player = mlx_new_image(game->mlx, game->scene.w_mmap,
				game->scene.h_mmap);
		if (!game->graphs.minimap || !game->graphs.player)
			my_mlx_err(game, FAIL_IMAGES);
	}
}

void	init_draw_to_window(t_game *game)
{
	if (USE_MINIMAP)
	{
		draw_minimap_tiles(game);
		draw_minimap_grid_vertical(game);
		draw_minimap_grid_horizontal(game);
	}
	draw_frame(game);
	mlx_image_to_window(game->mlx, game->graphs.screen, 0, 0);
	if (USE_MINIMAP)
	{
		mlx_image_to_window(game->mlx, game->graphs.minimap, WIDTH - 10
			- game->scene.w_mmap, HEIGHT - 10 - game->scene.h_mmap);
		mlx_image_to_window(game->mlx, game->graphs.player, WIDTH - 10
			- game->scene.w_mmap, HEIGHT - 10 - game->scene.h_mmap);
	}
}
