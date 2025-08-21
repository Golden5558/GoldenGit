/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsp.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: golden <golden@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 23:23:16 by golden            #+#    #+#             */
/*   Updated: 2025/08/21 02:36:08 by golden           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Point.hpp"

bool	bsp(Point const a, Point const b, Point const c, Point const point) {

	Fixed const	p_side_ab = point.side_from_vector(a, b, c);
	Fixed const	p_side_bc = point.side_from_vector(b, c, a);
	Fixed const	p_side_ca = point.side_from_vector(c, a, b);

	if ((p_side_ab > 0 && p_side_bc > 0 && p_side_ca > 0) || (p_side_ab > 0 && p_side_bc > 0 && p_side_ca > 0))
		return true;
	return false;
}