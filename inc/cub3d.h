/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozamora- <ozamora-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 18:31:20 by ozamora-          #+#    #+#             */
/*   Updated: 2025/06/03 20:46:07 by ozamora-         ###   ########.fr       */
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

#define USAGE "Usage: ./cub3d \"assets/scenes/example.cub\"\n"

#define SCENE_EMPTY "Invalid scene: path is empty\n"
#define FAIL_MLX "Failed initializing MLX42\n"
#define FAIL_TEXTURE "Failed loading textures\n"
#define FAIL_IMAGES "Failed loading images\n"

#define WIDTH 1080
#define HEIGHT 720

/* ************************************************************************** */
/*                              ENUMS AND STRUCTS                             */
/* ************************************************************************** */

typedef struct s_player
{
	int				x;
	int				y;
	float			angle;
}					t_player;

typedef struct s_scene
{
	char			*map1d;
	char			**map2d;
	int				height;
	int				width;
	int				floor_rgb;
	int				ceil_rgb;
}					t_scene;

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
	mlx_image_t		*minimap;
}					t_graph;

typedef struct s_game
{
	t_scene			scene;
	t_graph			graphs;
	t_player		player;
	mlx_t			*mlx;
	bool			is_running;
}					t_game;

/* ************************************************************************** */
/*                              FUNCTION DECLARATIONS                         */
/* ************************************************************************** */

// init.c

t_game	init_game(t_game *game);
void	init_texture(t_game *game);
void	init_images(t_game *game);
// void	init_player(t_game *game);
void	init_mlx(t_game *game);

// background.c

void	draw_bg(t_game *game);
void	draw_minimap(t_game *game);

// hook.c

void	key_hook(mlx_key_data_t keydata, void *param);
void	close_hook(void *param);

// exit.c

void	ft_mlx_err(const char *msg);
void	free_textures(t_game *game);
void	free_images(t_game *game);
void	free_game(t_game *game);

/* ************************************************************************** */
#endif