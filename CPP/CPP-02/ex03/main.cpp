/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: golden <golden@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 14:49:53 by golden            #+#    #+#             */
/*   Updated: 2025/08/21 02:36:20 by golden           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/Fixed.hpp"
#include "includes/Point.hpp"

int main(void) {

	Point const a(0, 0);
	Point const b(6, 0);
	Point const c(3, 5);
	Point const point(3.0f, 1.2f);

	if (bsp(a, b, c, point))
		std::cout << GREEN << "Point is inside abc !" << RESET << std::endl;
	else
		std::cout << RED << "Point is not inside abc !" << RESET << std::endl;

	return 0;
}