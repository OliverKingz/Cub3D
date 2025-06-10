/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozamora- <ozamora-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 18:31:20 by ozamora-          #+#    #+#             */
/*   Updated: 2025/06/11 00:28:57 by ozamora-         ###   ########.fr       */
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
# include "colors.h"

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
/*                                   FLAGS                                    */
/* ************************************************************************** */

// Debug mode flag to enable or disable debug information printing.
# ifndef DEBUG_MODE
#  define DEBUG_MODE false
# endif

// Use textures flag to enable or disable texture rendering in the game.
# ifndef USE_TEXTURES
#  define USE_TEXTURES true
# endif

/* ************************************************************************** */
/*                              MACROS AND DEFINES                            */
/* ************************************************************************** */

// Usage message for the game. 
# define USAGE "Usage: ./cub3d assets/scenes/example.cub\n"

// Settings: constants for the game window, minimap dimensions and speeds
# define WIDTH 1080		// Width of the game window
# define HEIGHT 720		// Height of the game window

# define FOV 60			// Field of view in degrees for the raycasting system
# define SPEED 0.05		// Speed of the player movement in the game
# define ANGLE_SPEED 5	// Speed of the player rotation in degrees per frame
# define WALL_DIM_X 1	// Width of each wall segment in pixels
# define FPS 60 		// Frames per second for the game loop

# define MMAP_TILE 20			// Size of each tile in the minimap
# define MMAP_PLAYER_RADIUS 3	// Radius of the player in the minimap in tiles

// Colors used in the game, represented in RGBA format.
# define MMAP_WALL_COLOR LIGHT_GREEN	// Color of the walls in the minimap
# define MMAP_EMPTY_COLOR GREY			// Color of the empty spaces in the mmap
# define MMAP_GRID_COLOR BLACK			// Color of the grid in the minimap

# define MMAP_PLAYER_COLOR TURQUOISE	// Color of the player in the minimap
# define MMAP_RAY_COLOR WHITE			// Color of the rays in the minimap

# define WALL_COLOR GREEN 				// Color of the walls in the game
# define WALL_COLOR_SHADOW DARK_GREEN	// Shaded color of the walls in the game

// Math constants for the game.
# define PI 3.14159265358979323846

// Error messages for various failure scenarios in the game.
# define SCENE_EMPTY "Invalid scene: path is empty\n"
# define FAIL_MLX "Failed initializing MLX42\n"
# define FAIL_TEXTURE "Failed loading textures\n"
# define FAIL_IMAGES "Failed loading images\n"
# define FAIL_MINIMAP_TOO_BIG "Minimap is too big, change the tile size\n"

/* ************************************************************************** */
/*                              ENUMS AND STRUCTS                             */
/* ************************************************************************** */

// Directions for the raycasting system.
// These directions are used to determine which side of the wall the ray hits.
typedef enum e_dir
{
	NONE,
	NORTH,
	SOUTH,
	EAST,
	WEST
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
}				t_file;

// Point structure to represent a 2D point in the game world.
typedef struct s_point
{
	double	x;	// X coordinate of the point
	double	y;	// Y coordinate of the point
}				t_point;

// Player structure to represent the player's position and angle in the game.
typedef struct s_player
{
	t_point		pos;	// Player's position in the map array
	t_point		mmap;	// Player's position in the minimap in pixels
	double		angle;	// Player's angle in degrees
}				t_player;

// Scene structure to represent the game scene, including the map and colors.
typedef struct s_scene
{
	char	*map1d;		// 1D representation of the map
	char	**map2d;	// 2D representation of the map
	int		height_map;	// Height of the map array
	int		width_map;	// Width of the map array
	double	ratio_map;	// Aspect Ratio of the map (width/height)
	int		h_mmap;		// Height of the minimap
	int		w_mmap;		// Width of the minimap
	int		floor_rgb;	// RGB values for floor
	int		ceil_rgb;	// RGB values for ceiling
}				t_scene;

//  Ray structure to represent a ray in the raycasting system.
typedef struct s_ray
{
	double	length;			// Total distance from start_pos to hit point
	double	corrected_len;	// Corrected distance considering fisheye effect
	double	angle_rads;		// Ray angle in radians
	t_dir	collision_dir;	// Direction of the wall hit (NO, SO, EA, WE)
	t_point	vector;			// Direction vector (unit vector for the ray)
	t_point	start_pos;		// Start position of the ray (player position)
	t_point	end_pos;		// End position of the ray (updated as it moves)
	t_point	delta_dist;		// Distance ray must travel to cross the next axis
	t_point	axis_dist;		// Distance from current pos to the next x or y axis
	t_point	real_axis_dist;	// Scaled distance to next axis x or y
	t_point	step;			// Step direction for x and y (-1, 0, or 1)
}					t_ray;

// Graphical representation of the game, including textures and images.
typedef struct s_graph
{
	char			*east_path;		// Path to the texture for the east wall
	char			*north_path;	// Path to the texture for the north wall
	char			*south_path;	// Path to the texture for the south wall
	char			*west_path;		// Path to the texture for the west wall
	mlx_texture_t	*icon_t;		// Texture for the icon
	mlx_texture_t	*east_t;		// Textures for the east wall
	mlx_texture_t	*north_t;		// Textures for the north wall
	mlx_texture_t	*south_t;		// Textures for the south wall
	mlx_texture_t	*west_t;		// Textures for the west wall
	mlx_image_t		*east;			// Image for the east wall
	mlx_image_t		*north;			// Image for the north wall
	mlx_image_t		*south;			// Image for the south wall
	mlx_image_t		*west;			// Image for the west wall
	mlx_image_t		*screen;		// Image for the screen/window
	mlx_image_t		*minimap;		// Image for the minimap
	mlx_image_t		*player;		// Image for the player in the minimap
}					t_graph;

// Keys structure to represent the state of the keys pressed by the player.
typedef struct s_keys
{
	bool	w;		// Forward movement key
	bool	a;		// Left movement key
	bool	s;		// Backward movement key
	bool	d;		// Right movement key
	bool	left;	// Left rotation key
	bool	right;	// Right rotation key
}			t_keys;

// Game structure to represent the entire game state.
typedef struct s_game
{
	t_scene		scene;		// Scene containing the game information 
	t_player	player;		// Player's position and angle
	mlx_t		*mlx;		// Pointer to the MLX instance
	t_graph		graphs;		// Graphical representation of the game
	t_keys		keys;		// State of the keys pressed
	bool		is_running; // Flag to indicate if the game is running
}				t_game;

/* ************************************************************************** */
/*                              FUNCTION DECLARATIONS                         */
/* ************************************************************************** */

// init_game.c

t_game			init_game(t_game *game, const char *scene_dir);
void			init_mlx(t_game *game);
void			init_images(t_game *game);
void			init_draw_to_window(t_game *game);

// init_scene.c

t_game			init_scene(t_game *game, const char *scene_dir);
void			init_texture(t_game *game, const char *scene_dir);
void			init_player(t_game *game, const char *scene_dir);
void			init_map(t_game *game, const char *scene_dir);

// draw.c

void			draw_frame(t_game *game);
void			draw_screen_bg(t_game *game);
void			draw_player_bg(t_game *game);

// draw_raycast.c

void			draw_walls_and_rays(t_game *game);
void			draw_ray(mlx_image_t *img, t_ray ray, int mult);
void			draw_wall_rectangle(t_game *game, t_ray ray, t_point pos,
					t_point dim);
void			draw_wall_texture(t_game *game, t_ray ray, t_point pos,
					t_point dim);

// draw_minimap.c

//void			draw_minimap(t_game *game);
void			draw_player(t_game *game);
void			draw_minimap_tiles(t_game *game);
void			draw_minimap_grid_vertical(t_game *game);
void			draw_minimap_grid_horizontal(t_game *game);

// draw_utils.c

void			draw_rectangle(mlx_image_t *img, t_point pos, t_point size,
					int color);
int				get_texture_and_xt(t_game *game, t_ray ray,
					mlx_texture_t **texture);
unsigned int	get_pixel_rgba(mlx_texture_t *texture, int x, int y);

// hook.c

void			key_hook(mlx_key_data_t keydata, void *param);
void			close_hook(void *param);
void			loop_hook(void *param);
void			fps_counter(void);

// move.c

void			move(t_game *game, int dx, int dy);
void			rotate(t_game *game, int dang);

// raycast.c

void			init_ray(t_game *game, t_ray *ray, double angle);
t_ray			cast_ray(t_game *game, double angle);
double			get_ray_length(t_ray ray);
double			correct_raylen_fisheye(t_ray *ray, double player_angle);

// raycast_dda.c

void			get_delta(t_ray *ray);
void			get_ray_to_axis_distance(t_ray *ray);
void			move_ray_to_next_axis(t_ray *ray);
void			check_axis_is_wall_collision(t_ray *ray, t_scene *scene);

// raycast_utils.c

double			degrees_to_radians(double angle_degs);
t_point			radians_to_vector(double angle_rads);

// parser.c

bool			is_valid_color(const char *s);
uint32_t		get_rgb(t_game *game, char *s);
int				manage_line(t_game *game, char *s);
bool			read_file(t_game *game, const char *file);

// exit.c

void			my_mlx_err(const char *msg);
void			my_err_clean(t_game *game, char *msg);
void			free_map(t_game *game);
void			free_game(t_game *game);

// exit_utils.c

void			my_delete_texture(mlx_texture_t *texture);
void			my_delete_image(mlx_t *mlx, mlx_image_t *image);
void			free_textures(t_game *game);
void			free_images(t_game *game);

// utils.c

void			my_perr(const char *msg, bool should_exit, int exit_code);
void			my_free(void **mem);
void			my_free2d(void ***mem);
void			my_close(int *fd);

// utils2.c

int				my_strchr_pos(const char *s, char c);
int				my_strnstr_pos(const char *big, const char *little, size_t len);
char			*my_replace_first(char *og, char *target, char *rep);
int				my_strchr_count(const char *s, int c);
size_t			my_strlen2d(char **s);

// debug.c

void			print_debug_info(t_game *game);
void			print_texture_info(mlx_texture_t *texture);
void			print_texture_pixel_info(mlx_texture_t *texture, int x, int y);
void			print_ray_info(t_ray *ray);

/* ************************************************************************** */
#endif