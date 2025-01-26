/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberthal <nberthal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 11:43:06 by nberthal          #+#    #+#             */
/*   Updated: 2025/01/26 10:27:10 by nberthal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <limits.h>
# include <stdarg.h>
# include <unistd.h>

typedef struct s_pile
{
	int				content;
	int				index;
	int				op_cost;
	int				index_target;
	int				target;
	struct s_pile	*target_n;
	struct s_pile	*prev;
	struct s_pile	*next;
}	t_pile;

int		ft_isalnum(int c);
int		ft_isalpha(int c);
int		ft_isascii(int c);
int		ft_isdigit(int c);
int		ft_isprint(int c);
int		ft_toupper(int c);
int		ft_tolower(int c);
int		ft_atoi_verif(const char *nptr, int *valid);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
char	*ft_strdup(const char *s);
char	*ft_strnstr(const char *big, const char *little, size_t len);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	**ft_split(char const *s, char c);
char	*ft_itoa(int n);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void	ft_bzero(void *s, size_t n);
void	ft_striteri(char *s, void (*f)(unsigned int, char *));
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
void	*ft_memset(void *s, int c, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);
void	*ft_calloc(size_t nmemb, size_t size);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
size_t	ft_strlen(const char *s);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
size_t	ft_strlcat(char *dest, char *src, size_t size);
void	ft_putnbr_base(long long nbr, char *base);
int		ft_printf(const char *args, ...)__attribute__((format(printf, 1, 2)));
int		ft_print_hex_uint(char arg, va_list ap);
int		ft_getdec(int n, int base);

//	Lst functions :

t_pile	*ft_lstnew(int content, int index);
t_pile	*ft_lstlast(t_pile *lst);
t_pile	*ft_lstmap(t_pile *lst, int (*f)(int));
void	ft_lstadd_back(t_pile **lst, t_pile *new);
void	ft_lstadd_front(t_pile **lst, t_pile *new);
int		ft_lstsize(t_pile *lst);
void	ft_lstdelone(t_pile *lst);
void	ft_lstclear(t_pile **lst);
void	ft_lstiter(t_pile *lst, void (*f)(int));

#endif