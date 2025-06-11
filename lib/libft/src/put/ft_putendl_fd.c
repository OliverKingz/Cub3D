/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raperez- <raperez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 17:12:03 by ozamora-          #+#    #+#             */
/*   Updated: 2025/06/11 12:56:46 by raperez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Sends a string to the specified file descriptor, followed by a newline
 * @param s:  The string to send.
 * @param fd: The file descriptor on which to write.
 * @return Nothing.
 * @note 
 * - The function ensures that a newline character is written to 'fd' after 
 * writing the string 's', effectively appending a newline to the output.
 * 
 * - If the input string 's' is NULL, the function does nothing.
 */
void	ft_putendl_fd(const char *s, int fd)
{
	if (fd < 0 || s == NULL)
		return ;
	write(fd, s, ft_strlen(s));
	write(fd, "\n", 1);
}
