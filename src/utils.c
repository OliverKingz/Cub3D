/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raperez- <raperez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 11:34:51 by raperez-          #+#    #+#             */
/*   Updated: 2025/06/07 11:55:48 by raperez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_perr(const char *msg, bool should_exit, int exit_code)
{
	perror(msg);
	if (should_exit)
		exit(exit_code);
}

void	my_free(void **mem)
{
	if (*mem)
	{
		free(*mem);
		*mem = NULL;
	}
}

void	my_free2d(void ***mem)
{
	int	i;

	if (!mem || !*mem)
		return ;
	i = 0;
	while ((*mem)[i])
	{
		if ((*mem)[i] != NULL)
		{
			free((*mem)[i]);
			(*mem)[i] = NULL;
		}
		i++;
	}
	free(*mem);
	*mem = NULL;
}

void	my_close(int *fd)
{
	if (*fd != -1 && *fd != STDOUT_FILENO && *fd != STDIN_FILENO)
		close(*fd);
	*fd = -1;
}

void	my_delete_texture(mlx_texture_t* texture)
{
	if (texture)
		mlx_delete_texture(texture);
}

void	my_delete_image(mlx_t* mlx, mlx_image_t* image)
{
	if (mlx && image)
		mlx_delete_image(mlx, image);
}
