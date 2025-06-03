#ifndef SO_LONG_H
# define SO_LONG_H

# include "MLX42/MLX42.h"
# include "libft.h"

# include <stdio.h>    // To use printf
# include <sys/time.h> // To use gettimeofday
# include <math.h>     // To use every function needed

/* Explicitly allowed functions for so_long, already included at the libraries
# include <stdbool.h> // Included in MLX42
# include <stddef.h>  // Included in MLX42
# include <stdint.h>  // Included in MLX42
# include <stdio.h>   // To use perror
# include <stdlib.h>  // To use malloc, free, exit and size_t
# include <string.h>  // To use strerror
# include <unistd.h>  // To use system calls like write, open, read, close.
 */


//Oliver lo pone bonito

typedef struct s_player
{
	int		x;
	int		y;
	float	angle;
}	t_player;

typedef struct s_scene
{
	char	*map1d;
	char	**map2d;
	int		height;
	int		width;
	int		floor_rgb;
	int		ceil_rgb;
}   t_scene;

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
}	t_graph;

typedef struct s_game
{
	t_scene		scene;
	t_graph		graphs;
	t_player	player;
	mlx_t		*mlx;
	bool		is_running;
}   t_game;

#endif