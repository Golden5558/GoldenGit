/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zombieHorde.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberthal <nberthal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 02:37:17 by nberthal          #+#    #+#             */
/*   Updated: 2025/05/09 03:05:19 by nberthal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Zombie.hpp"

Zombie* zombieHorde(int N, std::string name)
{
	Zombie* H = new Zombie[N];
	for (int i = 0; i < N; ++i) {
		H[i].setName(name);
		H[i].announce();
	}
	return H;
}
