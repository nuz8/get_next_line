/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamatya <pamatya@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 20:41:06 by pamatya           #+#    #+#             */
/*   Updated: 2024/03/27 19:06:15 by pamatya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_toupper(int c)
{
	unsigned char	letter;

	letter = (unsigned char)c;
	if (letter >= 'a' && letter <= 'z')
		c -= 32;
	return (c);
}
