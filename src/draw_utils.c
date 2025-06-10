/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozamora- <ozamora-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 18:42:36 by ozamora-          #+#    #+#             */
/*   Updated: 2025/06/10 17:49:38 by ozamora-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_rectangle(mlx_image_t *img, t_point pos, t_point dim, int color)
{
	int	px;
	int	py;

	py = pos.y;
	while (py < pos.y + dim.y)
	{
		px = pos.x;
		while (px < pos.x + dim.x)
		{
			if (px >= 0 && px < (int)img->width && py >= 0
				&& py < (int)img->height)
				mlx_put_pixel(img, px, py, color);
			px++;
		}
		py++;
	}
}

int	get_texture_and_xt(t_game *game, t_ray ray, mlx_texture_t **texture)
{
	int	x_t;

	x_t = 0;
	*texture = NULL;
	if (ray.collision_dir == NORTH)
		*texture = game->graphs.north_t;
	else if (ray.collision_dir == SOUTH)
		*texture = game->graphs.south_t;
	else if (ray.collision_dir == WEST)
		*texture = game->graphs.west_t;
	else if (ray.collision_dir == EAST)
		*texture = game->graphs.east_t;
	if (ray.collision_dir == NORTH)
		x_t = (int)((1.0 - (ray.end_pos.x - floor(ray.end_pos.x)))
				* (*texture)->width) % (int)(*texture)->width;
	else if (ray.collision_dir == SOUTH)
		x_t = (int)(((ray.end_pos.x - floor(ray.end_pos.x)))
				* (*texture)->width) % (int)(*texture)->width;
	else if (ray.collision_dir == WEST)
		x_t = (int)(((ray.end_pos.y - floor(ray.end_pos.y))
					* (*texture)->width)) % (int)(*texture)->width;
	else if (ray.collision_dir == EAST)
		x_t = (int)((1.0 - (ray.end_pos.y - floor(ray.end_pos.y)))
				* (*texture)->width) % (int)(*texture)->width;
	return (x_t);
}

unsigned int	get_pixel_rgba(mlx_texture_t *texture, int x, int y)
{
	size_t			idx;
	unsigned int	rgba_hex;

	if (!texture || !texture->pixels)
		return (CLEAR);
	if (x >= 0 && x < (int)texture->width && y >= 0 && y < (int)texture->height)
	{
		idx = (y * texture->width + x) * texture->bytes_per_pixel;
		rgba_hex = (texture->pixels[idx] << 24)
			| (texture->pixels[idx + 1] << 16)
			| (texture->pixels[idx + 2] << 8)
			| (texture->pixels[idx + 3]);
		return (rgba_hex);
	}
	return (CLEAR);
}
