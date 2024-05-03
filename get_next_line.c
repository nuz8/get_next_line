/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamatya <pamatya@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 14:37:49 by pamatya           #+#    #+#             */
/*   Updated: 2024/05/03 15:58:46 by pamatya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		write_n_shift(char *buffer, char *store, int line_len);
char	*get_next_line(int fd);

// Function to write the contents of the buffer to the store
int		write_n_shift(char *buffer, char *store, int line_len)
{
	char	*str;						//
	int		wrote;
	char	*buf_ptr;

	wrote = 0;
	buf_ptr = buffer;
	str = store;					//
	while (*buffer && line_len--)
	{
		*store++ = *buffer++;
		wrote++;
	}
	*store = '\0';
	while (*buffer)
		*buf_ptr++ = *buffer++;
	*buf_ptr = *buffer;
	return (wrote);
}

// Primary function to get the next line
char	*get_next_line(int fd)
{
	ssize_t		bytes_read;
	static char	buffer[BUFFER_SIZE];
	char		*next_line;
	char		*line_part;
	int			line_len;

	next_line = NULL;
	bytes_read = read(fd, buffer, BUFFER_SIZE - 1);
	if (bytes_read <= 0)
		return (NULL);
	buffer[bytes_read] = '\0';
	line_len = line_length(buffer);
	next_line = malloc(line_len + 1);
	if (!next_line)
		return (NULL);
	write_n_shift(buffer, next_line, line_len);
	while (next_line[line_length(next_line) - 1] != '\n')
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE - 1);
		if (bytes_read < 0)
			return (free(next_line), NULL);
		else if (bytes_read == 0)
			return (next_line);
		buffer[bytes_read] = '\0';
		line_len = line_length(buffer);
		line_part = malloc(line_len + 1);
		if (!line_part)
			return (NULL);
		write_n_shift(buffer, line_part, line_len);
		next_line = f_strjoin(next_line, line_part);
	}
	return (next_line);
}
