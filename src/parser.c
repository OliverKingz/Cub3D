/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raperez- <raperez-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 11:56:40 by raperez-          #+#    #+#             */
/*   Updated: 2025/06/10 13:43:34 by raperez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	error_clean(t_game *game, char *msg)
{
	ft_putendl_fd(msg, STDERR_FILENO);
	free_game(game);
	exit(1);
}

size_t	ft_strlen2d(char **s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

bool	is_valid_color(const char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (false);
	while (s[i])
	{
		if ((!ft_isdigit(s[i]) && !(s[i] == '+' && i == 0)) || i > 3)
			return (false);
		i++;
	}
	if (i == 0)
		return (false);
	i = ft_atoi(s);
	if (i > 255)
		return (false);
	return (true);
}

uint32_t	get_rgb(t_game *game, char *s)
{
	char		**str_array;
	char		*temp;
	int			i;
	uint32_t	color;

	(void) game;
	//Comprobar numero de comas
	str_array = ft_split(s, ',');
	if (ft_strlen2d(str_array) != 3)
		error_clean(game, "Invalid rgb format");
	i = 0;
	color = 0;
	while (i < 3)
	{
		temp = ft_strtrim(str_array[i], " \f\n\r\t\v");
		if (!is_valid_color(temp))
			(my_free((void *)&temp), error_clean(game, "Invalid rgb format"));
		color = color << 8;
		color += ft_atoi(temp);
		my_free((void *)&temp);
		i++;
	}
	my_free2d((void *)&str_array);
	color = (color << 8) + 0xFF;
	return (color);
}

//Returns 0 is line is empty, 1 in case of correct info and -1 on error
int	manage_line(t_game *game, char *s)
{
	char	**str_array;

	s = ft_strtrim(s, " \f\n\r\t\v");
	if (ft_strlen(s) == 0)
		return (0);
	str_array = ft_split(s, ' ');
	if (ft_strcmp(str_array[0], "NO") == 0)
		game->graphs.north_path = ft_strdup(str_array[1]);
	else if (ft_strcmp(str_array[0], "SO") == 0)
		game->graphs.south_path = ft_strdup(str_array[1]);
	else if (ft_strcmp(str_array[0], "WE") == 0)
		game->graphs.west_path = ft_strdup(str_array[1]);
	else if (ft_strcmp(str_array[0], "EA") == 0)
		game->graphs.east_path = ft_strdup(str_array[1]);
	else if (ft_strcmp(str_array[0], "F") == 0)
		game->scene.floor_rgb = get_rgb(game, str_array[1]);
	else if (ft_strcmp(str_array[0], "C") == 0)
		game->scene.ceil_rgb = get_rgb(game, str_array[1]);
	else
		return (my_free2d((void *)&str_array), -1);
	my_free2d((void *)&str_array);
	return (1);
}

//Tries to open and read the file passed as parameter, returns false on failure
bool	read_file(t_game *game, const char *file)
{
	int		fd;
	char	*s;

	fd = open(file, R_OK);
	if (fd < 0)
		return (false);
	s = get_next_line(fd);
	while (s)
	{
		manage_line(game, s);
		my_free((void *)&s);
		s = get_next_line(fd);
	}
	return (true);
}
