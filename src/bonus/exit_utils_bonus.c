/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raperez- <raperez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 22:54:15 by ozamora-          #+#    #+#             */
/*   Updated: 2025/06/16 15:24:55 by raperez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	my_delete_texture(mlx_texture_t *texture)
{
	if (texture)
		mlx_delete_texture(texture);
}

void	my_delete_image(mlx_t *mlx, mlx_image_t *image)
{
	if (mlx && image)
		mlx_delete_image(mlx, image);
}

void	free_textures(t_game *game)
{
	if (!game)
		return ;
	my_free((void *)&(game->graphs.north_path));
	my_free((void *)&(game->graphs.south_path));
	my_free((void *)&(game->graphs.east_path));
	my_free((void *)&(game->graphs.west_path));
	my_free((void *)&(game->graphs.door_path));
	my_delete_texture(game->graphs.icon_t);
	my_delete_texture(game->graphs.north_t);
	my_delete_texture(game->graphs.south_t);
	my_delete_texture(game->graphs.east_t);
	my_delete_texture(game->graphs.west_t);
	my_delete_texture(game->graphs.door_t);
}

void	free_images(t_game *game)
{
	if (!game)
		return ;
	my_delete_image(game->mlx, game->graphs.screen);
	my_delete_image(game->mlx, game->graphs.minimap);
	my_delete_image(game->mlx, game->graphs.player);
}
