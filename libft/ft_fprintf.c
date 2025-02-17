/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberthal <nberthal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 06:08:43 by nberthal          #+#    #+#             */
/*   Updated: 2025/02/11 01:23:48 by nberthal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_print_chars(FILE *stream, char arg, va_list ap)
{
	char	*str;

	if (arg == 's')
	{
		str = va_arg(ap, char *);
		if (!str)
			return (fwrite("(null)", 1, 6, stream));
		ft_fputstr(stream, str);
		return (ft_strlen(str));
	}
	else if (arg == 'c')
	{
		ft_fputchar(stream, va_arg(ap, int));
		return (1);
	}
	return (0);
}

static int	ft_printarg(FILE *stream, const char *args, va_list ap)
{
	char	format;

	format = args[1];
	if (ft_strchr("diuxXp", format))
		return (ft_fprint_num(stream, format, ap));
	if (ft_strchr("cs", format))
		return (ft_print_chars(stream, format, ap));
	if (format == '%')
		return (fwrite("%", 1, 1, stream));
	return (0);
}

int	ft_fprintf(FILE *stream, const char *args, ...)
{
	va_list	ap;
	int		c;

	c = 0;
	if (!args)
		return (-1);
	va_start(ap, args);
	while (*args)
	{
		if (*args == '%' && ft_strchr("cspdiuxX%", *(args + 1)))
		{
			c += ft_printarg(stream, args, ap);
			args += 2;
		}
		else if (*args == '%' && !ft_strchr("cspdiuxX%", *(args + 1)))
			return (-1);
		else
			c += fwrite(args++, 1, 1, stream);
	}
	return (va_end(ap), c);
}
