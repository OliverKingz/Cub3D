/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozamora- <ozamora-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 21:48:20 by ozamora-          #+#    #+#             */
/*   Updated: 2025/06/16 14:57:36 by ozamora-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	print_debug_info(t_game *game)
{
	t_ray	ray;

	if (DEBUG_MODE && game)
	{
		printf("\n%s ✅\n", game->graphs.north_path);
		printf("%s ✅\n", game->graphs.east_path);
		printf("%s ✅\n", game->graphs.south_path);
		printf("%s ✅\n", game->graphs.west_path);
		printf("Ceiling color: %X \t✅\n", game->scene.ceil_rgb);
		printf("Flooring color: %X  \t✅\n\n", game->scene.floor_rgb);
		print_texture_info(game->graphs.east_t);
		printf("Player (%f, %f, %f)\n", game->player.pos.x, game->player.pos.y,
			game->player.angle);
		ray = cast_ray(game, game->player.angle);
		print_ray_info(&ray);
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
	size_t			idx;
	unsigned int	rgba_hex;

	if (DEBUG_MODE && tx && tx->pixels)
	{
		if (x >= 0 && x < (int)tx->width && y >= 0 && y < (int)tx->height)
		{
			idx = (y * tx->width + x) * tx->bytes_per_pixel;
			rgba_hex = (tx->pixels[idx] << 24)
				| (tx->pixels[idx + 1] << 16)
				| (tx->pixels[idx + 2] << 8)
				| (tx->pixels[idx + 3]);
			printf("Pixel at (%d, %d):\n", x, y);
			printf("  RGBA: (%d, %d, %d, %d)\n", tx->pixels[idx], tx->pixels[idx
				+ 1], tx->pixels[idx + 2], tx->pixels[idx + 3]);
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
		printf("  Angle (radians/degree): %f / %fº\n", ray->angle_rads,
			rad_to_deg(ray->angle_rads));
		printf("  Start Point: (%f, %f)\n", ray->start_pos.x, ray->start_pos.y);
		printf("  End Point: (%f, %f)\n", ray->end_pos.x, ray->end_pos.y);
		printf("  Delta Dist: (%f, %f)\n", ray->delta_dist.x,
			ray->delta_dist.y);
		printf("  Axis Dist: (%f, %f)\n", ray->axis_dist.x, ray->axis_dist.y);
		printf("  Real Axis Dist: (%f, %f)\n", ray->real_axis_dist.x,
			ray->real_axis_dist.y);
		printf("  Step Directio: (%f, %f)\n", ray->step_dir.x, ray->step_dir.y);
		printf("  Hit Direction: %d\n", ray->collision_dir);
		printf("  Size: %f\n\n", ray->length);
	}
}
