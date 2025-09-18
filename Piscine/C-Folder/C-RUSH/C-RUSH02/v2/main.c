/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduarte <vduarte@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 11:49:45 by vduarte           #+#    #+#             */
/*   Updated: 2024/09/22 22:18:16 by vduarte          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft.h"

int	main(int argc, char *argv[])
{
	char	*dico;

	if (argc == 2 && verif_arg(argv[1]))
	{
		dico = make_dictionnary("numbers.dict");
		decompose_nb(dico, argv[1]);
	}
	else if (argc == 3 && verif_arg(argv[2]))
	{
		dico = make_dictionnary(argv[1]);
		decompose_nb(dico, argv[2]);
	}
	else
	{
		ft_putstr("Error\n");
		return (0);
	}
	free (dico);
}
