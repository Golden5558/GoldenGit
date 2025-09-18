/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberthal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 13:27:57 by nberthal          #+#    #+#             */
/*   Updated: 2024/09/21 14:47:10 by nberthal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

int	main(void)
{
	int i = 0;
	int j = 0;
	int file;
	int t;
	char c[800];

	file = open("numbers.dict", O_RDONLY);
	printf("file == %d\n", file);
	if (file != 3)
		return (1);
	t = read(file, c, 800);
	printf("%d\n%s\n\n", t, c);
	while (i < 8)
	{
		if (c[j] == '\n')
			i++;
		j++;
	}
	while (c[j] != '\n')
	{
		write(1, &c[j], 1);
		j++;
	}
}
