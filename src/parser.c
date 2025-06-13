/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozamora- <ozamora-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 11:56:40 by raperez-          #+#    #+#             */
/*   Updated: 2025/06/13 15:21:27 by ozamora-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	select_mode(t_game *game, char *id, char *info)
{
	if (!game || !id || !info)
		return (my_free((void *)&id), my_free((void *)&info), -1);
	if (ft_strcmp(id, "NO") == 0)
		game->graphs.north_path = ft_strtrim(info, " \f\n\r\t\v");
	else if (ft_strcmp(id, "SO") == 0)
		game->graphs.south_path = ft_strtrim(info, " \f\n\r\t\v");
	else if (ft_strcmp(id, "WE") == 0)
		game->graphs.west_path = ft_strtrim(info, " \f\n\r\t\v");
	else if (ft_strcmp(id, "EA") == 0)
		game->graphs.east_path = ft_strtrim(info, " \f\n\r\t\v");
	else if (ft_strcmp(id, "F") == 0)
		game->scene.floor_rgb = get_rgb(game, info);
	else if (ft_strcmp(id, "C") == 0)
		game->scene.ceil_rgb = get_rgb(game, info);
	else
		return (my_free((void *)&id), my_free((void *)&info), -1);
	my_free((void *)&id);
	my_free((void *)&info);
	return (1);
}

int	manage_line(t_game *game, char *s)
{
	char	*id;
	char	*info;
	int		i;

	if (my_is_str_empty(s))
		return (0);
	s = ft_strtrim(s, " \f\n\r\t\v");
	i = my_strchrs_pos(s, " \f\n\r\t\v");
	if (i == -1)
		return (free(s), -1);
	id = ft_substr(s, 0, i);
	info = ft_substr(s, i + 1, ft_strlen(s));
	my_free((void *)&s);
	return (select_mode(game, id, info));
}

void	read_file(t_game *game, const char *file)
{
	int		fd;
	int		n;
	int		counter;
	char	*s;

	fd = open(file, R_OK);
	if (fd < 0)
		my_err_clean(game, file, true);
	s = get_next_line(fd);
	counter = 0;
	while (s)
	{
		n = manage_line(game, s);
		if (n == -1)
			my_err_clean(game, "Invalid map format", false);
		counter += n;
		my_free((void *)&s);
		if (counter >= 6)
			break ;
		s = get_next_line(fd);
	}
	if (counter != 6)
		my_err_clean(game, "Invalid map format", false);
	read_map(game, fd);
}
