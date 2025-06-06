/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raperez- <raperez-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 19:11:12 by raperez-          #+#    #+#             */
/*   Updated: 2025/06/06 23:56:49 by raperez-         ###   ########.fr       */
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
			if (j >= 0 && j < HEIGHT)
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

	i = game->player.angle - FOV / 2;
	wall_x = 0;
	while (i < game->player.angle + FOV / 2)
	{
		ray = launch_ray(game, i);
		draw_ray(game->graphs.minimap, ray, MAP_TILE);
		printf("Distacia: %f\n", ray.size);
		wall_height = HEIGHT / ray.size;
		(void)wall_height;
		draw_rectangle(game->graphs.screen, wall_x, (HEIGHT / 2) - (wall_height / 2), wall_height);
		wall_x += WIDTH / FOV;
		i++;
	}
}

void	init_draw_to_window(t_game *game)
{
	draw_frame(game);
	mlx_image_to_window(game->mlx, game->graphs.screen, 0, 0);
	mlx_image_to_window(game->mlx, game->graphs.minimap, WIDTH - 10
		- game->scene.w_mmap, HEIGHT - 10 - game->scene.h_mmap);
}

void	draw_frame(t_game *game)
{
	draw_screen_bg(game);
	draw_minimap(game);
	draw_walls_and_rays(game);
	//draw_ray(game->graphs.minimap, launch_ray(game, game->player.angle), MAP_TILE);
	draw_player_mmap(game);
}


void	draw_screen_bg(t_game *game)
{
	int	x;
	int	y;

	x = 0;
	while (x < WIDTH)
	{
		y = 0;
		while (y < HEIGHT / 2)
		{
			mlx_put_pixel(game->graphs.screen, x, y, game->scene.ceil_rgb);
			y++;
		}
		while (y < HEIGHT)
		{
			mlx_put_pixel(game->graphs.screen, x, y, game->scene.floor_rgb);
			y++;
		}
		x++;
	}
}
