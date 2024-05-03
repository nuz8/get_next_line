/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamatya <pamatya@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 16:07:26 by pamatya           #+#    #+#             */
/*   Updated: 2024/05/03 17:07:19 by pamatya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// Tester main function
int main(void)
{
	int		fd;
	char	*line;
	int		loop;
	
	loop = 5;
	fd = open("file0.txt", O_RDONLY);
	while (loop--)
	{
		line = get_next_line(fd);
		if (!line)
			return (-40);
		printf("%s", line);
	}
	
	free(line);
	return (0);
}
