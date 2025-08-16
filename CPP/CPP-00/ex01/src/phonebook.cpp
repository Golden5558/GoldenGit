/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phonebook.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberthal <nberthal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 14:53:29 by nberthal          #+#    #+#             */
/*   Updated: 2025/05/08 18:44:17 by nberthal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "phonebook.hpp"

PhoneBook::PhoneBook() : _added_contact( 0 )
{
	return ;
}

PhoneBook::~PhoneBook()
{
	return ;
}

int		PhoneBook::getAddedContact()
{
	return this->_added_contact;
}

void	PhoneBook::incrementAddedContact()
{
	this->_added_contact++;
}

void	PhoneBook::addContact()
{
	int i = getAddedContact();

	this->_contacts[i % 8] = Contact((i % 8) + 1);
	incrementAddedContact();
}

void PhoneBook::searchList()
{
	std::string	user_choice;
	int			index_contact = 0;
	
	std::cout << "/-------------------------------------------\\" << std::endl;
	std::cout << "|  Index   |First name|Last name |Nick name |" << std::endl;
	std::cout << "|----------|----------|----------|----------|" << std::endl;
	for (int i = 0; i < 8; i++)
	{
		this->_contacts[i].displayBoard();
	}
	std::cout << "\\-------------------------------------------/" << std::endl;
	std::cout << "Enter an Index : ";
	if (!std::getline(std::cin, user_choice)) {
		if (std::cin.eof()) {
			std::cout << std::endl;
			throw std::runtime_error("[EOF detected - exiting]");
		}
	}
	if (!convert(user_choice, index_contact))
        throw std::runtime_error("Invalid number!\n");
	int added_contact = getAddedContact();
	if (added_contact > 8)
		added_contact = 8;
	if (!(index_contact >= 1 && index_contact <= added_contact))
		throw std::out_of_range("Invalid Index");
	this->_contacts[index_contact - 1].printContact();
}
