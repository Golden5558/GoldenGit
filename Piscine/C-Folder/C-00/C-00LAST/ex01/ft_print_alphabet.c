/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_alphabet.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberthal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 22:40:13 by nberthal          #+#    #+#             */
/*   Updated: 2024/09/05 11:10:55 by nberthal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_print_alphabet(void)
{	
	char	b;

	b = 'a';
	while (b <= 'z')
	{
		write(1, &b, 1);
		b++;
	}
}

/*
int main(void)
{
	ft_print_alphabet();
	return 0;
}
*/
