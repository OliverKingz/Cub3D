/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raperez- <raperez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 19:11:12 by raperez-          #+#    #+#             */
/*   Updated: 2025/06/05 16:24:25 by raperez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_walls(t_game *game)
{
	int	i;

	i = game->player.angle - FOV / 2;
	while (i < game->player.angle + FOV / 2)
	{
		launch_ray(game, i);
		i++;
	}
}

void	draw_game(t_game *game)
{
	int			mmap_width;
	int			mmap_height;
	
	draw_bg(game);
	draw_walls(game); //AKA draw textures

	mmap_width = MAP_TILE * game->scene.width_map;
	mmap_height = MAP_TILE * game->scene.height_map;
	if (mmap_width > WIDTH - 20 || mmap_height > HEIGHT - 20)
		return (free_game(game), ft_mlx_err(FAIL_MINIMAP_TOO_BIG));
	draw_minimap(game, mmap_width, mmap_height);
	draw_player_mmap(game, 3, mmap_width, mmap_height);
}

void	draw_bg(t_game *game)
{
	int	x;
	int	y;

	game->graphs.bg = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	x = 0;
	while (x < WIDTH)
	{
		y = 0;
		while (y < HEIGHT / 2)
		{
			mlx_put_pixel(game->graphs.bg, x, y, game->scene.ceil_rgb);
			y++;
		}
		while (y < HEIGHT)
		{
			mlx_put_pixel(game->graphs.bg, x, y, game->scene.floor_rgb);
			y++;
		}
		x++;
	}
	mlx_image_to_window(game->mlx, game->graphs.bg, 0, 0);
}
