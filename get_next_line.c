/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamatya <pamatya@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 14:37:49 by pamatya           #+#    #+#             */
/*   Updated: 2024/05/01 17:40:44 by pamatya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		write_next(char *buffer, char *store);
char	*get_next_line(int fd);

// Function to write the contents of the buffer to the store
int write_next(char *buffer, char *store)
{
	int		i;
	char	*str;						//
	int		wrote;

	wrote = 0;
	i = line_length(buffer);
	str = store;					//
	while (*buffer && i--)
	{
		*store++ = *buffer++;
		wrote++;
	}
	*store = '\0';
	return (wrote);
}

// Primary function to get the next line
char	*get_next_line(int fd)
{
	ssize_t		bytes_read;
	char		buffer[BUFFER_SIZE];
	char		*next_line;
	int			line_len;
	static char	*store;

	next_line = NULL;
	bytes_read = read(fd, buffer, BUFFER_SIZE - 1);
	if (bytes_read <= 0)
		return (NULL);
	buffer[bytes_read] = '\0';
	line_len = line_length(buffer);
	
	store = malloc(line_len + 1);
	if (!store)
		return (NULL);
	write_next(buffer, store);
	// if (store[(line_len - 1)] == '\n')
	
	next_line = store;
	// (void)bytes_read;
	// (void)line_len;
	return (next_line);
}
