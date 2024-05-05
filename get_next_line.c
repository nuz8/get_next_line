/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamatya <pamatya@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 14:37:49 by pamatya           #+#    #+#             */
/*   Updated: 2024/05/05 23:38:51 by pamatya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		has_new_line(char *str);
char	*copy_n_shift(char *buffer);
char	*extract_rest(char *next_line, char *buffer, int fd);
char	*get_next_line(int fd);

int	has_new_line(char *str)
{
	int	has_nl;

	has_nl = 0;
	while (*str)
	{
		if (*str == '\n')
		{
			has_nl = 1;
			break ;
		}
		str++;
	}
	return (has_nl);
}

// // Function to write the contents of the buffer to the store, shift the rest
// // of the buffer storage to the beginning, and return the the number of
// // characters copied
// int		copy_n_shift(char *buffer, char *store, int line_len)
// {
// 	char	*buf_ptr;
// 	int		copied;

// 	copied = 0;
// 	buf_ptr = buffer;
// 	while (*buffer && copied < line_len)
// 		store[copied++] = *buffer++;
// 	store[copied] = '\0';
// 	while (*buffer)
// 		*buf_ptr++ = *buffer++;
// 	*buf_ptr = *buffer;
// 	return (copied);
// }

// Function to write the contents of the buffer to a new string "store" until
// the \n character is found and shift the rest of the buffer storage to the
// beginning, or until the buffer is emptied before finding \n. Then it
// returns the new string store
char	*copy_n_shift(char *buffer)
{
	char	*line_part;
	char	*buf_ptr;
	int		index;
	int		line_len;

	if (!buffer)
		return (NULL);
	line_len = line_length(buffer);
	line_part = (char *)malloc((line_len + 1) * sizeof(char));
	if (!line_part)
		return (NULL);
	index = 0;
	buf_ptr = buffer;
	while (*buffer && index < line_len)
		line_part[index++] = *buffer++;
	line_part[index] = '\0';
	while (*buffer)
		*buf_ptr++ = *buffer++;
	*buf_ptr = *buffer;
	return (line_part);
}

char	*extract_rest(char *next_line, char *buffer, int fd)
{
	ssize_t	bytes_read;
	char	*line_part;
	char	*joined_line;

	while (next_line[line_length(next_line) - 1] != '\n')
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
			return (free(next_line), NULL);
		else if (bytes_read == 0)
		{
			// free(buffer);
			return (next_line);	// Check that everything is freed correctly in this case where the last long line is read and returned and EOF is reached before encountering \n character
		}
		buffer[bytes_read] = '\0';
		line_part = copy_n_shift(buffer);
		if (!line_part)
			return (free(next_line), NULL);
		joined_line = join_parts(next_line, line_part);
		if (!joined_line)
			return (free(next_line), free(line_part), NULL);
		next_line = joined_line;
	}
	return (next_line);
}

// Primary function to get the next line
// (version1: with buffer as char array)
char	*get_next_line(int fd)
{
	ssize_t		bytes_read;
	static char	buffer[BUFFER_SIZE + 1];
	char		*next_line;
	char		*joined_line;

	next_line = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0/* || read(fd, next_line, 0) < 0*/)
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
