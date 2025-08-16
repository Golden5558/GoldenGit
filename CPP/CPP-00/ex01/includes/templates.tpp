/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   templates.tpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberthal <nberthal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 15:03:35 by nberthal          #+#    #+#             */
/*   Updated: 2025/05/07 18:20:12 by nberthal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEMPLATES_H
# define TEMPLATES_H

# include <sstream>

template <typename T, typename Dest>
bool convert(const T& src, Dest & dest)
{
	std::stringstream ss;
	ss << src;
	ss >> dest;
	return !ss.fail() && ss.eof();
};

#endif