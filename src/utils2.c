/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozamora- <ozamora-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 21:07:40 by raperez-          #+#    #+#             */
/*   Updated: 2025/06/13 15:21:27 by ozamora-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	my_strchr_pos(const char *s, char c)
{
	int	i;

	if (!s)
		return (-1);
	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

int	my_strchrs_pos(const char *s, const char *c)
{
	int	i;

	if (!s)
		return (-1);
	i = 0;
	while (s[i])
	{
		if (ft_strchr(c, s[i]))
			return (i);
		i++;
	}
	return (-1);
}

int	my_strchr_count(const char *s, int c)
{
	int	i;
	int	counter;

	i = 0;
	counter = 0;
	while (s[i] != '\0')
	{
		if ((int)s[i] == (char)c)
			counter++;
		i++;
	}
	return (counter);
}

size_t	my_strlen2d(char **s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

bool	my_is_str_empty(const char *s)
{
	int	i;

	if (!s)
		return (true);
	i = 0;
	while (s[i])
	{
		if (!ft_isspace(s[i]))
			return (false);
		i++;
	}
	return (true);
}
