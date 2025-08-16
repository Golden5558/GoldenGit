/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Replace.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberthal <nberthal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 08:44:16 by nberthal          #+#    #+#             */
/*   Updated: 2025/05/10 19:30:16 by nberthal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Replace.hpp"

Replacer::Replacer(char **argv) : _filename(argv[1]), _s1(argv[2]), _s2(argv[3])
{
	this->_outputFilename = argv[1];
	this->_outputFilename += ".replace";
	return ;
}

Replacer::~Replacer(void)
{
	return ;
}

std::string Replacer::replaceLine(std::string line)
{
	std::size_t	found = line.find(this->_s1);

	for ( ;found != std::string::npos; found = line.find(this->_s1)) {
		line.erase(found, this->_s1.length());
		line.insert(found, this->_s2);
	}
	return line;
}

void	Replacer::checkFile(const std::string & path, int access_flag)
{
	struct stat st;
    
	if (stat(path.c_str(), &st) != 0) {
		std::string err = std::string("Error: ") + strerror(errno);
		throw std::runtime_error(err);
	}
	if (S_ISDIR(st.st_mode)) {
		std::string err = std::string("Error: ") + path + " is a directory";
		throw std::runtime_error(err);
	}
	if (access(path.c_str(), access_flag) != 0) {
		std::string err = "Error: no ";
		if (access_flag == W_OK)
			err += "write";
		else
			err += "read";
		err += " permission on " + path;
		throw std::runtime_error(err);
	}
	if (access_flag != W_OK && st.st_size == 0) {
		std::string err = std::string("Error: ") + path + " is empty";
		throw std::runtime_error(err);
	}
}

void	Replacer::run(void)
{
	std::ifstream	ifs;
	std::ofstream	ofs;
	std::string		newline;
	
	ifs.open(this->_filename.c_str(), std::ifstream::in);
	ofs.open(this->_outputFilename.c_str(), std::ofstream::out);
	this->checkFile(this->_filename, R_OK);
	this->checkFile(this->_outputFilename, W_OK);
	for (std::string line; std::getline(ifs, line); )
	{
		line = this->replaceLine(line);
		ofs << line << std::endl;
	}
	if (ifs.fail() && !ifs.eof())
		throw std::runtime_error("Error : Failed to read from input file");
	if (ofs.fail())
		throw std::runtime_error("Error : Failed to write to output file");
}