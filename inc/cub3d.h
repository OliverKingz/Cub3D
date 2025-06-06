/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozamora- <ozamora-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 18:31:20 by ozamora-          #+#    #+#             */
/*   Updated: 2025/06/06 18:56:44 by ozamora-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

/* ************************************************************************** */
/*                              STANDARD INCLUDES                             */
/* ************************************************************************** */
// Standard libraries and system headers required for Cub3D functionality.

# include "MLX42/MLX42.h"
# include "libft.h"

/* Explicitly allowed functions for so_long, already included at the libraries
# include <stdbool.h> // Included in MLX42
# include <stddef.h>  // Included in MLX42
# include <stdint.h>  // Included in MLX42
# include <stdio.h>   // To use perror, printf
# include <stdlib.h>  // To use malloc, free, exit and size_t
# include <string.h>  // To use strerror
# include <unistd.h>  // To use system calls like write, open, read, close.
 */

# include <math.h>     // To use every function needed
# include <sys/time.h> // To use gettimeofday

/* ************************************************************************** */
/*                              MACROS AND DEFINES                            */
/* ************************************************************************** */

# define USAGE "Usage: ./cub3d assets/scenes/example.cub\n"

# define SCENE_EMPTY "Invalid scene: path is empty\n"
# define FAIL_MLX "Failed initializing MLX42\n"
# define FAIL_TEXTURE "Failed loading textures\n"
# define FAIL_IMAGES "Failed loading images\n"
# define FAIL_MINIMAP_TOO_BIG "Minimap is too big, change the tile size\n"

# define WIDTH 540
# define HEIGHT 360
# define MAP_TILE 10
# define PMAP_RADIUS 3
# define FOV 60
# define SPEED 0.2
# define ANGLE_SPEED 1

# define PI 3.14159265358979323846

# define BLACK 0x000000FF
# define WHITE 0xFFFFFFFF
# define GREY 0x808080FF
# define LIGHT_GREY 0xC0C0C0FF
# define DARK_GREY 0x404040FF
# define GREEN 0x00FF00FF
# define TURQUOISE 0x40E0D0FF
# define BLUE 0x0000FFFF
# define LIGHT_BLUE 0xADD8E6FF
# define DARK_BLUE 0x00008BFF

/* ************************************************************************** */
/*                              ENUMS AND STRUCTS                             */
/* ************************************************************************** */

typedef enum e_dir
{
	NONE,
	NO,
	SO,
	EA,
	WE
}					t_dir;

typedef struct s_point
{
	double			x;
	double			y;
}					t_point;

typedef struct s_player
{
	t_point			pos;
	t_point			mmap;
	double			angle;
}					t_player;

typedef struct s_scene
{
	char			*map1d;
	char			**map2d;
	int				height_map;
	int				width_map;
	int				h_mmap;
	int				w_mmap;
	int				floor_rgb;
	int				ceil_rgb;
}					t_scene;

typedef struct s_ray
{
	double	angle_radians;
	t_point	vector;
	t_point	start_point;
	t_point	pos;
	t_dir	hit_dir;
	t_point	delta_dist;
	t_point	axis_dist;
	t_point real_axis_dist;
	t_point	step;
	double	size;
}	t_ray;

typedef struct s_graph
{
	mlx_texture_t	*icon_t;
	mlx_texture_t	*east_t;
	mlx_texture_t	*north_t;
	mlx_texture_t	*south_t;
	mlx_texture_t	*west_t;
	mlx_image_t		*east;
	mlx_image_t		*north;
	mlx_image_t		*south;
	mlx_image_t		*west;
	mlx_image_t		*bg;
	mlx_image_t		*walls;
	mlx_image_t		*minimap;
	mlx_image_t		*player_mmap;
	mlx_image_t		*rays_mmap;
}					t_graph;

typedef struct s_game
{
	t_scene			scene;
	t_player		player;
	mlx_t			*mlx;
	t_graph			graphs;
	bool			is_running;
}					t_game;

/* ************************************************************************** */
/*                              FUNCTION DECLARATIONS                         */
/* ************************************************************************** */

// init_game.c

t_game				init_game(t_game *game, const char *scene_dir);
void				init_images(t_game *game);
void				init_mlx(t_game *game);

// init_scene.c
t_game				init_scene(t_game *game, const char *scene_dir);
void				init_texture(t_game *game, const char *scene_dir);
void				init_player(t_game *game, const char *scene_dir);
void				init_map(t_game *game, const char *scene_dir);

// draw.c
void				draw_game(t_game *game);
void				draw_bg(t_game *game);
void	draw_walls_and_rays(t_game *game);
void	draw_rectangle(mlx_image_t *img, int x, int y, int height);
void	draw_ray(mlx_image_t *img, t_ray ray, int mult);

// map.c

void				draw_minimap(t_game *game);
void	draw_player_mmap(t_game *game);
void	draw_map_bg(t_game *game);
void	draw_fill_cell(t_game *game, int x, int y, int color);
void	draw_map_cells(t_game *game);
void	draw_map_grid(t_game *game);

// hook.c

void				key_hook(mlx_key_data_t keydata, void *param);
void				close_hook(void *param);

// move.c
void	move(t_game *game, int dx, int dy, int dang);

// exit.c

void				ft_mlx_err(const char *msg);
void				free_textures(t_game *game);
void				free_images(t_game *game);
void				free_map(t_game *game);
void				free_game(t_game *game);

// raycast.c

double				degrees_to_radians(double degrees);
t_point				angle_to_vector(double angle_rads);
void				set_delta_dist(t_ray *ray);
void				init_ray(t_game *game, t_ray *ray, double angle);
void				calculate_axis_dist(t_ray *ray);
void				move_ray(t_ray *ray);
void				check_hit(t_ray *ray, t_scene *scene);
double				calculate_ray_size(t_ray ray);
t_ray				launch_ray(t_game *game, double angle);

/* ************************************************************************** */
#endif