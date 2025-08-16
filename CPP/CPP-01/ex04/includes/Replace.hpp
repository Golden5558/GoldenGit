/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Replace.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberthal <nberthal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 08:25:17 by nberthal          #+#    #+#             */
/*   Updated: 2025/05/10 17:08:20 by nberthal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REPLACE_H
# define REPLACE_H

#include <sys/stat.h>
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <cerrno>
#include <unistd.h>
#include <cstring>

# define RESET   "\033[0m"
# define YELLOW  "\033[33m"

class Replacer
{
	public:
		Replacer(char **argv);
		~Replacer();

		void	run(void);
	
	private:
		std::string	_filename;
		std::string	_outputFilename;
		std::string	_s1;
		std::string	_s2;

		std::string	replaceLine(std::string line);
		void		checkFile(const std::string & path, int access_flag);
};

#endif