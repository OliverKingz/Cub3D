/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozamora- <ozamora-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 19:11:12 by raperez-          #+#    #+#             */
/*   Updated: 2025/06/06 18:50:48 by ozamora-         ###   ########.fr       */
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

void	draw_rectangle(mlx_image_t *img, int x, int y, int height)
{
	int j;
	int	width;

	width = x + WIDTH / FOV;
	height += y;
	while (x < width)
	{
		j = y;
		while (j < height)
		{
			if (j >= 0)
				mlx_put_pixel(img, x, j, GREEN);
			j++;
		} 
		x++;
	}
}

void	draw_walls_and_rays(t_game *game)
{
	double		i;
	int			wall_x;
	int			wall_height;
	t_ray		ray;

	// game->graphs.rays_mmap = mlx_new_image(game->mlx, game->scene.w_mmap, game->scene.h_mmap);
	i = game->player.angle - FOV / 2;
	wall_x = 0;
	while (i < game->player.angle + FOV / 2)
	{
		ray = launch_ray(game, i);
		draw_ray(game->graphs.minimap, ray, MAP_TILE);
		//printf("Distacia: %f\n", ray.size);
		wall_height = HEIGHT / ray.size;
		draw_rectangle(game->graphs.bg, wall_x, (HEIGHT / 2) - (wall_height / 2), wall_height);
		wall_x += WIDTH / FOV;
		i++;
	}
	// mlx_image_to_window(game->mlx, game->graphs.rays_mmap, WIDTH - 10
	// 	- game->scene.w_mmap, HEIGHT - 10 - game->scene.h_mmap);
}

void	draw_game(t_game *game)
{
	draw_bg(game);
	draw_minimap(game);
	draw_walls_and_rays(game);
	draw_player_mmap(game);
}

void	draw_bg(t_game *game)
{
	int	x;
	int	y;

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
