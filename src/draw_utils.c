/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozamora- <ozamora-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 18:42:36 by ozamora-          #+#    #+#             */
/*   Updated: 2025/06/12 00:37:43 by ozamora-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_rectangle(mlx_image_t *img, t_point pos, t_point dim, int color)
{
	t_point	p;
	t_point	end;

	end.x = pos.x + dim.x;
	end.y = pos.y + dim.y;
	p.y = pos.y;
	while (p.y < end.y)
	{
		if (p.y < 0)
			p.y = 0;
		if (p.y >= (int)img->height)
			break ;
		p.x = pos.x;
		while (p.x < end.x)
		{
			if (p.x < 0)
				p.x = 0;
			if (p.x >= (int)img->width)
				break ;
			mlx_put_pixel(img, p.x, p.y, color);
			p.x++;
		}
		p.y++;
	}
}

mlx_texture_t	*get_texture(t_game *game, t_ray ray)
{
	if (ray.collision_dir == NORTH)
		return (game->graphs.north_t);
	else if (ray.collision_dir == SOUTH)
		return (game->graphs.south_t);
	else if (ray.collision_dir == WEST)
		return (game->graphs.west_t);
	else if (ray.collision_dir == EAST)
		return (game->graphs.east_t);
	return (NULL);
}

int	get_x_texture(t_ray ray, mlx_texture_t *texture)
{
	int	x_t;

	if (!texture)
		return (0);
	if (ray.collision_dir == NORTH)
		x_t = (int)((1.0 - (ray.end_pos.x - floor(ray.end_pos.x)))
				* texture->width);
	else if (ray.collision_dir == SOUTH)
		x_t = (int)(((ray.end_pos.x - floor(ray.end_pos.x)))
				* texture->width);
	else if (ray.collision_dir == WEST)
		x_t = (int)(((ray.end_pos.y - floor(ray.end_pos.y))
					* texture->width));
	else if (ray.collision_dir == EAST)
		x_t = (int)((1.0 - (ray.end_pos.y - floor(ray.end_pos.y)))
				* texture->width);
	else
		x_t = 0;
	x_t = x_t % (int)(texture->width);
	if (x_t < 0)
		x_t += (int)(texture->width);
	return (x_t);
}

unsigned int	get_pixel_rgba(mlx_texture_t *texture, int x, int y)
{
	size_t			idx;
	unsigned char	*p;

	if (!texture || !texture->pixels || x < 0 || x >= (int)texture->width
		|| y < 0 || y >= (int)texture->height)
		return (CLEAR);
	idx = ((size_t)y * texture->width + x) * 4;
	p = &texture->pixels[idx];
	return (((unsigned int)p[0] << 24) | ((unsigned int)p[1] << 16)
		| ((unsigned int)p[2] << 8) | (unsigned int)p[3]);
}
