/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phonebook.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberthal <nberthal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 14:53:31 by nberthal          #+#    #+#             */
/*   Updated: 2025/05/07 23:49:25 by nberthal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	PHONEBOOK_H
# define PHONEBOOK_H

# include <iostream>
# include <iomanip>
# include <sstream>
# include <cctype>
# include <string>
# include "templates.tpp"

# define RESET   "\033[0m"
# define GREEN   "\033[32m"
# define YELLOW  "\033[33m"
# define CYAN    "\033[36m"

void	setContactInfo(std::string & to_set, const bool is_number);
void	printField(std::string str);

class	Contact
{
	public:
		Contact();
		Contact(int i);
		~Contact();
		void printContact();
		void displayBoard();
	
	private:
		int			index;
		std::string first_name;
		std::string last_name;
		std::string nick_name;
		std::string phone_number;
		std::string darkest_secret;
};

class	PhoneBook
{
	public:
		PhoneBook();
		~PhoneBook();

		void 	addContact();
		void 	searchList();
		void	incrementAddedContact();
		int		getAddedContact();

	private:
		Contact _contacts [8];
		int		_added_contact;
};

#endif
