/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberthal <nberthal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 20:57:15 by nberthal          #+#    #+#             */
/*   Updated: 2025/05/09 02:51:41 by nberthal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/Zombie.hpp"

int	main(void)
{
	Zombie* z = newZombie("newZombie");
	z->announce();

	delete z;

	randomChump("randomChump");

	return 0;
}
