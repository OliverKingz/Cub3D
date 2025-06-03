/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozamora- <ozamora-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 19:43:10 by ozamora-          #+#    #+#             */
/*   Updated: 2025/06/03 19:47:40 by ozamora-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_mlx_err(const char *msg)
{
	ft_putstr_fd("Error\n", 2);
	if (msg)
		ft_putstr_fd((char *)msg, 2);
	if (mlx_errno != 0)
	{
		ft_putstr_fd("MLX42 Error: ", 2);
		ft_putstr_fd((char *)mlx_strerror(mlx_errno), 2);
	}
	exit(EXIT_FAILURE);
}

void	free_textures(t_game *game)
{
	mlx_delete_texture(game->graphs.north_t);
	mlx_delete_texture(game->graphs.south_t);
	mlx_delete_texture(game->graphs.east_t);
	mlx_delete_texture(game->graphs.west_t);
}

void	free_images(t_game *game)
{
	mlx_delete_image(game->mlx, game->graphs.north);
	mlx_delete_image(game->mlx, game->graphs.south);
	mlx_delete_image(game->mlx, game->graphs.east);
	mlx_delete_image(game->mlx, game->graphs.west);
	mlx_delete_image(game->mlx, game->graphs.bg);
	mlx_delete_image(game->mlx, game->graphs.minimap);
}

void	free_game(t_game *game)
{
	free_images(game);
	free_textures(game);
	//free_map2d(game);
}
