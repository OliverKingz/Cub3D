/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozamora- <ozamora-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 19:43:10 by ozamora-          #+#    #+#             */
/*   Updated: 2025/06/10 23:23:41 by ozamora-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_mlx_err(const char *msg)
{
	ft_putendl_fd("Error", STDERR_FILENO);
	if (msg)
		ft_putendl_fd((char *)msg, STDERR_FILENO);
	if (mlx_errno != 0)
	{
		ft_putstr_fd("MLX42 Error: ", STDERR_FILENO);
		ft_putstr_fd((char *)mlx_strerror(mlx_errno), 2);
	}
	exit(EXIT_FAILURE);
}

void	my_err_clean(t_game *game, char *msg)
{
	ft_putendl_fd("Error", STDERR_FILENO);
	if (msg)
		ft_putendl_fd(msg, STDERR_FILENO);
	free_game(game);
	exit(EXIT_FAILURE);
}

void	free_map(t_game *game)
{
	my_free2d((void ***)&game->scene.map2d);
	my_free((void **)&game->scene.map1d);
}

void	free_game(t_game *game)
{
	free_images(game);
	free_textures(game);
	free_map(game);
}
