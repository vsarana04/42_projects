#include "../includes/irc.hpp"
#include <iostream>
#include <cstdlib>
#include <sstream>
#include <climits>

std::string unescape(const std::string& str) {
	std::string res;
	for (size_t i = 0; i < str.length(); ++i) {
		switch (str[i]) {
			case '\r':
				res += "\\r";
				break;
			case '\n':
				res += "\\n";
				break;
			case '\\':
				res += "\\\\";
				break;
			case '\t':
				res += "\\t";
				break;
			default:
				res += str[i];
		}
	}
	return res;
}

std::vector<std::string> splitModeArgs(const std::string& str) {
	std::stringstream ss(str);
	std::string field;
	std::vector<std::string> res;
	while (1) {
		if (ss >> field)
			res.push_back(field);
		else if (ss.eof())
			break;
		ss.clear();
	}
	return res;
}

std::vector<std::string> splitOnDelim(const std::string& str, const char& delim) {
	std::stringstream ss(str);
	std::vector<std::string> res;
	while (ss.good()) {
		std::string substr;
		std::getline(ss, substr, delim);
		res.push_back(substr);
	}
	return res;
}

bool	isInteger(char * string)
{
	std::stringstream 	ss;
	long long 				nb;

	ss << string;
	ss >> nb;

	if (ss.fail() || !ss.eof())
		return (false);
	if (nb > INT_MAX || nb < INT_MIN)
		return (false);
	else
		return (true);
}

int	convertInt(char * string)
{
	if (isInteger(string) == true)
	{
		std::stringstream ss;
		int	integer; 

		ss << string;
		ss >> integer;

		return (integer);
	}
	return (-1);
}

void	printHeader(std::string password)
{
	std::cout << 
		" ------------------------------------------------------------------------ \n"
        "| ### ######   #####      #####  ####### ######  #     # ####### ######   | \n"
        "|  #  #     # #     #    #     # #       #     # #     # #       #     #  | \n"
        "|  #  #     # #          #       #       #     # #     # #       #     #  | \n"
        "|  #  ######  #           #####  #####   ######  #     # #####   ######   | \n"
        "|  #  #   #   #                # #       #   #    #   #  #       #   #    | \n"
        "|  #  #    #  #     #    #     # #       #    #    # #   #       #    #   | \n"
        "| ### #     #  #####      #####  ####### #     #    #    ####### #     #  | \n"
		" ------------------------------------------------------------------------ \n"
        << std::endl;

	std::cout << std::endl;
	std::cout << "\033[4;32m[SERVER] Password:\033[0m " << password << std::endl << std::endl;
}
