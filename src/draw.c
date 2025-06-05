/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raperez- <raperez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 19:11:12 by raperez-          #+#    #+#             */
/*   Updated: 2025/06/05 17:12:21 by raperez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_rays(t_game *game, int mmap_width, int mmap_height)
{
	double		i;
	double		x;
	double		y;
	t_ray	ray;

	game->graphs.rays_mmap = mlx_new_image(game->mlx, mmap_width, mmap_height);
	i = game->player.angle - FOV / 2;
	while (i < game->player.angle + FOV / 2)
	{
		ray = launch_ray(game, i);
		x = ray.start_point.x;
		while (x <= ray.pos.x)
		{
			y = tan(ray.angle_radians)*(x - ray.start_point.x) + ray.start_point.y;
			mlx_put_pixel(game->graphs.rays_mmap, x * MAP_TILE, y * MAP_TILE, BLUE);
			x += 0.001;
		}
		printf("Distacia: %f\n", ray.size);
		i += 0.001;
	}
	mlx_image_to_window(game->mlx, game->graphs.rays_mmap, WIDTH - 10
		- mmap_width, HEIGHT - 10 - mmap_height);
}

void	draw_game(t_game *game)
{
	int			mmap_width;
	int			mmap_height;
	
	draw_bg(game);
	mmap_width = MAP_TILE * game->scene.width_map;
	mmap_height = MAP_TILE * game->scene.height_map;
	if (mmap_width > WIDTH - 20 || mmap_height > HEIGHT - 20)
		return (free_game(game), ft_mlx_err(FAIL_MINIMAP_TOO_BIG));
	//draw_walls
	draw_minimap(game, mmap_width, mmap_height);
	draw_rays(game, mmap_width, mmap_height);
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
