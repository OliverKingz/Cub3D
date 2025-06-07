/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozamora- <ozamora-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 19:11:12 by raperez-          #+#    #+#             */
/*   Updated: 2025/06/07 12:57:29 by ozamora-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_frame(t_game *game)
{
	draw_screen_bg(game);
	draw_minimap(game);
	draw_walls_and_rays(game);
	//draw_ray(game->graphs.minimap, launch_ray(game, game->player.angle), MAP_TILE);
	draw_player_mmap(game);
}

void	draw_walls_and_rays(t_game *game)
{
	double		i;
	int			wall_x;
	int			wall_height;
	t_ray		ray;

	i = game->player.angle - FOV / 2;
	wall_x = 0;
	while (i < game->player.angle + FOV / 2)
	{
		ray = launch_ray(game, i);
		draw_ray(game->graphs.minimap, ray, MAP_TILE);
		if (DEBUG_MODE)
			//printf("Distacia ray: %f\n", ray.size);
		wall_height = HEIGHT / ray.size;
		(void)wall_height;
		draw_rectangle(game->graphs.screen, wall_x, (HEIGHT / 2) - (wall_height / 2), wall_height);
		wall_x += WIDTH / FOV;
		i += 1;
	}
}
