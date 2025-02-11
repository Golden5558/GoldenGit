/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fprintf_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberthal <nberthal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 10:14:38 by nberthal          #+#    #+#             */
/*   Updated: 2025/02/11 01:57:54 by nberthal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_print_ptr(FILE *stream, void *ptr)
{
	unsigned long	num;
	int				c;

	c = 0;
	num = (unsigned long)ptr;
	if (num == 0)
		return (fwrite("(nil)", 1, 5, stream));
	c += fwrite("0x", 1, 2, stream);
	fputnbr_base(stream, num, "0123456789abcdef");
	return (c + ft_getdec(num, 16));
}

static int	ft_print_hex_uint(FILE *stream, char arg, va_list ap)
{
	unsigned int	num;

	if (arg == 'u')
	{
		num = va_arg(ap, unsigned int);
		fputnbr_base(stream, (unsigned long)num, "0123456789");
		return (ft_getdec(num, 10));
	}
	if (arg == 'p')
		return (ft_print_ptr(stream, va_arg(ap, void *)));
	num = va_arg(ap, unsigned int);
	if (arg == 'x')
		fputnbr_base(stream, (unsigned long)num, "0123456789abcdef");
	if (arg == 'X')
		fputnbr_base(stream, (unsigned long)num, "0123456789ABCDEF");
	return (ft_getdec(num, 16));
}

int	ft_fprint_num(FILE *stream, char arg, va_list ap)
{
	int	c;
	int	num;

	c = 0;
	if (ft_strchr("di", arg))
	{
		num = va_arg(ap, int);
		if (num < 0)
		{
			ft_fputchar(stream, '-');
			c++;
			fputnbr_base(stream, (long)(-num), "0123456789");
			return (c + ft_getdec(-num, 10));
		}
		else
		{
			fputnbr_base(stream, (long)num, "0123456789");
			return (ft_getdec(num, 10));
		}
	}
	else if (arg == 'u' || arg == 'x' || arg == 'X' || arg == 'p')
		return (ft_print_hex_uint(stream, arg, ap));
	return (0);
}
