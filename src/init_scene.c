/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raperez- <raperez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 15:07:34 by ozamora-          #+#    #+#             */
/*   Updated: 2025/06/11 16:43:11 by raperez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_game	init_scene(t_game *game, const char *scene_dir)
{
	read_file(game, scene_dir);
	init_texture(game, scene_dir);
	init_map(game, scene_dir);
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
		my_mlx_err(FAIL_TEXTURE);
}

void	init_player(t_game *game, char angle, double x, double y)
{
	if (angle == 'E')
		game->player.angle = 0;
	else if (angle == 'S')
		game->player.angle = 90;
	else if (angle == 'W')
		game->player.angle = 180;
	else if (angle == 'N')
		game->player.angle = 270;
	game->player.pos.x = x;
	game->player.pos.y = y;
	game->player.mmap.x = game->player.pos.x * MMAP_TILE;
	game->player.mmap.y = game->player.pos.y * MMAP_TILE;
}

void	init_map(t_game *game, const char *scene_dir)
{
	(void)scene_dir;
	// Mapa 7x5
	// game->scene.map1d = ft_strdup(
	// 	"        1111111111111111111111111\n"
	// 	"        1000000000110000000000001\n"
	// 	"        1011000001110000000000001\n"
	// 	"        1001000000000000000000001\n"
	// 	"111111111011000001110000000000001\n"
	// 	"100000000011000001110111111111111\n"
	// 	"11110111111111011100000010001    \n"
	// 	"11110111111111011101010010001    \n"
	// 	"11000000110101011100000010001    \n"
	// 	"10000000000000001100000010001    \n"
	// 	"10000000000000001101010010001    \n"
	// 	"11000001110101011111011110N0111  \n"
	// 	"11110111 1110101 101111010001    \n"
	// 	"11111111 1111111 111111111111    \n"
	// );
	// game->scene.map2d = ft_split(game->scene.map1d, '\n');
	// game->scene.width_map = ft_strlen(game->scene.map2d[0]);
	// game->scene.height_map = my_strlen2d(game->scene.map2d);
	game->scene.ratio_map = (double)game->scene.width_map
		/ (double)game->scene.height_map;
	game->scene.h_mmap = game->scene.height_map * MMAP_TILE;
	game->scene.w_mmap = game->scene.width_map * MMAP_TILE;
	if (game->scene.w_mmap > WIDTH - 20 || game->scene.h_mmap > HEIGHT - 20)
		return (my_err_clean(game, FAIL_MINIMAP_TOO_BIG, false));
}

// Mapa 16x6
/*
	game->scene.map1d = ft_strdup("1111111111111111 "
								"1000000000000001 "
								"1000N00000000001 "
								"1111111111111111");
	game->scene.map2d = ft_split(game->scene.map1d, ' ');
	game->scene.width_map = 16;
	game->scene.height_map = 6;
	game->scene.ratio_map = (double)game->scene.width_map
	/ (double)game->scene.height_map;
	game->scene.ceil_rgb = LIGHT_BLUE;
	game->scene.floor_rgb = DARK_GREY;
*/

// Mapa 7x5
/*
	game->scene.map1d = ft_strdup (" 11111 \n"
			"110001 \n"
			"100N011\n"
			"111011 \n"
			"1 111  \n");
*/

// Mapa Example
/*
	game->scene.map1d = ft_strdup(
		"        1111111111111111111111111\n"
		"        1000000000110000000000001\n"
		"        1011000001110000000000001\n"
		"        1001000000000000000000001\n"
		"111111111011000001110000000000001\n"
		"100000000011000001110111111111111\n"
		"11110111111111011100000010001    \n"
		"11110111111111011101010010001    \n"
		"11000000110101011100000010001    \n"
		"10000000000000001100000010001    \n"
		"10000000000000001101010010001    \n"
		"11000001110101011111011110N0111  \n"
		"11110111 1110101 101111010001    \n"
		"11111111 1111111 111111111111    \n"
	);
	game->scene.map2d = ft_split(game->scene.map1d, '\n');
	game->scene.width_map = ft_strlen(game->scene.map2d[0]);
	game->scene.height_map = my_strlen2d(game->scene.map2d);
*/