/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozamora- <ozamora-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 16:04:25 by ozamora-          #+#    #+#             */
/*   Updated: 2025/06/16 16:05:34 by ozamora-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	open_close_door(t_game *game, t_dir dir)
{
	int	x;
	int	y;

	x = (int)game->player.pos.x;
	y = (int)game->player.pos.y;
	if (dir == NORTH)
		y -= 1;
	else if (dir == SOUTH)
		y += 1;
	else if (dir == EAST)
		x += 1;
	else if (dir == WEST)
		x -= 1;
	if (game->scene.map2d[y][x] == DOOR_OPEN)
		game->scene.map2d[y][x] = DOOR_CLOSED;
	else if (game->scene.map2d[y][x] == DOOR_CLOSED)
		game->scene.map2d[y][x] = DOOR_OPEN;
	draw_frame(game);
	game->keys.e = false;
}

void	key_door(t_game *game)
{
	if (310 >= game->player.angle && game->player.angle >= 230)
		open_close_door(game, NORTH);
	else if (130 >= game->player.angle && game->player.angle >= 50)
		open_close_door(game, SOUTH);
	else if ((40 >= game->player.angle && game->player.angle >= 0)
		|| (360 > game->player.angle && game->player.angle >= 320))
		open_close_door(game, EAST);
	else if (220 >= game->player.angle && game->player.angle >= 140)
		open_close_door(game, WEST);
}
