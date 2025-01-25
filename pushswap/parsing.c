/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberthal <nberthal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 04:27:59 by nberthal          #+#    #+#             */
/*   Updated: 2025/01/23 16:04:44 by nberthal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	fill_a(char **args, int *valid, t_pile **a)
{
	t_pile		*tmp;
	int			i;

	i = 0;
	while (args[i])
	{
		tmp = ft_lstnew(ft_atoi_verif(args[i], valid), i);
		if (!tmp || *valid == 0)
			return (ft_lstclear(&tmp), ft_lstclear(a), 1);
		if (!(*a))
			*a = tmp;
		else
			ft_lstadd_back(a, tmp);
		i++;
	}
	return (0);
}

static int	check_no_double(t_pile	**a)
{
	t_pile	*current_check;
	t_pile	*checking;
	int		num_check;

	current_check = *a;
	while (current_check)
	{
		num_check = current_check->content;
		checking = current_check->next;
		while (checking)
		{
			if (num_check == checking->content)
				return (1);
			checking = checking->next;
		}
		current_check = current_check->next;
	}
	return (0);
}

void	check_input(char **args, t_pile **a)
{
	int	valid;

	valid = 1;
	if (!args)
		error_exit("Error parsing\n");
	if (fill_a(args, &valid, a) == 1)
	{
		ft_freeall(args);
		error_exit("Error : input invalid\n");
	}
	if (!(*a) || valid == 0)
	{
		ft_freeall(args);
		ft_lstclear(a);
		error_exit("Error : input invalid\n");
	}
	if (check_no_double(a) == 1)
	{
		ft_freeall(args);
		ft_lstclear(a);
		error_exit("Error : There was two times the same input !\n");
	}
}

static char	*pars_args(char	**argv)
{
	int		i;
	char	*temp;
	char	*args_string;

	i = 1;
	args_string = ft_strdup("");
	if (!args_string)
		return (NULL);
	while (argv[i])
	{
		temp = args_string;
		args_string = ft_strjoin(args_string, argv[i++]);
		if (!args_string)
			return (free(temp), NULL);
		free(temp);
		temp = args_string;
		args_string = ft_strjoin(args_string, " ");
		if (!args_string)
			return (free(temp), NULL);
		free(temp);
	}
	return (args_string);
}

void	pars_args_and_check_inputs(int argc, char **argv, t_pile **a)
{
	char	**args;
	char	*args_string;

	if (argc > 2)
	{
		args_string = pars_args(argv);
		if (!args_string)
			error_exit("Error parsing\n");
		args = ft_split(args_string, ' ');
		if (!args)
			error_exit("Error parsing\n");
		free(args_string);
	}
	else
	{
		args = ft_split(argv[1], ' ');
		if (!args)
			error_exit("Error parsing\n");
	}
	check_input(args, a);
	ft_freeall(args);
}
