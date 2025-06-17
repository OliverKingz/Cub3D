/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_raycast.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raperez- <raperez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 12:25:19 by ozamora-          #+#    #+#             */
/*   Updated: 2025/06/17 12:26:25 by raperez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_walls_and_rays(t_game *game)
{
	double	ray_angle;
	double	camera_x;
	t_point	wall_pos;
	t_point	wall_dim;
	t_ray	ray;

	wall_dim.x = WALL_DIM_X;
	wall_pos.x = 0;
	while (wall_pos.x < WIDTH)
	{
		camera_x = 2.0 * wall_pos.x / (WIDTH - 1) - 1.0;
		ray_angle = game->player.angle
			+ rad_to_deg(atan(camera_x * tan(deg_to_rad(FOV / 2.0))));
		ray = cast_ray(game, ray_angle);
		if (USE_MINIMAP)
			draw_ray(game->graphs.player, ray, MMAP_TILE);
		wall_dim.y = HEIGHT / ray.corrected_len;
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
	int				draw_start;
	int				draw_end;

	texture = get_texture(game, ray);
	txt.x = get_x_texture(ray, texture);
	p.x = -1;
	while (++p.x < dim.x && (pos.x + p.x) < WIDTH)
	{
		draw_end = (int)(pos.y + dim.y);
		draw_start = fmax(0, (int)pos.y);
		draw_end = fmin(HEIGHT, draw_end);
		p.y = draw_start - (int)pos.y;
		while (p.y < draw_end - (int)pos.y && dim.y != 0)
		{
			txt.y = ((long long)p.y * texture->height) / dim.y;
			if (pos.x + p.x >= 0 && pos.x + p.x < WIDTH
				&& pos.y + p.y >= 0 && pos.y + p.y < HEIGHT)
				mlx_put_pixel(game->graphs.screen, pos.x + p.x, pos.y + p.y,
					get_rgb_pixel(texture, txt.x, txt.y));
			p.y += 0.9;
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
