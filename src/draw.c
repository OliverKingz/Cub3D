/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raperez- <raperez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 19:11:12 by raperez-          #+#    #+#             */
/*   Updated: 2025/06/05 19:08:59 by raperez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_ray(mlx_image_t *img, t_ray ray, int mult)
{
	int	x;
	int	y;

	ray.start_point.x *= mult;
	ray.start_point.y *= mult;
	ray.pos.x *= mult;
	ray.pos.y *= mult;
	x = ray.start_point.x;
	while ((ray.vector.x > 0 && x <= ray.pos.x) || (ray.vector.x < 0 && x >= ray.pos.x))
	{
		y = tan(ray.angle_radians)*(x - ray.start_point.x) + ray.start_point.y;
		mlx_put_pixel(img, x, y, BLUE);
		x += ray.step.x;
	}
	y = ray.start_point.y;
	while ((ray.vector.y > 0 && y <= ray.pos.y) || (ray.vector.y < 0 && y >= ray.pos.y))
	{
		x = (y - ray.start_point.y) / tan(ray.angle_radians) + ray.start_point.x;
		mlx_put_pixel(img, x, y, BLUE);
		y += ray.step.y;
	}
}

void	draw_walls(t_game *game, int mmap_width, int mmap_height)
{
	double		i;
	t_ray		ray;

	game->graphs.rays_mmap = mlx_new_image(game->mlx, mmap_width, mmap_height);
	i = game->player.angle - FOV / 2;
	while (i < game->player.angle + FOV / 2)
	{
		ray = launch_ray(game, i);
		draw_ray(game->graphs.rays_mmap, ray, MAP_TILE);
		printf("Distacia: %f\n", ray.size);
		i++;
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
	draw_minimap(game, mmap_width, mmap_height);
	draw_walls(game, mmap_width, mmap_height);
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
