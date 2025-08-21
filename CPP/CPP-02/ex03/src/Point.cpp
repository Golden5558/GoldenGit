/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Point.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: golden <golden@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 16:52:11 by golden            #+#    #+#             */
/*   Updated: 2025/08/21 02:36:12 by golden           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Point.hpp"

Point::Point() : _x(0), _y(0) {	
}

Point::~Point() {
}

Point::Point(float const x, float const y) : _x(x), _y(y) {
}

Point::Point(Point const & other) : _x(other._x), _y(other._y) {
}

Point & Point::operator=(Point const & other) {

	(void)other;
	return *this;
}

Fixed const Point::orientationVector(Point const a, Point const b) const {

	Fixed const abx = b._x - a._x;
	Fixed const aby = b._y - a._x;
	Fixed const apx = this->_x - a._x;
	Fixed const apy = this->_y - a._y;

	return abx * apy - aby * apx;
}

Fixed const Point::side_from_vector(Point const a, Point const b, Point const c) const {
	

	Fixed const sc = c.orientationVector(a, b);
	Fixed const sp = this->orientationVector(a, b);

	if (sc == 0 || sp == 0)
		return 0;
	return sc * sp;
}

