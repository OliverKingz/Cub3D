/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozamora- <ozamora-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 19:52:22 by ozamora-          #+#    #+#             */
/*   Updated: 2025/06/03 20:46:51 by ozamora-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_game	init_game(t_game *game)
{
	init_texture(game);
	// init_map(game, map_dir);
	init_mlx(game);
	init_images(game);
	draw_bg(game);
	// init_display(game); //AKA draw textures
	draw_minimap(game);
	game->is_running = true;
	return (*game);
}

void	init_texture(t_game *game)
{
	game->graphs.icon_t = mlx_load_png("./assets/textures/cub3de.png");
	game->graphs.east_t = mlx_load_png("./assets/textures/basic_ES.png"); //Coger de scene, necesario leer 
	game->graphs.north_t = mlx_load_png("./assets/textures/basic_NO.png");
	game->graphs.south_t = mlx_load_png("./assets/textures/basic_SO.png");
	game->graphs.west_t = mlx_load_png("./assets/textures/basic_WE.png");
	if (!game->graphs.north_t || !game->graphs.south_t || !game->graphs.east_t
		|| !game->graphs.west_t)
		ft_mlx_err(FAIL_TEXTURE);
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

// void	init_player(t_game *game)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	while (i < game->map.height)
// 	{
// 		j = 0;
// 		while (j < game->map.width)
// 		{
// 			if (game->map.grid[i][j] == 'P')
// 			{
// 				game->play.x = j;
// 				game->play.y = i;
// 				game->play.img = game->graphs.play;
// 			}
// 			j++;
// 		}
// 		i++;
// 	}
// }

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
