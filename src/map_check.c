/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozamora- <ozamora-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 14:34:22 by ozamora-          #+#    #+#             */
/*   Updated: 2025/06/13 14:57:43 by ozamora-         ###   ########.fr       */
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
