/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozamora- <ozamora-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 19:11:12 by raperez-          #+#    #+#             */
/*   Updated: 2025/06/10 15:28:52 by ozamora-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_frame(t_game *game)
{
	draw_screen_bg(game);
	draw_minimap_tiles(game);
	draw_walls_and_rays(game);
	draw_minimap_grid(game);
	draw_minimap_player(game);
}

static double	fisheye_correction_ray_size(double ray_angle,
		double player_angle, double ray_size)
{
	double	ray_angle_rad;
	double	player_angle_rad;
	double	corrected;

	ray_angle_rad = degrees_to_radians(ray_angle);
	player_angle_rad = degrees_to_radians(player_angle);
	corrected = ray_size * cos(ray_angle_rad - player_angle_rad);
	if (corrected < 0.0001)
		corrected = 0.0001;
	return (corrected);
}

void	draw_walls_and_rays(t_game *game)
{
	double	ray_angle;
	t_point	wall_pos;
	t_point	wall_dim;
	t_ray	ray;
	double	corrected_dist;

	wall_dim.x = WALL_DIM_X;
	wall_pos.y = 0;
	wall_pos.x = 0;
	while (wall_pos.x < WIDTH)
	{
		ray_angle = game->player.angle - (FOV / 2) + ((double)wall_pos.x
				/ WIDTH) * FOV;
		ray = launch_ray(game, ray_angle);
		draw_ray(game->graphs.minimap, ray, MMAP_TILE);
		corrected_dist = fisheye_correction_ray_size(ray_angle,
				game->player.angle, ray.size);
		wall_dim.y = HEIGHT / corrected_dist;
		wall_pos.y = (HEIGHT / 2) - (wall_dim.y / 2);
		if (USE_TEXTURES)
			draw_wall_texture(game, ray, wall_pos, wall_dim);
		else
			draw_wall_rectangle(game, ray, wall_pos, wall_dim);
		wall_pos.x += WALL_DIM_X;
	}
}

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

void	draw_wall_rectangle(t_game *game, t_ray ray, t_point pos, t_point dim)
{
	if (ray.hit_dir == NORTH || ray.hit_dir == SOUTH)
		draw_rectangle(game->graphs.screen, pos, dim, WALL_COLOR);
	else
		draw_rectangle(game->graphs.screen, pos, dim, WALL_COLOR_SHADOW);
}

static int	get_texture_and_xt(t_game *game, t_ray ray, mlx_texture_t **texture)
{
	int	x_t;

	*texture = NULL;
	if (ray.hit_dir == NORTH)
		*texture = game->graphs.north_t;
	else if (ray.hit_dir == SOUTH)
		*texture = game->graphs.south_t;
	else if (ray.hit_dir == WEST)
		*texture = game->graphs.west_t;
	else if (ray.hit_dir == EAST)
		*texture = game->graphs.east_t;
	if (ray.hit_dir == NORTH)
		x_t = (int)((1.0 - (ray.pos.x - floor(ray.pos.x))) * (*texture)->width)
			% (int)(*texture)->width;
	else if (ray.hit_dir == SOUTH)
		x_t = (int)(((ray.pos.x - floor(ray.pos.x))) * (*texture)->width)
			% (int)(*texture)->width;
	else if (ray.hit_dir == WEST)
		x_t = (int)(((ray.pos.y - floor(ray.pos.y)) * (*texture)->width))
			% (int)(*texture)->width;
	else if (ray.hit_dir == EAST)
		x_t = (int)((1.0 - (ray.pos.y - floor(ray.pos.y))) * (*texture)->width)
			% (int)(*texture)->width;
	return (x_t);
}

void	draw_wall_texture(t_game *game, t_ray ray, t_point pos, t_point dim)
{
	mlx_texture_t	*texture;
	int				x_t;
	int				y_t;
	int				y;
	int				x;

	x_t = get_texture_and_xt(game, ray, &texture);
	if (!texture)
		return ;
	x = -1;
	while (++x < dim.x)
	{
		y = -1;
		while (++y < dim.y)
		{
			y_t = (int)(((double)y / (double)dim.y) * texture->height)
				% (int)texture->height;
			if (pos.x + x >= 0
				&& pos.x + x < (int)game->graphs.screen->width
				&& pos.y + y >= 0
				&& pos.y + y < (int)game->graphs.screen->height)
				mlx_put_pixel(game->graphs.screen, pos.x + x, pos.y + y,
					get_pixel_rgba(texture, x_t, y_t));
		}
	}
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
// 		ray = launch_ray(game, ray_angle);
// 		draw_ray(game->graphs.minimap, ray, MMAP_TILE);
// 		corrected_dist = fisheye_correction_ray_size(ray_angle,
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
