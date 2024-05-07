/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamatya <pamatya@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 14:37:49 by pamatya           #+#    #+#             */
/*   Updated: 2024/05/07 19:50:52 by pamatya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// Primary function to get the next line
// (version1: with buffer as char array)
char	*get_next_line(int fd)
{
	ssize_t		bytes_read;
	static char	buffer[BUFFER_SIZE + 1];
	char		*next_line;
	char		*joined_line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!*buffer)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read <= 0)
			return (NULL);
		buffer[bytes_read] = '\0';
	}
	next_line = copy_n_shift(buffer);
	if (!next_line)
		return (NULL);
	if (next_line[line_length(next_line) - 1] != '\n')		// Reviewed this as (next_line[line_length(next_line)] != '\n') and it fails because it only ever finds \0 at that index
	{
		joined_line = extract_rest(next_line, buffer, fd);
		if (!joined_line)
			return (NULL);
		next_line = joined_line;
	}
	return (next_line);
}

// // Primary function to get the next line
// // (version 2: with buffer as calloc'd pointer)
// char	*get_next_line(int fd)
// {
// 	ssize_t		bytes_read;
// 	static char	*buffer = NULL;
// 	char		*next_line;
// 	char		*joined_line;

// 	next_line = NULL;
// 	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, next_line, 0) < 0)
// 		return (NULL);
// 	if (!buffer)
// 	{
// 		buffer = (char *)ft_calloc((BUFFER_SIZE + 1), sizeof(char));
// 		if (!buffer)
// 			return (NULL);
// 	}
// 	if (!*buffer || !has_new_line(buffer))
// 	{
// 		bytes_read = read(fd, buffer, BUFFER_SIZE);
// 		if (bytes_read <= 0)
// 		{
// 			free(buffer);
// 			return (NULL);
// 		}
// 		// buffer[bytes_read + 1] = '\0';
// 	}
// 	next_line = copy_n_shift(buffer);
// 	if (!next_line)
// 	{
// 		free(buffer);
// 		return (NULL);
// 	}
// 	if (next_line[line_length(next_line) - 1] != '\n')
// 	{
// 		joined_line = extract_rest(next_line, buffer, fd);
// 		if (!joined_line)
// 		{
// 			free(buffer);
// 			return (NULL);
// 		}
// 		next_line = joined_line;
// 	}
// 	return (next_line);
// }
