/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberthal <nberthal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 22:01:45 by nberthal          #+#    #+#             */
/*   Updated: 2024/10/28 03:50:08 by nberthal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>

int	ft_printf(const char *args, ...);
int	ft_print_str(va_list ap, int *e);
int	ft_print_decimal(va_list ap, int *e);
int	ft_print_char(va_list ap, int *e);
int	ft_print_hexa(const char *args, va_list ap, int *e);
int	ft_print_unsigned_decimal(va_list ap, int *e);
int	ft_print_memory(va_list ap, int *e);

#endif