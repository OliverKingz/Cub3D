/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozamora- <ozamora-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 12:11:57 by raperez-          #+#    #+#             */
/*   Updated: 2025/06/15 15:32:48 by ozamora-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

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

int	my_strnbrlen(const char *s)
{
	while ((*s < '1' || '9' < *s) && *s)
		s++;
	if (*s)
		return (ft_strlen(s));
	else
		return (-1);
}
