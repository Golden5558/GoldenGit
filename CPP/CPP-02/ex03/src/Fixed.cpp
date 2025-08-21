/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: golden <golden@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 14:51:13 by golden            #+#    #+#             */
/*   Updated: 2025/08/21 01:51:41 by golden           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Fixed.hpp"

/******************************************************************************/
/*                             CANNONICAL FORM		                          */
/******************************************************************************/

Fixed::Fixed() : _fixed_value(0) {
	
}

Fixed::Fixed(Fixed const & other) {
	
	*this = other;
}

Fixed::~Fixed() {
	
}

Fixed & Fixed::operator=(Fixed const & rhs) {
	
	if (this != &rhs)
		this->_fixed_value = rhs.getRawBits();
	return *this;
}

/******************************************************************************/
/*                             NEW CONSTUCTORS		                          */
/******************************************************************************/

Fixed::Fixed(int const o) {
	
	this->_fixed_value = o << this->_fractional_bit;
}

Fixed::Fixed(float const o) {

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

Fixed & Fixed::min(Fixed & lhs, Fixed & rhs) {

	if (lhs.getRawBits() < rhs.getRawBits())
		return lhs;
	else
		return rhs;
}

Fixed const & Fixed::min(Fixed const & lhs, Fixed const & rhs) {

	if (lhs.getRawBits() < rhs.getRawBits())
		return lhs;
	else
		return rhs;
}

Fixed & Fixed::max(Fixed & lhs, Fixed & rhs) {

	if (lhs.getRawBits() > rhs.getRawBits())
		return lhs;
	else
		return rhs;
}

Fixed const & Fixed::max(Fixed const & lhs, Fixed const & rhs) {

	if (lhs.getRawBits() > rhs.getRawBits())
		return lhs;
	else
		return rhs;
}

/******************************************************************************/
/*                             OPERATOR OVERLOAD	                          */
/******************************************************************************/

// Compare operators

bool Fixed::operator>(Fixed const & rhs) const {

	if (this->_fixed_value > rhs._fixed_value)
		return true;
	return false;
}

bool Fixed::operator<(Fixed const & rhs) const {

	if (this->_fixed_value < rhs._fixed_value)
		return true;
	return false;
}

bool Fixed::operator>=(Fixed const & rhs) const {

	if (this->_fixed_value >= rhs._fixed_value)
		return true;
	return false;
}

bool Fixed::operator<=(Fixed const & rhs) const {

	if (this->_fixed_value <= rhs._fixed_value)
		return true;
	return false;
}

bool Fixed::operator==(Fixed const & rhs) const {

	if (this->_fixed_value == rhs._fixed_value)
		return true;
	return false;
}

bool Fixed::operator!=(Fixed const & rhs) const {

	if (this->_fixed_value != rhs._fixed_value)
		return true;
	return false;
}

// Calcul operators

Fixed Fixed::operator+(Fixed const & rhs) const {

	Fixed add;
	add.setRawBits(this->_fixed_value + rhs._fixed_value);
	return add;
}

Fixed Fixed::operator-(Fixed const & rhs) const {

	Fixed substract;
	substract.setRawBits(this->_fixed_value - rhs._fixed_value);
	return substract;
}

Fixed Fixed::operator*(Fixed const & rhs) const {
	
	Fixed			multiply;
	long long		res = static_cast<long long>(this->_fixed_value * rhs._fixed_value);
	multiply.setRawBits(static_cast<int>(res >> _fractional_bit));
	return multiply;
}

Fixed Fixed::operator/(Fixed const & rhs) const {

	Fixed divide;
	if (rhs._fixed_value == 0) {
		std::cerr << "Division par zero" << std::endl;
		divide.setRawBits(0);
		return divide;
	}
	long long res = static_cast<long long>(this->_fixed_value / rhs._fixed_value);
	divide.setRawBits(static_cast<int>(res << _fractional_bit));
	return divide;
}

// Increment / Decrement Operator

Fixed & Fixed::operator++() {

	this->_fixed_value += 1;
	return *this;
}

Fixed & Fixed::operator--() {

	this->_fixed_value -= 1;
	return *this;
}

Fixed Fixed::operator++(int ghost) {

	(void)ghost;
	Fixed	ret;
	ret.setRawBits(this->_fixed_value);
	this->_fixed_value += 1;
	return ret;
}

Fixed Fixed::operator--(int ghost) {

	(void)ghost;
	Fixed	ret;
	ret.setRawBits(this->_fixed_value);
	this->_fixed_value -= 1;
	return ret;
}

// Ostream Operator

std::ostream & operator<<(std::ostream & o, Fixed const & rhs) {

	o << rhs.toFloat();
	
	return o;
}
