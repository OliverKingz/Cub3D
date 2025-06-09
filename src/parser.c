/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raperez- <raperez-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 11:56:40 by raperez-          #+#    #+#             */
/*   Updated: 2025/06/09 16:46:02 by raperez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
		//manejar rgb
		;
	else if (ft_strcmp(str_array[0], "C") == 0)
		//manejar rgb
		;
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
		s = get_next_line(fd);
	}
	return (true);
}
