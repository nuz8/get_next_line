/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamatya <pamatya@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 17:49:16 by pamatya           #+#    #+#             */
/*   Updated: 2024/03/27 19:03:09 by pamatya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *str, int c, size_t n)
{
	unsigned char	*s;
	unsigned char	character;

	s = (unsigned char *)str;
	character = (unsigned char)c;
	while (n)
	{
		if (*s == character)
			return ((void *)s);
		s++;
		n--;
	}
	return (NULL);
}
