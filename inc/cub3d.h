/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozamora- <ozamora-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 18:31:20 by ozamora-          #+#    #+#             */
/*   Updated: 2025/06/03 19:15:04 by ozamora-         ###   ########.fr       */
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
	mlx_texture_t	*north_t;
	mlx_texture_t	*south_t;
	mlx_texture_t	*east_t;
	mlx_texture_t	*west_t;
	mlx_image_t		*north;
	mlx_image_t		*south;
	mlx_image_t		*east;
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

/* ************************************************************************** */
#endif