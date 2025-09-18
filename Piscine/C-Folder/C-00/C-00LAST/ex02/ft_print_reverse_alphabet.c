/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_reverse_alphabet.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberthal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 22:40:13 by nberthal          #+#    #+#             */
/*   Updated: 2024/09/06 09:48:22 by nberthal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_print_reverse_alphabet(void)
{	
	char	b;

	b = 'z';
	while (b >= 'a')
	{
		write(1, &b, 1);
		b--;
	}
}

/*
int main(void)
{
	ft_print_reverse_alphabet();
	return 0;
}
*/
