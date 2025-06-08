/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozamora- <ozamora-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 18:31:20 by ozamora-          #+#    #+#             */
/*   Updated: 2025/06/08 02:24:20 by ozamora-         ###   ########.fr       */
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

// Debug mode flag to enable or disable debug features in the game.
# ifndef DEBUG_MODE
#  define DEBUG_MODE 1
# endif

// Usage message for the game.
# define USAGE "Usage: ./cub3d assets/scenes/example.cub\n"

// Error messages for various failure scenarios in the game.
# define SCENE_EMPTY "Invalid scene: path is empty\n"
# define FAIL_MLX "Failed initializing MLX42\n"
# define FAIL_TEXTURE "Failed loading textures\n"
# define FAIL_IMAGES "Failed loading images\n"
# define FAIL_MINIMAP_TOO_BIG "Minimap is too big, change the tile size\n"

// Constants for the game window, minimap dimensions and speeds
# define WIDTH 1080		// Width of the game window
# define HEIGHT 720		// Height of the game window
# define MAP_TILE 30	// Size of each tile in the minimap
# define PMAP_RADIUS 3	// Radius of the player in the minimap in pixels
# define FOV 60			// Field of view in degrees for the raycasting system
# define SPEED 0.05		// Speed of the player movement in the game
# define ANGLE_SPEED 1	// Speed of the player rotation in degrees per frame

// Math constants for the game.
# define PI 3.14159265358979323846

// Colors used in the game, represented in RGBA format.
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

// Directions for the raycasting system.
// These directions are used to determine which side of the wall the ray hits.
typedef enum e_dir
{
	NONE,
	NO,
	SO,
	EA,
	WE
}					t_dir;

// File characters used in the file representation of the map.
// These characters represent different elements in the game world.
typedef enum e_file
{
	WALL = '1',
	EMPTY = '0',
	SPACE = ' ',
	NO_PLAYER = 'N',
	EA_PLAYER = 'E',
	SO_PLAYER = 'S',
	WE_PLAYER = 'W',
}					t_file;

// Point structure to represent a 2D point in the game world.
typedef struct s_point
{
	double			x;	// X coordinate of the point
	double			y;	// Y coordinate of the point
}					t_point;

// Player structure to represent the player's position and angle in the game.
typedef struct s_player
{
	t_point			pos;	// Player's position in the map array
	t_point			mmap;	// Player's position in the minimap in pixels
	double			angle;	// Player's angle in degrees
}					t_player;

// Scene structure to represent the game scene, including the map and colors.
typedef struct s_scene
{
	char			*map1d;		// 1D representation of the map
	char			**map2d;	// 2D representation of the map
	int				height_map;	// Height of the map array
	int				width_map;	// Width of the map array
	int				h_mmap;		// Height of the minimap
	int				w_mmap;		// Width of the minimap
	int				floor_rgb;	// RGB values for floor
	int				ceil_rgb;	// RGB values for ceiling
}					t_scene;

//  Ray structure to represent a ray in the raycasting system.
typedef struct s_ray
{
	double	angle_radians;	// Ray angle in radians
	t_point	vector;			// Direction vector (unit vector for the ray)
	t_point	start_point;	// Ray starting position (player position) RENAME POS_START
	t_point	pos;			// Current position of the ray (updated as it moves)
	t_point	delta_dist;		// Distance ray must travel to cross the next axis
	t_point	axis_dist;		// Distance from current pos to the next x or y axis
	t_point	real_axis_dist;	// Scaled distance to next axis x or y
	t_point	step;			// Step direction for x and y (-1, 0, or 1)
	t_dir	hit_dir;		// Direction of the wall hit (NO, SO, EA, WE) RENAME TO COLLISION_DIR
	double	size;			// Total distance from start_point to hit point RENAME TO LENGTH
}					t_ray;

// Graphical representation of the game, including textures and images.
typedef struct s_graph
{
	mlx_texture_t	*icon_t;	// Texture for the icon
	mlx_texture_t	*east_t;	// Textures for the east wall
	mlx_texture_t	*north_t;	// Textures for the north wall
	mlx_texture_t	*south_t;	// Textures for the south wall
	mlx_texture_t	*west_t;	// Textures for the west wall
	mlx_image_t		*east;		// Image for the east wall
	mlx_image_t		*north;		// Image for the north wall
	mlx_image_t		*south;		// Image for the south wall
	mlx_image_t		*west;		// Image for the west wall
	mlx_image_t		*screen;	// Image for the screen/window
	mlx_image_t		*minimap;	// Image for the minimap
}					t_graph;

// Keys structure to represent the state of the keys pressed by the player.
typedef struct s_keys
{
	bool	w; // Forward movement key
	bool	a; // Left movement key
	bool	s; // Backward movement key
	bool	d; // Right movement key
	bool	left; // Left rotation key
	bool	right; // Right rotation key
}					t_keys;

// Game structure to represent the entire game state.
typedef struct s_game
{
	t_scene			scene;		// Scene containing the game information 
	t_player		player;		// Player's position and angle
	mlx_t			*mlx;		// Pointer to the MLX instance
	t_graph			graphs;		// Graphical representation of the game
	t_keys			keys;		// State of the keys pressed
	bool			is_running; // Flag to indicate if the game is running
}					t_game;

/* ************************************************************************** */
/*                              FUNCTION DECLARATIONS                         */
/* ************************************************************************** */

// init_game.c

t_game				init_game(t_game *game, const char *scene_dir);
void				init_mlx(t_game *game);
void				init_images(t_game *game);
void				init_draw_to_window(t_game *game);

// init_scene.c

t_game				init_scene(t_game *game, const char *scene_dir);
void				init_texture(t_game *game, const char *scene_dir);
void				init_player(t_game *game, const char *scene_dir);
void				init_map(t_game *game, const char *scene_dir);

// draw.c

void				draw_frame(t_game *game);
void				draw_walls_and_rays(t_game *game);

// draw_screen.c

void				draw_screen_bg(t_game *game);
void				draw_rectangle(mlx_image_t *img, int x, int y, int height);

// draw_minimap.c

void				draw_minimap(t_game *game);
void				draw_ray(mlx_image_t *img, t_ray ray, int mult);
void				draw_player_mmap(t_game *game);

// draw_minimap_utils.c

void				draw_map_bg(t_game *game);
void				draw_fill_tile(t_game *game, int x, int y, int color);
void				draw_map_all_tiles(t_game *game);
void				draw_map_grid(t_game *game);

// hook.c

void				key_hook(mlx_key_data_t keydata, void *param);
void				close_hook(void *param);
void				loop_hook(void *param);

// move.c

void				move(t_game *game, int dx, int dy);
void				rotate(t_game *game, int dang);

// raycast.c REORGANIZATION SUGGESTION

void				init_ray(t_game *game, t_ray *ray, double angle);
t_ray				launch_ray(t_game *game, double angle); // cast_ray
double				calculate_ray_size(t_ray ray); // get_ray_length

// raycast_dda.c

void				set_delta_dist(t_ray *ray); // get_delta
void				calculate_axis_dist(t_ray *ray); // get_ray_to_axis_distance
void				move_ray(t_ray *ray); // move_ray_to_next_axis
void				check_hit(t_ray *ray, t_scene *scene); // detect_axis_is_wall_collision

// raycast_utils.c

double				degrees_to_radians(double degrees);
t_point				angle_to_vector(double angle_rads);

// exit.c

void				ft_mlx_err(const char *msg);
void				free_textures(t_game *game);
void				free_images(t_game *game);
void				free_map(t_game *game);
void				free_game(t_game *game);

// utils.c

void				my_perr(const char *msg, bool should_exit, int exit_code);
void				my_free(void **mem);
void				my_free2d(void ***mem);
void				my_close(int *fd);
void				my_delete_texture(mlx_texture_t *texture);
void				my_delete_image(mlx_t *mlx, mlx_image_t *image);

/* ************************************************************************** */
#endif