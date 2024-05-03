/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamatya <pamatya@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 16:34:09 by pamatya           #+#    #+#             */
/*   Updated: 2024/05/03 16:58:01 by pamatya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	f_strlen(const char *str);								//
size_t line_length(char *str);
char	*f_strjoin(char *s1, char *s2);

// Conventional strlen function
size_t	f_strlen(const char *str)								//
{
	size_t	len;

	len = 0;
	while (*str++)
		len++;
	return (len);
}

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
char	*f_strjoin(char *s1, char *s2)
{
	char	*joined_str;
	size_t	len;
	size_t	i;
	char	*s2_ptr;

	len = line_length(s1) + line_length(s2);
	joined_str = (char *)malloc((len + 1) * sizeof(char));
	if (!joined_str)
		return (NULL);
	i = 0;
	s2_ptr = s2;
	while (i < len)
	{
		if (i < line_length(s1))
			joined_str[i] = s1[i];
		else
			joined_str[i] = *s2++;
		i++;
	}
	joined_str[i] = '\0';
	free(s1);
	free(s2_ptr);
	return (joined_str);
}
