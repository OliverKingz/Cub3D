/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raperez- <raperez-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 15:09:15 by ozamora-          #+#    #+#             */
/*   Updated: 2025/06/13 23:50:08 by raperez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	is_valid_rgb(const char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (false);
	if (my_strnbrlen(s) > 3)
		return (false);
	while (s[i])
	{
		if (!ft_isdigit(s[i]) && !(s[i] == '+' && i == 0))
			return (false);
		i++;
	}
	if (i == 0 || (i == 1 && s[0] == '+'))
		return (false);
	i = ft_atoi(s);
	if (i > 255)
		return (false);
	return (true);
}

uint32_t	get_rgb(t_game *game, char **s)
{
	char		**str_array;
	char		*temp;
	int			i;
	uint32_t	color;

	i = my_strchr_count(*s, ',');
	str_array = ft_split(*s, ',');
	my_free((void *)s);
	if (i != 2 || my_strlen2d(str_array) != 3)
		(my_free2d((void *)&str_array), my_err_clean(game, SCENE_RGB, false));
	i = -1;
	color = 0;
	while (++i < 3)
	{
		temp = ft_strtrim(str_array[i], " \f\n\r\t\v");
		if (!is_valid_rgb(temp))
			(my_free((void *)&temp), my_free2d((void *)&str_array),
				my_err_clean(game, SCENE_RGB, false));
		color = color << 8;
		color += ft_atoi(temp);
		my_free((void *)&temp);
	}
	my_free2d((void *)&str_array);
	color = (color << 8) + 0xFF;
	return (color);
}

uint32_t	get_rgb_pixel(mlx_texture_t *texture, int x, int y)
{
	size_t			idx;
	unsigned char	*p;

	if (!texture || !texture->pixels || x < 0 || x >= (int)texture->width
		|| y < 0 || y >= (int)texture->height)
		return (CLEAR);
	idx = ((size_t)y * texture->width + x) * 4;
	p = &texture->pixels[idx];
	return (((uint32_t)p[0] << 24) | ((uint32_t)p[1] << 16)
		| ((uint32_t)p[2] << 8) | (uint32_t)p[3]);
}
