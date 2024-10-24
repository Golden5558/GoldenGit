/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberthal <nberthal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 20:41:06 by nberthal          #+#    #+#             */
/*   Updated: 2024/10/16 20:52:36 by nberthal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	int	minus;
	int	a;
	int	i;

	a = 0;
	i = 1;
	minus = 0;
	while (*nptr == 32 || (*nptr >= 9 && *nptr <= 13))
		nptr++;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			minus = 1;
		nptr++;
	}
	while (*nptr && *nptr >= '0' && *nptr <= '9')
		a = a * 10 + (*nptr++ - 48);
	if (minus == 1)
		a = -a;
	return (a);
}

// int main(void)
// {
// 	const char *test_str1 = "   +1234";
// 	const char *test_str2 = "42";
// 	const char *test_str3 = "   +5678";
// 	const char *test_str4 = "  - 0";
// 	const char *test_str5 = "   -0";

// 	printf("ft_atoi(\"%s\") = %d\n", test_str1, ft_atoi(test_str1));
// 	printf("atoi(\"%s\") = %d\n", test_str1, atoi(test_str1));

// 	printf("ft_atoi(\"%s\") = %d\n", test_str2, ft_atoi(test_str2));
// 	printf("atoi(\"%s\") = %d\n", test_str2, atoi(test_str2));

// 	printf("ft_atoi(\"%s\") = %d\n", test_str3, ft_atoi(test_str3));
// 	printf("atoi(\"%s\") = %d\n", test_str3, atoi(test_str3));

// 	printf("ft_atoi(\"%s\") = %d\n", test_str4, ft_atoi(test_str4));
// 	printf("atoi(\"%s\") = %d\n", test_str4, atoi(test_str4));

// 	printf("ft_atoi(\"%s\") = %d\n", test_str5, ft_atoi(test_str5));
// 	printf("atoi(\"%s\") = %d\n", test_str5, atoi(test_str5));

// 	return 0;
// }