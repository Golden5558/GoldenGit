/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberthal <nberthal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 23:15:43 by nberthal          #+#    #+#             */
/*   Updated: 2025/05/07 23:48:13 by nberthal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "phonebook.hpp"

void printField(std::string str)
{
	if (str.size() >= 10)
		std::cout << std::setw(9);
	else
		std::cout << std::setw(10);
	std::cout << str.substr(0, 9);
	if (str.size() >= 10)
		std::cout << ".";
}

static bool isAllPrintable(const std::string& str) {
    for (size_t i = 0; i < str.length(); ++i) {
        if (!std::isprint(static_cast<unsigned char>(str[i]))) {
            return false;
        }
    }
    return true;
}

static bool isAllDigits(const std::string& str) {
    for (size_t i = 0; i < str.length(); ++i) {
        if (!std::isdigit(static_cast<unsigned char>(str[i]))) {
            return false;
        }
    }
    return true;
}

void	setContactInfo(std::string & to_set, const bool is_number)
{
	while (1)
	{
		if (!std::getline(std::cin, to_set))
		{
			if (std::cin.eof()) {
				std::cout << std::endl;
				throw std::runtime_error("[EOF detected - exiting]");
			}
		}
		if (to_set.length() > 0 && isAllPrintable(to_set))
		{
			if (is_number == true && isAllDigits(to_set))
				break;
			else if (is_number == false)
				break;
		}
		std::cin.clear();
		std::cout << YELLOW << "[Input error — try again]" << RESET << std::endl;
	}
	return ;
}
