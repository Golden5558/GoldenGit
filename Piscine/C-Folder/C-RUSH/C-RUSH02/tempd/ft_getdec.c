/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getdec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberthal <nberthal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 15:24:19 by nberthal          #+#    #+#             */
/*   Updated: 2024/09/22 20:42:30 by nberthal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char *ft_getdec(int dec)
{
	char *dec;
	int i;

	i = 0;
	dec = malloc((dec + 1) * sizeof(char));
	if (!dec)
		return (NULL);
	dec++ = '1';
	while (dec[i])
		dec[i++] = '0';
	return (dec);
}