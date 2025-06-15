/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozamora- <ozamora-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 16:16:16 by raperez-          #+#    #+#             */
/*   Updated: 2025/06/15 15:32:07 by ozamora-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	read_map(t_game *game, int i)
{
	char	*temp;

	while (game->scene.file[i] && my_is_str_empty(game->scene.file[i]))
		i++;
	if (!game->scene.file[i])
		my_err_clean(game, MAP_EMPTY, false);
	while (!my_is_str_empty(game->scene.file[i]))
	{
		temp = game->scene.map1d;
		game->scene.map1d = ft_strjoin(temp, game->scene.file[i]);
		if (ft_strlen(game->scene.file[i]) > (size_t) game->scene.width_map)
			game->scene.width_map = ft_strlen(game->scene.file[i]);
		my_free((void *)&temp);
		i++;
	}
	check_after_map(game, i);
	my_free2d((void *)&game->scene.file);
	check_map1d(game);
	game->scene.map2d = ft_split(game->scene.map1d, '\n');
	game->scene.height_map = my_strlen2d(game->scene.map2d);
	check_dimension(game);
	manage_map(game);
	check_walls(game);
}

void	manage_map(t_game *game)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
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
