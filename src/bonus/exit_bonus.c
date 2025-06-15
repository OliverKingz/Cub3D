/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozamora- <ozamora-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 19:43:10 by ozamora-          #+#    #+#             */
/*   Updated: 2025/06/15 15:31:47 by ozamora-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	my_mlx_err(t_game *game, const char *msg)
{
	ft_putendl_fd("Error", STDERR_FILENO);
	if (msg)
		ft_putendl_fd((char *)msg, STDERR_FILENO);
	if (mlx_errno != 0)
	{
		ft_putstr_fd("MLX42 Error: ", STDERR_FILENO);
		ft_putendl_fd((char *)mlx_strerror(mlx_errno), STDERR_FILENO);
	}
	free_game(game);
	exit(EXIT_FAILURE);
}

void	my_err_clean(t_game *game, const char *msg, bool perror_flag)
{
	ft_putendl_fd("Error", STDERR_FILENO);
	if (perror_flag && msg)
		perror(msg);
	else if (msg)
		ft_putendl_fd(msg, STDERR_FILENO);
	free_game(game);
	exit(EXIT_FAILURE);
}

void	free_map(t_game *game)
{
	if (!game)
		return ;
	my_free2d((void ***)&game->scene.map2d);
	my_free2d((void ***)&game->scene.file);
	my_free((void **)&game->scene.map1d);
}

void	free_game(t_game *game)
{
	if (!game)
		return ;
	free_images(game);
	free_textures(game);
	free_map(game);
	if (game->mlx)
		mlx_close_window(game->mlx);
}
