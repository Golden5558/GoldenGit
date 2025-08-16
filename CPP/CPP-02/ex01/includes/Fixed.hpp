/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: golden <golden@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 14:51:15 by golden            #+#    #+#             */
/*   Updated: 2025/08/16 18:40:12 by golden           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIXED_H
# define FIXED_H

# include <cmath>
# include <string.h>
# include <iostream>
# include <iomanip>
# include <sstream>

# define RESET   "\033[0m"
# define YELLOW  "\033[33m"
# define RED     "\033[31m"
# define CYAN    "\033[36m"
# define BLACK   "\033[30m"
# define GREEN   "\033[32m"
# define MAGENTA "\033[35m"

class Fixed {

	public :

		Fixed();
		~Fixed();
		Fixed(Fixed const & other);
		Fixed & operator=(Fixed const & rhs);

		Fixed(const int);
		Fixed(const float);

		int		getRawBits(void) const;
		void	setRawBits(int const raw);

		int		toInt(void) const;
		float	toFloat(void) const;

	private :
		
		int					_fixed_value;
		static const int	_fractional_bit = 8; 

};

std::ostream & operator<<(std::ostream & o, Fixed const & rhs);

#endif