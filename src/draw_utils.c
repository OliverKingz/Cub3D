/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozamora- <ozamora-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 18:42:36 by ozamora-          #+#    #+#             */
/*   Updated: 2025/06/15 23:43:23 by ozamora-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_rectangle(mlx_image_t *img, t_point pos, t_point dim, int color)
{
	t_point	start;
	t_point	end;

	end.x = pos.x + dim.x;
	end.y = pos.y + dim.y;
	start.y = pos.y;
	while (start.y < end.y)
	{
		if (start.y < 0)
			start.y = 0;
		if (start.y >= (int)img->height)
			break ;
		start.x = pos.x;
		while (start.x < end.x)
		{
			if (start.x < 0)
				start.x = 0;
			if (start.x >= (int)img->width)
				break ;
			mlx_put_pixel(img, start.x, start.y, color);
			start.x++;
		}
		start.y++;
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
