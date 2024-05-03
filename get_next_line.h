/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamatya <pamatya@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 16:33:02 by pamatya           #+#    #+#             */
/*   Updated: 2024/05/01 16:33:02 by pamatya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	GET_NEXT_LINE_H
#define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>

# include "./Libft/libft.h"
#include <fcntl.h>
#include <stdio.h>

# define BUFFER_SIZE 10

char	*get_next_line(int fd);

int		write_n_shift(char *buffer, char *store, int line_len);

size_t	f_strlen(const char *str);
int		line_length(char *str);
char	*f_strjoin(char const *s1, char const *s2);


#endif