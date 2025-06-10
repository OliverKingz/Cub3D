/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raperez- <raperez-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 21:07:40 by raperez-          #+#    #+#             */
/*   Updated: 2025/06/10 21:07:45 by raperez-         ###   ########.fr       */
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

int	my_strnstr_pos(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	little_length;

	little_length = ft_strlen(little);
	if (little_length == 0)
		return (0);
	i = 0;
	while (big[i] && i + little_length <= len)
	{
		if (ft_strncmp(&big[i], little, little_length) == 0)
			return (i);
		i++;
	}
	return (-1);
}

char	*my_replace_first(char *og, char *target, char *rep)
{
	int		pos;
	size_t	size;
	char	*s;

	if (!og || !target || !rep)
		return (NULL);
	pos = my_strnstr_pos(og, target, ft_strlen(og));
	if (pos == -1)
		return (ft_strdup(og));
	size = ft_strlen(og) - ft_strlen(target) + ft_strlen(rep);
	s = ft_calloc(size + 1, sizeof(char));
	if (!s)
		return (ft_puterr("str calloc"), NULL);
	ft_memcpy(s, og, pos);
	ft_memcpy(&s[pos], rep, ft_strlen(rep));
	ft_memcpy(&s[pos + ft_strlen(rep)], &og[pos + ft_strlen(target)],
		ft_strlen(&og[pos + ft_strlen(target)]));
	return (s);
}

int	ft_strchr_count(const char *s, int c)
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

void	my_delete_texture(mlx_texture_t *texture)
{
	if (texture)
		mlx_delete_texture(texture);
}

void	my_delete_image(mlx_t *mlx, mlx_image_t *image)
{
	if (mlx && image)
		mlx_delete_image(mlx, image);
}
