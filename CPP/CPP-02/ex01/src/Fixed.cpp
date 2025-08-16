/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: golden <golden@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 14:51:13 by golden            #+#    #+#             */
/*   Updated: 2025/08/16 19:11:26 by golden           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Fixed.hpp"

/******************************************************************************/
/*                             CANNONICAL FORM		                          */
/******************************************************************************/

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

/******************************************************************************/
/*                             NEW CONSTUCTORS		                          */
/******************************************************************************/

Fixed::Fixed(int const o) {
	
	std::cout << "Int constructor called" << std::endl;

	this->_fixed_value = o << this->_fractional_bit;
}

Fixed::Fixed(float const o) {

	std::cout << "Float constructor called" << std::endl;

	this->_fixed_value = roundf(o * (1 << this->_fractional_bit));
}

/******************************************************************************/
/*                             MEMBER FUNCTIONS		                          */
/******************************************************************************/

int		Fixed::getRawBits(void) const {	

	return this->_fixed_value;
}


void	Fixed::setRawBits(int const raw) {

	this->_fixed_value = raw;	

}

int	Fixed::toInt(void) const {
	
	return this->_fixed_value >> this->_fractional_bit;
}

float	Fixed::toFloat(void) const {
	
	return static_cast<float>(this->_fixed_value) / (1 << this->_fractional_bit);
}

/******************************************************************************/
/*                             OPERATOR OVERLOAD	                          */
/******************************************************************************/

std::ostream & operator<<(std::ostream & o, Fixed const & rhs) {

	o << rhs.toFloat();
	
	return o;
}
