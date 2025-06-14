/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozamora- <ozamora-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 14:34:22 by ozamora-          #+#    #+#             */
/*   Updated: 2025/06/14 14:59:57 by ozamora-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_map1d(t_game *game)
{
	int	player_count;
	int	i;

	player_count = my_strchr_count(game->scene.map1d, 'N');
	player_count += my_strchr_count(game->scene.map1d, 'S');
	player_count += my_strchr_count(game->scene.map1d, 'E');
	player_count += my_strchr_count(game->scene.map1d, 'W');
	if (player_count != 1)
		my_err_clean(game, MAP_PLAYER_AMOUNT, false);
	i = 0;
	while (game->scene.map1d[i])
	{
		if (!ft_strchr(" 01NSEW\n", game->scene.map1d[i]))
			my_err_clean(game, MAP_INVALID_CHAR, false);
		i++;
	}
}

void	check_after_map(t_game *game, char *s, int fd)
{
	while (s)
	{
		if (!my_is_str_empty(s))
			my_err_clean(game, MAP_DATA_AFTERMAP, false);
		my_free((void *)&s);
		s = get_next_line(fd);
	}
}

void	check_walls(t_game *game)
{
	char	**temp;
	int		x;
	int		y;

	temp = my_strdup2d(game->scene.map2d);
	y = 0;
	while (y < game->scene.height_map)
	{
		x = 0;
		while (x < game->scene.width_map)
		{
			if (ft_strchr("0NSEW", game->scene.map2d[y][x]))
				flood_fill(game, temp, x, y);
			x++;
		}
		y++;
	}
	if (DEBUG_MODE)
		my_printf2d(temp);
	my_free2d((void *)&temp);
}

void	check_dimension(t_game *game)
{
	if (game->scene.width_map > MAX_MAP_WIDTH
		|| game->scene.height_map > MAX_MAP_HEIGHT)
		my_err_clean(game, MAP_TOO_BIG, false);
}

void	flood_fill(t_game *game, char **map, int x, int y)
{
	if (x < 0 || y < 0 || x >= game->scene.width_map
		|| y >= game->scene.height_map || map[y][x] == SPACE)
	{
		if (DEBUG_MODE)
			(printf("Flood fill:\n"), my_printf2d(map));
		my_free2d((void ***)&map);
		my_err_clean(game, MAP_NOT_WALLED, false);
	}
	else if (ft_strchr("0NSEW", map[y][x]))
	{
		map[y][x] = '*';
		flood_fill(game, map, x - 1, y);
		flood_fill(game, map, x + 1, y);
		flood_fill(game, map, x, y - 1);
		flood_fill(game, map, x, y + 1);
	}
}
