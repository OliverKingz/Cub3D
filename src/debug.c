/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozamora- <ozamora-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 21:48:20 by ozamora-          #+#    #+#             */
/*   Updated: 2025/06/10 00:01:18 by ozamora-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_debug_info(t_game *game)
{
	t_ray ray;

	if (DEBUG_MODE && game)
	{
		print_texture_info(game->graphs.east_t); // Debug
		printf("Player (%f, %f, %f)\n", game->player.pos.x, game->player.pos.y, game->player.angle);
		ray = launch_ray(game, game->player.angle);
		print_ray_info(&ray); // Debug
	}
}

void	print_texture_info(mlx_texture_t *tx)
{
	size_t	pixel_count;

	if (DEBUG_MODE && tx && tx->pixels)
	{
		pixel_count = tx->width * tx->height;
		printf("Texture info:\n");
		printf("  Width: %d\n", tx->width);
		printf("  Height: %d\n", tx->height);
		printf("  Bytes per pixel: %d\n", tx->bytes_per_pixel);
		printf("  Total pixels: %zu\n\n", pixel_count);
		print_texture_pixel_info(tx, tx->width - 1, tx->height - 1);
	}
}

void	print_texture_pixel_info(mlx_texture_t *tx, int x, int y)
{
	size_t	idx;
	unsigned int rgba_hex;

	if (DEBUG_MODE && tx && tx->pixels)
	{
		if (x >= 0 && x < (int)tx->width && y >= 0
			&& y < (int)tx->height)
		{
			idx = (y * tx->width + x) * tx->bytes_per_pixel;
			rgba_hex = (tx->pixels[idx] << 24)
					| (tx->pixels[idx + 1] << 16)
					| (tx->pixels[idx + 2] << 8)
					| (tx->pixels[idx + 3]);
			printf("Pixel at (%d, %d):\n", x, y);
			printf("  RGBA: (%d, %d, %d, %d)\n", tx->pixels[idx],
				tx->pixels[idx + 1], tx->pixels[idx + 2],
				tx->pixels[idx + 3]);
			printf("  RGBA (hex): 0x%08X\n\n", rgba_hex);
		}
		else
		{
			printf("Pixel coordinates (%d, %d) out of bounds.\n", x, y);
		}
	}
}

void	print_ray_info(t_ray *ray)
{
	if (DEBUG_MODE && ray)
	{
		printf("\nRay info:\n");
		printf("  Angle (radians): %f\n", ray->angle_radians);
		printf("  Start Point: (%f, %f)\n", ray->start_point.x, ray->start_point.y);
		printf("  End Point: (%f, %f)\n", ray->pos.x, ray->pos.y);
		printf("  Delta Dist: (%f, %f)\n", ray->delta_dist.x, ray->delta_dist.y);
		printf("  Axis Dist: (%f, %f)\n", ray->axis_dist.x, ray->axis_dist.y);
		printf("  Real Axis Dist: (%f, %f)\n", ray->real_axis_dist.x, ray->real_axis_dist.y);
		printf("  Step: (%f, %f)\n", ray->step.x, ray->step.y);
		printf("  Hit Direction: %d\n", ray->hit_dir);
		printf("  Size: %f\n\n", ray->size);
	}
}
