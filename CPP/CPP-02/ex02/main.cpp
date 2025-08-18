/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: golden <golden@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 14:49:53 by golden            #+#    #+#             */
/*   Updated: 2025/08/18 16:37:16 by golden           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/Fixed.hpp"

int main(void) {

	// Subject test example :

	std::cout << YELLOW << "Output example from subject :\n" << RESET << std::endl;

	Fixed a;
	Fixed const b(Fixed(5.05f) * Fixed(2));
	std::cout << a << std::endl;
	std::cout << ++a << std::endl;
	std::cout << a << std::endl;
	std::cout << a++ << std::endl;
	std::cout << a << std::endl;
	std::cout << b << std::endl;
	std::cout << Fixed::max( a, b ) << std::endl;

	// My own tests :

	std::cout << std::endl << GREEN << "Compare operators :\n" << RESET << std::endl;

	Fixed low(2);
	Fixed high(8);
	
	low < high;
	low > high;
	
	low.setRawBits(8 / 256);
	
	low >= high;		
	low <= high;		
	low == high;		
	low != high;		

	std::cout << std::endl << RED << "Min / Max Member functions :\n" << RESET << std::endl;

	std::cout << RESET << Fixed::min(low, high) << std::endl;
	std::cout << RESET << Fixed::max(low, high) << std::endl << std::endl;

	Fixed const low_const(1);
	Fixed const high_const(5);

	std::cout << RESET << Fixed::min(low_const, high_const) << std::endl;
	std::cout << RESET << Fixed::max(low_const, high_const) << RESET << std::endl;

	std::cout << std::endl << MAGENTA << "Calcul operators :\n" << RESET << std::endl;

	Fixed c(3);
	Fixed d(4);

	std::cout << c << " + " << d << " = " << c + d << std::endl;
	std::cout << c << " - " << d << " = " << c - d << std::endl;
	std::cout << c << " * " << d << " = " << c * d << std::endl;
	std::cout << c << " / " << d << " = " << c / d << std::endl;

	std::cout << std::endl << MAGENTA << "Increment / Decrement operators :\n" << RESET << std::endl;

	std::cout << "Before Pre-increment : " << MAGENTA << c << RESET << std::endl;
	
	std::cout << "Pre-increment : " << MAGENTA << ++c << RESET << std::endl;
	std::cout << "Post-increment : " << MAGENTA << c++ << RESET << std::endl;
	std::cout << "Post-increment : " << MAGENTA << c++ << RESET << std::endl;
	std::cout << "Pre-decrement : " << MAGENTA << --c << RESET << std::endl;
	std::cout << "Post-decrement : " << MAGENTA << c-- << RESET << std::endl;
	std::cout << "Post-decrement : " << MAGENTA << c-- << RESET << std::endl;

	std::cout << "After post-decrement : " << MAGENTA << c << RESET << std::endl;

	return 0;
}