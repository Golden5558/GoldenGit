/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduarte <vduarte@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 11:03:24 by vduarte           #+#    #+#             */
/*   Updated: 2024/09/22 23:03:21 by nberthal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_H
# define FT_H
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h> //

void	ft_putchar(char c);
void	ft_putstr(char *str);
char	*ft_strstr(char *str, char *to_find);
int		ft_strlen(char *str);
char	*make_dictionnary(char *name);
int		verif_arg(char *str);
int		verif_zero(char *dico, char *str);
void	show_text_number(char *str);
char	*ft_getdec(int dec);
void	unit(char *dico, char *str, int nb);
void	decompose_nb(char *dico, char *str);

#endif
