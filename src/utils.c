/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozamora- <ozamora-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 11:34:51 by raperez-          #+#    #+#             */
/*   Updated: 2025/06/10 18:02:09 by ozamora-         ###   ########.fr       */
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
