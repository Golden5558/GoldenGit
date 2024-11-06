/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberthal <nberthal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 00:47:36 by nberthal          #+#    #+#             */
/*   Updated: 2024/11/06 05:41:10 by nberthal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int	main(void)
{
	int		file;
	int		i;
	char	*str;

	i = 0;
	file = open("numbers.dict", O_RDONLY);
	if (file == -1)
		write(1, "FUCK\n", 5);
	while (i < 42)
	{
		str = get_next_line(file);
		printf("ligne %d : %s\n", i++, str);
		free (str);
		str = NULL;
	}
}
