/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Point.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: golden <golden@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 16:48:51 by golden            #+#    #+#             */
/*   Updated: 2025/08/21 02:22:17 by golden           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef POINT_H
# define POINT_H

#include "../includes/Fixed.hpp"

class Point {

	public :

		~Point();
		Point();
		Point(Point const & other);
		Point(float const x, float const y);
		Point & operator=(Point const & other);

		Fixed const	orientationVector(Point const, Point const) const; 
		Fixed const	side_from_vector(Point const, Point const, Point const) const;

	private :
	
		Fixed const _x;
		Fixed const _y;
};

bool	bsp(Point const a, Point const b, Point const c, Point const point);

#endif