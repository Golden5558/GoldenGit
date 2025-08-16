/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   contact.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberthal <nberthal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 16:30:01 by nberthal          #+#    #+#             */
/*   Updated: 2025/05/07 23:48:05 by nberthal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "phonebook.hpp"

Contact::Contact()
{
	this->index = -1;
	this->first_name = "";
	this->last_name = "";
	this->nick_name = "";
	this->phone_number = "";
	this->darkest_secret = "";
	return ;
}

Contact::~Contact()
{
	return ;
}

Contact::Contact(int i)
{
	this->index = i;
	std::cout << "Enter First Name : ";
	setContactInfo(this->first_name, false);
	std::cout << "Enter Last Name : ";
	setContactInfo(this->last_name, false);
	std::cout << "Enter Nick Name : ";
	setContactInfo(this->nick_name, false);
	std::cout << "Enter Phone number : ";
	setContactInfo(this->phone_number, true);
	std::cout << "Enter Darkest secret : ";
	setContactInfo(this->darkest_secret, false);
}

void Contact::printContact()
{
	std::cout << "First Name : " << this->first_name << std::endl;
	std::cout << "Last Name : " << this->last_name << std::endl;
	std::cout << "Nick Name : " << this->nick_name << std::endl;
	std::cout << "Phone Number : " << this->phone_number << std::endl;
	std::cout << "Darkest Secret : " << this->darkest_secret << std::endl;
}

void Contact::displayBoard()
{
	if (this->index < 0)
		return ;
	std::cout << "|";
	std::cout << std::setw(10);
	std::cout << this->index;
	std::cout << "|";
	printField(this->first_name);
	std::cout << "|";
	printField(this->last_name);
	std::cout << "|";
	printField(this->nick_name);
	std::cout << "|";
	std::cout << std::endl;
}
