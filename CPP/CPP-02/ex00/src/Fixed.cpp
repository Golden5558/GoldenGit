/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: golden <golden@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 14:51:13 by golden            #+#    #+#             */
/*   Updated: 2025/08/16 17:12:47 by golden           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Fixed.hpp"

Fixed::Fixed() : _fixed_value(0) {
	
	std::cout << "Default constructor called" << std::endl;
	
}

Fixed::Fixed(Fixed const  & other) {
	
	std::cout << "Copy constructor called" << std::endl;

	*this = other;
}

Fixed::~Fixed() {
	
	std::cout << "Default destructor called" << std::endl;
	
}

Fixed & Fixed::operator=(Fixed const & rhs) {
	
	
	std::cout << "Copy assignement operator called" << std::endl;

	if (this != &rhs)
		this->_fixed_value = rhs.getRawBits();
	return *this;
}

int		Fixed::getRawBits(void) const {	

	std::cout << "getRawBits member function called" << std::endl;
	
	return this->_fixed_value;
}


void	Fixed::setRawBits(int const raw) {

	this->_fixed_value = raw;	

}