/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_raycast.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raperez- <raperez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 12:25:19 by ozamora-          #+#    #+#             */
/*   Updated: 2025/06/11 18:00:43 by raperez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_walls_and_rays(t_game *game)
{
	double	ray_angle;
	t_point	wall_pos;
	t_point	wall_dim;
	t_ray	ray;

	wall_dim.x = WALL_DIM_X;
	wall_pos.y = 0;
	wall_pos.x = 0;
	while (wall_pos.x < WIDTH)
	{
		ray_angle = game->player.angle - (FOV / 2)
			+ (wall_pos.x / (double)WIDTH) * FOV;
		ray = cast_ray(game, ray_angle);
		if (USE_MINIMAP)
			draw_ray(game->graphs.player, ray, MMAP_TILE);
		wall_dim.y = HEIGHT / ray.corrected_len;
		//if (wall_dim.y > HEIGHT)
		//	wall_dim.y = HEIGHT;
		wall_pos.y = (HEIGHT / 2) - (wall_dim.y / 2);
		if (USE_TEXTURES)
			draw_wall_texture(game, ray, wall_pos, wall_dim);
		else
			draw_wall_rectangle(game, ray, wall_pos, wall_dim);
		wall_pos.x += WALL_DIM_X;
	}
}

void	draw_ray(mlx_image_t *img, t_ray ray, int mult)
{
	double	x;
	double	y;

	x = ray.start_pos.x;
	while ((ray.vector.x > 0 && x <= ray.end_pos.x)
		|| (ray.vector.x < 0 && x >= ray.end_pos.x))
	{
		if (cos(ray.angle_rads) != 0)
		{
			y = tan(ray.angle_rads) * (x - ray.start_pos.x) + ray.start_pos.y;
			mlx_put_pixel(img, x * mult, y * mult, MMAP_RAY_COLOR);
		}
		x += ray.step_dir.x * RAY_RES;
	}
	y = ray.start_pos.y;
	while ((ray.vector.y > 0 && y <= ray.end_pos.y)
		|| (ray.vector.y < 0 && y >= ray.end_pos.y))
	{
		if (cos(ray.angle_rads) != 0 && tan(ray.angle_rads) != 0)
		{
			x = ((y - ray.start_pos.y) / tan(ray.angle_rads)) + ray.start_pos.x;
			mlx_put_pixel(img, x * mult, y * mult, MMAP_RAY_COLOR);
		}
		y += ray.step_dir.y * RAY_RES;
	}
}

void	draw_wall_texture(t_game *game, t_ray ray, t_point pos, t_point dim)
{
	mlx_texture_t	*texture;
	t_point			txt;
	t_point			p;

	txt.x = get_texture_and_xt(game, ray, &texture);
	if (!texture)
		return ;
	p.x = -1;
	if (dim.x > WIDTH)
		dim.x = WIDTH;
	if (dim.x > WIDTH)
		dim.x = WIDTH;
	while (++p.x < dim.x && (pos.x + p.x) < WIDTH)
	{
		p.y = -1;
		while (++p.y < dim.y && (pos.y + p.y) < HEIGHT)
		{
			txt.y = ((long long)p.y * texture->height) / dim.y;
			if (pos.x + p.x >= 0 && pos.x + p.x < WIDTH
				&& pos.y + p.y >= 0 && pos.y + p.y < HEIGHT)
				mlx_put_pixel(game->graphs.screen, pos.x + p.x, pos.y + p.y,
					get_pixel_rgba(texture, txt.x, txt.y));
		}
	}
}

void	draw_wall_rectangle(t_game *game, t_ray ray, t_point pos, t_point dim)
{
	if (ray.collision_dir == NORTH || ray.collision_dir == SOUTH)
		draw_rectangle(game->graphs.screen, pos, dim, WALL_COLOR);
	else
		draw_rectangle(game->graphs.screen, pos, dim, WALL_COLOR_SHADOW);
}

// void	draw_walls_and_rays(t_game *game)
// {
// 	double	ray_angle;
// 	int		wall_x_pos;
// 	int		wall_height;
// 	t_ray	ray;
// 	double	corrected_dist;

// 	wall_x_pos = 0;
// 	ray_angle = game->player.angle - FOV / 2;
// 	while (ray_angle < game->player.angle + FOV / 2)
// 	{
// 		ray = cast_ray(game, ray_angle);
// 		draw_ray(game->graphs.minimap, ray, MMAP_TILE);
// 		corrected_dist = correct_raylen_fisheye(ray_angle,
// 				game->player.angle, ray.size);
// 		wall_height = HEIGHT / corrected_dist;
// 		draw_rectangle(game->graphs.screen, wall_x_pos, (HEIGHT / 2)
//			- (wall_height / 2), wall_height);
// 		wall_x_pos += WIDTH / FOV;
// 		ray_angle += 1;
// 	}
// }

// void	draw_rectangle(mlx_image_t *img, int x, int y, int height)
// {
// 	int j;
// 	int	width;

// 	width = x + WIDTH / FOV;
// 	height += y;
// 	while (x < width)
// 	{
// 		j = y;
// 		while (j < height)
// 		{
// 			if (j >= 0 && j < HEIGHT)
// 				mlx_put_pixel(img, x, j, WALL_COLOR);
// 			j++;
// 		}
// 		x++;
// 	}
// }

// void	draw_walls_and_rays(t_game *game)
// {
// 	double	ray_angle;
// 	t_point	wall_pos;
// 	t_point	wall_dim;
// 	t_ray	ray;

// 	wall_pos.y = 0;
// 	wall_pos.x = 0;
// 	ray_angle = game->player.angle - (FOV / 2);
// 	while (ray_angle < game->player.angle + FOV / 2)
// 	{
// 		ray = cast_ray(game, ray_angle);
// 		draw_ray(game->graphs.player, ray, MMAP_TILE);
// 		wall_dim.x = wall_pos.x + WIDTH / FOV;
// 		if (ray.corrected_len != 0)
// 			wall_dim.y = HEIGHT / ray.corrected_len;
// 		else
// 			wall_dim.y = HEIGHT;
//		if (wall_dim.y > HEIGHT)
//			wall_dim.y = HEIGHT;
// 		wall_pos.y = (HEIGHT / 2) - (wall_dim.y / 2);
// 		if (USE_TEXTURES)
// 			draw_wall_texture(game, ray, wall_pos, wall_dim);
// 		else
// 			draw_wall_rectangle(game, ray, wall_pos, wall_dim);
// 		wall_pos.x += WIDTH / FOV;
// 		ray_angle += 1;
// 	}
// }
