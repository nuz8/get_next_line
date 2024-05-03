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

char	*get_next_line(int fd);

char	*copy_n_shift(char *buffer);

size_t	f_strlen(const char *str);
size_t	line_length(char *str);
char	*join_parts(char *s1, char *s2);


#endif