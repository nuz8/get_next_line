/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamatya <pamatya@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 14:37:49 by pamatya           #+#    #+#             */
/*   Updated: 2024/05/09 18:33:43 by pamatya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*get_next_line(int fd)
{
	ssize_t		bytes_read;
	static char	buffer[4096][BUFFER_SIZE + 1];
	char		*next_line;
	char		*joined_line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!buffer[fd][0])
	{
		bytes_read = read(fd, &(buffer[fd][0]), BUFFER_SIZE);
		if (bytes_read <= 0)
			return (NULL);
		buffer[fd][bytes_read] = '\0';
	}
	next_line = copy_n_shift(&(buffer[fd][0]));
	if (!next_line)
		return (NULL);
	if (next_line[line_length(next_line) - 1] != '\n')
	{
		joined_line = extract_rest(next_line, &(buffer[fd][0]), fd);
		if (!joined_line)
			return (NULL);
		next_line = joined_line;
	}
	return (next_line);
}
