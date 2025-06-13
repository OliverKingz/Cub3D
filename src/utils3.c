/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozamora- <ozamora-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 12:11:57 by raperez-          #+#    #+#             */
/*   Updated: 2025/06/13 15:20:08 by ozamora-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	**my_strdup2d(char **src)
{
	char	**dest;
	int		len2d;
	int		i;

	if (!src)
		return (NULL);
	len2d = my_strlen2d(src);
	dest = malloc((len2d + 1) * sizeof(char *));
	if (!dest)
		return (NULL);
	i = 0;
	while (i < len2d)
	{
		dest[i] = ft_strdup(src[i]);
		i++;
	}
	dest[i] = NULL;
	return (dest);
}

void	my_printf2d(char **s)
{
	while (*s)
	{
		printf("%s\n", *s);
		s += 1;
	}
}
