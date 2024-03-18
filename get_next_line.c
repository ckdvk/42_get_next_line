/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javimar2 <javimar2@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 17:58:19 by javimar2          #+#    #+#             */
/*   Updated: 2024/03/02 17:58:25 by javimar2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/**/

char	*get_next_line(int fd)
{
	static char		*remainder_array[MAX_FD];
	char			*current_line;

	if (fd < 0)
		return (NULL);
	if ((remainder_array[fd] && !ft_strchr(remainder_array[fd], '\n'))
		|| !remainder_array[fd])
		remainder_array[fd] = current_read(fd, remainder_array[fd]);
	if (!remainder_array[fd])
		return (NULL);
	current_line = get_current_line(remainder_array[fd]);
	if (!current_line)
		return (ft_free(&remainder_array[fd]));
	remainder_array[fd] = update_remainder(remainder_array[fd]);
	return (current_line);
}

char	*current_read(int fd, char *remainder)
{
	char	*buffer;
	int		read_bytes;

	read_bytes = 1;
	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (ft_free(&remainder));
	buffer[0] = '\0';
	while (!ft_strchr(buffer, '\n') && read_bytes > 0)
	{
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		if (read_bytes > 0)
		{
			buffer[read_bytes] = '\0';
			remainder = ft_strjoin(remainder, buffer);
		}
	}
	free(buffer);
	if (read_bytes == -1)
		return (ft_free(&remainder));
	return (remainder);
}

char	*get_current_line(char *remainder)
{
	char	*line;
	char	*nl_ptr;
	int		length;

	nl_ptr = ft_strchr(remainder, '\n');
	length = (nl_ptr - remainder) + 1;
	line = ft_substr(remainder, 0, length);
	if (!line)
		return (NULL);
	return (line);
}

char	*update_remainder(char *remainder)
{
	char	*new_remainder;
	char	*nl_ptr;
	int		length;

	nl_ptr = ft_strchr(remainder, '\n');
	if (!nl_ptr)
	{
		new_remainder = NULL;
		return (ft_free(&remainder));
	}
	else
		length = (nl_ptr - remainder) + 1;
	if (!remainder[length])
		return (ft_free(&remainder));
	new_remainder = ft_substr(remainder, length, ft_strlen(remainder) - length);
	ft_free(&remainder);
	if (!new_remainder)
		return (NULL);
	return (new_remainder);
}
