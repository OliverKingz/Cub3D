/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozamora- <ozamora-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 11:56:40 by raperez-          #+#    #+#             */
/*   Updated: 2025/06/15 15:32:21 by ozamora-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	check_file_extension(t_game *game, const char *scene_dir)
{
	if (ft_strlen(scene_dir) < 4 || ft_strrncmp(scene_dir, ".cub", 4) != 0)
		my_mlx_err(game, SCENE_EXTENSION);
}

char	**read_file(t_game *game, const char *file)
{
	char	*s;
	char	**temp;
	char	**full_file;
	int		fd;
	int		i;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		my_err_clean(game, file, true);
	i = 0;
	temp = NULL;
	full_file = NULL;
	while (1)
	{
		s = get_next_line(fd);
		if (!s)
			break ;
		temp = full_file;
		full_file = malloc((i + 2) * sizeof(char *));
		ft_memmove((void *)full_file, (void *)temp, i * sizeof(char *));
		full_file[i] = s;
		full_file[i + 1] = NULL;
		(free(temp), i++);
	}
	return (close(fd), full_file);
}

void	parser(t_game *game, const char *file)
{
	int		n;
	int		counter;
	int		i;

	check_file_extension(game, file);
	game->scene.file = read_file(game, file);
	counter = 0;
	i = 0;
	while (game->scene.file[i])
	{
		n = manage_line(game, game->scene.file[i]);
		if (n == -1)
			my_err_clean(game, SCENE_FORMAT, false);
		counter += n;
		i++;
		if (counter >= 6)
			break ;
	}
	if (counter < 6)
		my_err_clean(game, SCENE_FORMAT, false);
	read_map(game, i);
}

int	manage_line(t_game *game, char *s)
{
	char	*temp;
	char	*id;
	char	*info;
	int		i;

	temp = ft_strtrim(s, " \f\n\r\t\v");
	if (my_is_str_empty(temp))
		return (free(temp), 0);
	i = my_strchrs_pos(temp, " \f\n\r\t\v");
	if (i == -1)
		return (free(temp), -1);
	id = ft_substr(temp, 0, i);
	info = ft_substr(temp, i + 1, ft_strlen(temp));
	my_free((void *)&temp);
	return (select_line_infotype(game, id, info));
}

int	select_line_infotype(t_game *game, char *id, char *info)
{
	if (!game || !id || !info)
		return (my_free((void *)&id), my_free((void *)&info), -1);
	if (ft_strcmp(id, "NO") == 0 && !game->graphs.north_path)
		game->graphs.north_path = ft_strtrim(info, " \f\n\r\t\v");
	else if (ft_strcmp(id, "SO") == 0 && !game->graphs.south_path)
		game->graphs.south_path = ft_strtrim(info, " \f\n\r\t\v");
	else if (ft_strcmp(id, "WE") == 0 && !game->graphs.west_path)
		game->graphs.west_path = ft_strtrim(info, " \f\n\r\t\v");
	else if (ft_strcmp(id, "EA") == 0 && !game->graphs.east_path)
		game->graphs.east_path = ft_strtrim(info, " \f\n\r\t\v");
	else if (ft_strcmp(id, "F") == 0 && !game->scene.floor_rgb)
		(my_free((void *)&id), game->scene.floor_rgb = get_rgb(game, &info));
	else if (ft_strcmp(id, "C") == 0 && !game->scene.ceil_rgb)
		(my_free((void *)&id), game->scene.ceil_rgb = get_rgb(game, &info));
	else
		return (my_free((void *)&id), my_free((void *)&info), -1);
	my_free((void *)&id);
	my_free((void *)&info);
	return (1);
}
