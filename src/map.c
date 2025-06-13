/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozamora- <ozamora-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 16:16:16 by raperez-          #+#    #+#             */
/*   Updated: 2025/06/13 16:47:35 by ozamora-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	read_map(t_game *game, int fd)
{
	char	*s;
	char	*temp;

	s = get_next_line(fd);
	while (my_is_str_empty(s))
	{
		my_free((void *)&s);
		s = get_next_line(fd);
	}
	while (!my_is_str_empty(s))
	{
		temp = game->scene.map1d;
		game->scene.map1d = ft_strjoin(temp, s);
		if (ft_strlen(s) > (size_t) game->scene.width_map)
			game->scene.width_map = ft_strlen(s);
		my_free((void *)&temp);
		my_free((void *)&s);
		s = get_next_line(fd);
	}
	check_after_map(game, s, fd);
	close(fd);
	check_map1d(game);
	game->scene.map2d = ft_split(game->scene.map1d, '\n');
	manage_map(game);
	check_walls(game);
}

void	manage_map(t_game *game)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	game->scene.height_map = my_strlen2d(game->scene.map2d);
	while (i < game->scene.height_map)
	{
		tmp = ft_calloc(game->scene.width_map + 1, sizeof(char));
		ft_memset((void *)tmp, SPACE, game->scene.width_map);
		ft_memmove(tmp, game->scene.map2d[i], ft_strlen(game->scene.map2d[i]));
		my_free((void *)&(game->scene.map2d[i]));
		game->scene.map2d[i] = tmp;
		j = 0;
		while (game->scene.map2d[i][j])
		{
			if (ft_strchr("NSEW", game->scene.map2d[i][j]))
				init_player(game, game->scene.map2d[i][j], j + 0.5, i + 0.5);
			j++;
		}
		i++;
	}
}
