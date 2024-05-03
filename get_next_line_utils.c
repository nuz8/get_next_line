/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamatya <pamatya@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 16:34:09 by pamatya           #+#    #+#             */
/*   Updated: 2024/05/01 17:40:18 by pamatya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	f_strlen(const char *str);								//
int		line_length(char *str);
char	*f_strjoin(char const *s1, char const *s2);

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
int line_length(char *str)
{
	int	i;

	i = 0;
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
char	*f_strjoin(char const *s1, char const *s2)
{
	char	*j_str;
	size_t	len;
	size_t	i;

	len = f_strlen(s1) + f_strlen(s2);
	j_str = (char *)malloc((len + 1) * sizeof(char));
	if (!j_str)
		return (NULL);
	i = 0;
	while (i < len)
	{
		if (i < f_strlen(s1))
			j_str[i] = s1[i];
		else
			j_str[i] = *s2++;
		i++;
	}
	j_str[i] = '\0';
	return (j_str);
}
