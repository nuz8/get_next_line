/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamatya <pamatya@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 16:34:09 by pamatya           #+#    #+#             */
/*   Updated: 2024/05/07 19:51:02 by pamatya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// void	*ft_calloc(size_t count, size_t size);
// int		has_new_line(char *str);
size_t	line_length(char *str);
char	*join_parts(char *s1, char *s2);
char	*copy_n_shift(char *buffer);
char	*extract_rest(char *next_line, char *buffer, int fd);

// // Calloc function from Libft, but commented as GNL-makefile is already including Libft
// void	*ft_calloc(size_t count, size_t size)
// {
// 	void	*ptr;
// 	char	*wrt;
// 	size_t	byts;

// 	byts = count * size;
// 	ptr = malloc(byts);
// 	if (!ptr)
// 		return (NULL);
// 	wrt = (char *)ptr;
// 	while (byts--)
// 		*wrt++ = '\0';
// 	return (ptr);
// }

// // Function to check if the str has \n character and return 1 if it does, else 0
// int	has_new_line(char *str)
// {
// 	int	has_nl;

// 	has_nl = 0;
// 	while (*str)
// 	{
// 		if (*str == '\n')
// 		{
// 			has_nl = 1;
// 			break ;
// 		}
// 		str++;
// 	}
// 	return (has_nl);
// }

// Modified strlen function:
// Function to get the length of the string terminated by \n or \0, whichever
// occurs first, also counting the \n character if it occurs within the count.
size_t	line_length(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (*str && *str != '\n')
	{
		i++;
		str++;
	}
	if (*str == '\n')
		i++;
	return (i);
}

// Function to join two strings by allocating with malloc
char	*join_parts(char *s1, char *s2)
{
	char	*joined_str;
	char	*str_ptr[2];
	size_t	str_len[2];
	size_t	len;
	size_t	i;

	str_len[0] = line_length(s1);
	str_len[1] = line_length(s2);
	len = str_len[0] + str_len[1];
	joined_str = (char *)malloc((len + 1) * sizeof(char));
	if (!joined_str)
		return (NULL);
	i = 0;
	str_ptr[0] = s1;
	str_ptr[1] = s2;
	while (i < str_len[0])
		joined_str[i++] = *s1++;
	while (i >= str_len[0] && i < len)
		joined_str[i++] = *s2++;
	joined_str[i] = '\0';
	return (free(str_ptr[0]), free(str_ptr[1]), joined_str);
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

// Function to extract the rest part of the next line with buffer as array
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
			return (next_line);
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

// // Function to extract the rest part of the next line with calloc'd buffer
// char	*extract_rest(char *next_line, char *buffer, int fd)
// {
// 	ssize_t	bytes_read;
// 	char	*line_part;
// 	char	*joined_line;

// 	while (next_line[line_length(next_line) - 1] != '\n')
// 	{
// 		bytes_read = read(fd, buffer, BUFFER_SIZE);
// 		if (bytes_read < 0)
// 			return (free(next_line), NULL);
// 		else if (bytes_read == 0)
// 		{
// 			// free(buffer);
// 			return (next_line);	// Check that everything is freed correctly in this case where the last long line is read and returned and EOF is reached before encountering \n character
// 		}
// 		buffer[bytes_read] = '\0';
// 		line_part = copy_n_shift(buffer);
// 		if (!line_part)
// 			return (free(next_line), NULL);
// 		joined_line = join_parts(next_line, line_part);
// 		if (!joined_line)
// 			return (free(next_line), free(line_part), NULL);
// 		next_line = joined_line;
// 	}
// 	return (next_line);
// }
