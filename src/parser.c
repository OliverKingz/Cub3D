/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozamora- <ozamora-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 11:56:40 by raperez-          #+#    #+#             */
/*   Updated: 2025/06/13 16:53:14 by ozamora-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_file(t_game *game, const char *scene_dir)
{
	int		fd;
	char	buffer[1];
	ssize_t	bytes_read;

	if (ft_strlen(scene_dir) <= 4 || ft_strrncmp(scene_dir, ".cub", 4) != 0)
		(free_game(game), my_mlx_err(SCENE_EXTENSION));
	fd = open(scene_dir, O_RDONLY);
	if (fd == -1)
		(free_game(game), my_mlx_err(SCENE_UNEXISTENT));
	bytes_read = read(fd, buffer, 1);
	if (bytes_read == 0)
		(free_game(game), close(fd), my_mlx_err(SCENE_EMPTY));
	else if (bytes_read == -1)
		(free_game(game), close(fd), my_mlx_err(SCENE_ERROR_READ));
	close(fd);
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
			my_err_clean(game, SCENE_FORMAT, false);
		counter += n;
		my_free((void *)&s);
		if (counter >= 6)
			break ;
		s = get_next_line(fd);
	}
	if (counter != 6)
		my_err_clean(game, SCENE_FORMAT, false);
	read_map(game, fd);
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
	return (select_line_infotype(game, id, info));
}

int	select_line_infotype(t_game *game, char *id, char *info)
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
