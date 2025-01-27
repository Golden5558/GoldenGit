/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberthal <nberthal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 05:19:09 by nberthal          #+#    #+#             */
/*   Updated: 2024/12/04 20:56:30 by nberthal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <limits.h>

int	main(void)
{
	char a = 'a';
	printf(" = a");
	ft_putnbr_base((int)a, "01");
	printf("\n");
	a = 'N';
	printf(" = N");
	ft_putnbr_base((int)a, "01");
	printf("\n");
	a = 'V';
	printf(" = V");
	ft_putnbr_base((int)a, "01");
	printf("\n");
	a = '\\';
	printf(" = \\");
	ft_putnbr_base((int)a, "01");
}
// ft_lstmap

// void	*map_length(void *s)
// {
// 	char	*str;

// 	str = malloc(30);
// 	if (str != NULL)
// 		sprintf(str, "__%lX", strlen((char *)s));
// 	return (str);
// }

// void	delete(void *content)
// {
// 	char	*str;

// 	str = (char *)content;
// 	if (str == NULL)
// 		return ;
// 	free(content);
// }

// int	main(void)
// {
// 	t_list	*s;
// 	t_list	*t;
// 	t_list	*y;

// 	s = ft_lstnew(ft_strdup("1"));
// 	t = s;
// 	printf("Element %s\n", (char *)s->content);
// 	s->next = ft_lstnew(ft_strdup("2"));
// 	s = s->next;
// 	printf("Element %s\n", (char *)s->content);
// 	s->next = ft_lstnew(ft_strdup("3"));
// 	s = s->next;
// 	printf("Element %s\n", (char *)s->content);
// 	y = ft_lstmap(t, map_length, delete);
// 	ft_lstclear(&t, delete);
// 	ft_lstclear(&y, delete);
// }

// ft_atoi

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

// ft_bzero

// int	main(void)
// {
// 	char str[] = "voic une string";
// 	int i = 0;
// 	int n = 6;
// 	ft_bzero(str, n);
// 	while (i <= 15)
// 		write(1, &str[i++], 1);
// 	i = 0;
// 	bzero(str, n);
// 	while (i <= 15)
// 		write(1, &str[i++], 1);
// }

// ft_calloc

// int	main(void)
// {
// 	size_t	nmemb = 5;
// 	size_t	size = 2;

// 	unsigned char	*ar;
// 	ar = ft_calloc(nmemb, size);
// 	size_t i = 0;
// 	while (i < nmemb)
// 		write(1, &ar[i++], size);
// 	printf("%p", ar);
// 	free (ar);
// 
	// unsigned char	*ar1;
	// ar1 = calloc(nmemb, size);
	// size_t j = 0;
	// while (j < nmemb)
	// 	write(1, &ar1[j++], size);
	// printf("%p", ar1);
	// free (ar1);
// }

// ft_isalnum

// int	main(void)
// {
// 	printf("%d\n", ft_isalnum(65));
// 	printf("%d\n", isalnum(65));
// }

// ft_isalpha

// int	main(void)
// {
// 	printf("%d\n", ft_isalpha(99));
// 	printf("%d\n", isalpha(99));
// }

// ft_isascii

// int	main(void)
// {
// 	printf("%d\n", ft_isascii(52));
// 	printf("%d\n", isascii(52));
// }

// ft_isdigit

// int	main(void)
// {
// 	printf("%d\n", ft_isdigit(54));
// 	printf("%d\n", isdigit(54));
// }

// ft_isprint

// int	main(void)
// {
// 	int	i = 0;
// 	while (i < 300)
// 	{
// 		printf("%d", ft_isprint(i));
// 		printf("  --->  %d\n", isprint(i));
// 		i++;
// 	}
// }

// ft_itoa

// int	main(void)
// {
// 	int i = 0;
// 	printf("%s\n", ft_itoa(52));
// 	printf("%s\n", ft_itoa(-2147483648));
// 	printf("%s\n", ft_itoa(-5522));
// 	printf("%s\n", ft_itoa(0));
// 	char *s = ft_itoa(0);
// 	while (i < ft_getdec(0) + 1)
// 		write(1, &s[i++], 1);
// }

// ft_lstaddback

// int	main(void)
// {
// 	t_list	*l;
// 	t_list	*n;

// 	n = malloc(sizeof(t_list));
// 	l = NULL;
// 	n->next = NULL;
// 	n->content = ft_strdup("OK");
// 	ft_lstadd_back(&l, n);
// 	printf("%s\n", (char *)l->content);
// }

// ft_lstadd_front

// ft_lstclear

// ft_lstdelone

// ft_lstiter

// ft_lstlast

// ft_lstnew

// int	main(void)
// {
// 	printf("%s\n", (char *)ft_lstnew("Voici une string")->content);
// }

// ft_lstsize

// ft_memchr

// int	main(void)
// {
// 	const unsigned char s[] = "je Aherche A";

// 	printf("%p\n", ft_memchr(s, 65, 5));
// 	printf("%p\n", memchr(s, 65, 5));
// }

// ft_memcmp

// int	main(void)
// {
// 	int r;
// 	unsigned int c = 3;
// 	char a[] = "ABC";
// 	char b[] = "AbC";
// 	char d[] = "ABC";

// 	r = ft_memcmp(a, b, c);
// 	printf("ft_memcmp(a, b, %u) = %d\n", c, r);
// 	r = ft_memcmp(a, d, c);
// 	printf("ft_memcmp(a, d, %u) = %d\n", c, r);
// 	r = ft_memcmp(b, d, c);
// 	printf("ft_memcmp(b, d, %u) = %d\n", c, r);

// 	printf("Official memcmp:\n");

// 	r = memcmp(a, b, c);
// 	printf("memcmp(a, b, %u) = %d\n", c, r);
// 	r = memcmp(a, d, c);
// 	printf("memcmp(a, d, %u) = %d\n", c, r);
// 	r = memcmp(b, d, c);
// 	printf("memcmp(b, d, %u) = %d\n", c, r);

// 	return 0;
// }

// ft_memcpy

// int	main(void)
// {
	// char src[] = "voici une string";
	// char dest[50];
	// char src1[] = "voici une string";
	// char dest1[50];
	// size_t i = 8;
	// ft_memcpy(dest, src, i);
	// memcpy(dest1, src1, i);
	// printf("Mon memcpy : %s\n", dest);
	// 	printf("Le memcpy : %s\n", dest1);
	// ft_memcpy(((void*)0), ((void*)0), 3);
	// memcpy(((void*)0), ((void*)0), 3);
// }

// ft_memmove

// int	main(void)
// {
// 	char src[] = "voici une string";
// 	char src1[] = "voici une string";
// 	size_t i = 4;
// 	char dest[50];
// 	char dest1[50];

// 	// Test 1: Overlapping regions
// 	printf("Test 1: Overlapping regions\n");
// 	ft_memmove(&src[5], src, i);
// 	memmove(&src1[5], src1, i);
// 	printf("mon memmove : %s\n", src);
// 	printf("the memmove : %s\n", src1);

// 	// Test 2: Non-overlapping regions
// 	printf("\nTest 2: Non-overlapping regions\n");
// 	ft_memmove(dest, src, i);
// 	memmove(dest1, src1, i);
// 	printf("mon memmove : %s\n", dest);
// 	printf("the memmove : %s\n", dest1);

// 	// Test 3: Entire string
// 	printf("\nTest 3: Entire string\n");
// 	ft_memmove(dest, src, strlen(src) + 1);
// 	memmove(dest1, src1, strlen(src1) + 1);
// 	printf("mon memmove : %s\n", dest);
// 	printf("the memmove : %s\n", dest1);

// 	return 0;
// }
// int	main(void)
// {
// 	char *src = NULL;
// 	char *dest = NULL;
// 	size_t n = 5;

// 	// Test 1: Both src and dest are NULL
// 	printf("Test 1: Both src and dest are NULL\n");
// 	printf("mon memmove : %p\n", ft_memmove(dest, src, n));
// 	printf("the memmove : %p\n", memmove(dest, src, n));

// 	// Test 2: src is NULL
// 	dest = malloc(n);
// 	printf("\nTest 2: src is NULL\n");
// 	printf("mon memmove : %p\n", ft_memmove(dest, src, n));
// 	printf("the memmove : %p\n", memmove(dest, src, n));
// 	free(dest);

// 	// Test 3: dest is NULL
// 	src = malloc(n);
// 	printf("\nTest 3: dest is NULL\n");
// 	printf("mon memmove : %p\n", ft_memmove(dest, src, n));
// 	printf("the memmove : %p\n", memmove(dest, src, n));
// 	free(src);

// 	return 0;
// }

// ft_memset

// int	
// int	main(void)
// {
// 	printf("%d\n", ft_toupper(97));
// }main(void)
// {
// 	char str[] = "voic une string";
// 	ft_memset(str, '4', 6);
// 	printf("%s\n", str);
// }

// ft_putchar_fd

// ft_putendl_fd

// ft_putnbr_fd

// ft_putstr_fd

// ft_split

// int	main(void)
// {
// 	char	**result;
// 	char	s[] = "      split       this for   me  !       ";
// 	char	c = ' ';
// 	size_t	i;

// 	result = ft_split(s, c);
// 	i = 0;
// 	while (i < ft_countword(s, c) + 1)
// 	{
// 		printf("%s\n", result[i]);
// 		free(result[i]);
// 		i++;
// 	}
// 	free(result);
// }
// 	result = ft_split("  Cb de mots a cette phrase", ' ');
// 	i = 0;
// 	while (result[i])
// 	{
// 		printf("%s\n", result[i]);
// 		free(result[i]);
// 		i++;
// 	}
// 	free(result);

// 	result = ft_split("    Cb de mots a cette phrase      ", ' ');
// 	i = 0;
// 	while (result[i])
// 	{
// 		printf("%s\n", result[i]);
// 		free(result[i]);
// 		i++;
// 	}
// 	free(result);

// 	return (0);
// }

// ft_strchr


// int	main(void)
// {
// 	const char s[] = "je cherche A";

// 	printf("%p\n", ft_strchr(s, 'e'));
// 	printf("%p\n", strchr(s, 'e'));
// 	printf("%p\n", ft_strchr("teste", 357));
// 	printf("%p\n", ft_strchr("teste", 1024));
// 	printf("%p\n", strchr("teste", 357));
// 	printf("%p\n", strchr("teste", 1024));
// }

// ft_strdup


// int	main(void)
// {
// 	const char	*str = "Hello, World!";
// 	char		*dup1;
// 	char		*dup2;

// 	dup1 = ft_strdup(str);
// 	dup2 = strdup(str);

// 	if (dup1 && dup2)
// 	{
// 		printf("Original string: %s\n", str);
// 		printf("ft_strdup: %s\n", dup1);
// 		printf("strdup: %s\n", dup2);
// 	}
// 	else
// 	{
// 		printf("Memory allocation failed\n");
// 	}

// 	free(dup1);
// 	free(dup2);

// 	return (0);
// }

// ft_striteri

// ft_strjoin


// int	main(void)
// {
// 	printf("%s\n", ft_strjoin("Hello ", "World !"));
// }

// ft_strlcat


// int main(void)
// {
// 	size_t siz = 0;
// 	// char init[] = "Voici le debut";
// 	// // char goal[13] = "de ma phrase.";
// 	// printf("%zu\n", ft_strlcat(NULL, init, siz));
// 	// printf("%s\n",goal);
// 	// char init2[] = "Voici le debut";
// 	char goal2[13] = "de ma phrase.";
// 	printf("%zu\n", strlcat(goal2, NULL, siz));
// 	// printf("%s\n", goal2);
// }

// ft_strlcpy


// int	main(void)
// {
// 	size_t	i = 8;
// 	char dst[50];
// 	char dst1[50];
// 	char src[] = "The phrase source";
// 	ft_strlcpy(dst, src, i);
// 	strlcpy(dst1, src, i);
// 	printf("%s    %zu\n", dst, i);
// 	printf("%s    %zu\n", dst1, i);
// }

// ft_strlen

// int	main(void)
// {
// 	printf("%zu\n", ft_strlen(NULL));
// 	printf("%zu\n", strlen(NULL));
// 	ft_strlen(NULL);
// 	strlen(NULL);
// }

// ft_strmapi


// int	main(void)
// {
// 	printf("%s\n", ft_strmapi("VOICI UNE STRING", jensairien));
// }

// ft_strncmp

// int main(void)
// {
// 	const char *str1 = "Hello";
// 	const char *str2 = "Hello";
// 	const char *str3 = "Hellp";
// 	size_t n = 5;

// 	printf("Comparing '%s' and '%s' with n=%zu\n", str1, str2, n);
// 	printf("ft_strncmp: %d\n", ft_strncmp(str1, str2, n));
// 	printf("strncmp: %d\n", strncmp(str1, str2, n));

// 	printf("Comparing '%s' and '%s' with n=%zu\n", str1, str3, n);
// 	printf("ft_strncmp: %d\n", ft_strncmp(str1, str3, n));
// 	printf("strncmp: %d\n", strncmp(str1, str3, n));

// 	return 0;
// }

// ft_strnstr

// int	main(void)
// {
// 	// const char big[] = "Hello, this is a simple string";
// 	const char little[] = "this";
// 	size_t len = 0;
// 	// char *result_ft;
// 	char *result_std;
// 	// result_ft = ft_strnstr(NULL, little, len);
// 	result_std = strnstr(NULL, little, len);
// 	// printf("%s\n", result_ft);
// 	// printf("%p\n", result_ft);
// 	printf("%s\n", result_std);
// 	printf("%p\n", result_std);
// 	return (0);
// }

// int	main(void)
// {
// 	const char *big = "Hello, this is a simple string";
// 	// const char *little = "this";
// 	size_t len = 0;
// 	// char *result_ft;
// 	char *result_std;

// 	// // Test case 1: both strings are non-NULL
// 	// result_ft = ft_strnstr(big, little, len);
// 	// result_std = strnstr(big, little, len);
// 	// printf("Test case 1:\n");
// 	// printf("ft_strnstr: %s\n", result_ft);
// 	// printf("strnstr: %s\n", result_std);

// 	// Test case 2: big is NULL
// 	// result_ft = ft_strnstr(NULL, little, len);
// 	// printf("ft_strnstr: %p\n", result_ft);
// 	// result_std = strnstr(NULL, little, len);
// 	// printf("strnstr: %p\n", result_std);

// 	// // Test case 3: little is NULL
// 	// result_ft = ft_strnstr(big, NULL, len);
// 	result_std = strnstr(big, NULL, len);
// 	// printf("Test case 3:\n");
// 	// printf("ft_strnstr: %p\n", result_ft);
// 	printf("strnstr: %p\n", result_std);

// 	// // Test case 4: both strings are NULL
// 	// result_ft = ft_strnstr(NULL, NULL, len);
// 	// result_std = strnstr(NULL, NULL, len);
// 	// printf("Test case 4:\n");
// 	// printf("ft_strnstr: %p\n", result_ft);
// 	// printf("strnstr: %p\n", result_std);

// 	return (0);
// }

// ft_strrchr

// int	main(void)
// {
// 	const char s[] = "je chArche a";

// 	printf("%p\n", ft_strrchr(s, 65));
// 	printf("%p\n", strrchr(s, 65));
// }

// ft_strtrim

// int	main(void)
// {
// 	printf("%s\n", ft_strtrim("  \t \t \n   \n\n\n\t", " \t\n"));
// 	// printf("%s\n", ft_strtrim("A   TATA   AAAA", "A   "));
// }

// ft_substr

// int main(void)
// {
// 	printf("%s\n", ft_substr("hola", 5, 50));
// 	printf("%s\n", ft_substr("hola", 5, 50));
// 	printf("%s\n", ft_substr("", 1, 1));
// 	// printf("%s\n", );
// }

// ft_tolower

// int	main(void)
// {
// 	printf("%d\n", ft_tolower(65));
// }

// ft_tolower

// int	main(void)
// {
// 	printf("%d\n", ft_toupper(97));
// }