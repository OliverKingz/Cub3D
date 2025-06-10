/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozamora- <ozamora-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 15:07:34 by ozamora-          #+#    #+#             */
/*   Updated: 2025/06/10 18:03:19 by ozamora-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_game	init_scene(t_game *game, const char *scene_dir)
{
	read_file(game, scene_dir);
	init_texture(game, scene_dir);
	init_map(game, scene_dir);
	init_player(game, scene_dir);
	return (*game);
}

void	init_texture(t_game *game, const char *scene_dir)
{
	(void)scene_dir;

	game->graphs.icon_t = mlx_load_png("./assets/textures/cub3de.png");
	game->graphs.east_t = mlx_load_png(game->graphs.east_path);
	game->graphs.north_t = mlx_load_png(game->graphs.north_path);
	game->graphs.south_t = mlx_load_png(game->graphs.south_path);
	game->graphs.west_t = mlx_load_png(game->graphs.west_path);
	if (!game->graphs.icon_t || !game->graphs.north_t || !game->graphs.south_t
		|| !game->graphs.east_t || !game->graphs.west_t)
		ft_mlx_err(FAIL_TEXTURE);
}

void	init_player(t_game *game, const char *scene_dir)
{
	(void)scene_dir;
	game->player.angle = 0;
	game->player.pos.x = 1.5;
	game->player.pos.y = 2.5;
	game->player.mmap.x = game->player.pos.x * MMAP_TILE;
	game->player.mmap.y = game->player.pos.y * MMAP_TILE;
}

void	init_map(t_game *game, const char *scene_dir)
{
	(void)scene_dir;
	// Mapa 8x5
	game->scene.map1d = ft_strdup("11111111 11010001 1000N001 10000101 11111111");
	game->scene.map2d = ft_split(game->scene.map1d, ' ');
	game->scene.width_map = 8;
	game->scene.height_map = 5;
	game->scene.ratio_map = (double)game->scene.width_map
		/ (double)game->scene.height_map;

	// Mapa 16x6
	// game->scene.map1d = ft_strdup("1111111111111111 1000000000000001 1000000000000001 1000N00000000001 1000000000000001 1111111111111111");
	// game->scene.map2d = ft_split(game->scene.map1d, ' ');
	// game->scene.width_map = 16;
	// game->scene.height_map = 6;
	// game->scene.ratio_map = (double)game->scene.width_map / (double)game->scene.height_map;
	// game->scene.ceil_rgb = LIGHT_BLUE;
	// game->scene.floor_rgb = DARK_GREY;
	game->scene.h_mmap = game->scene.height_map * MMAP_TILE;
	game->scene.w_mmap = game->scene.width_map * MMAP_TILE;
	if (game->scene.w_mmap > WIDTH - 20 || game->scene.h_mmap > HEIGHT - 20)
		return (free_game(game), ft_mlx_err(FAIL_MINIMAP_TOO_BIG));
}
