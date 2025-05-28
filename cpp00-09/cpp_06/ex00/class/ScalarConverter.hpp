/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsarana <vsarana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 14:27:06 by vsarana           #+#    #+#             */
/*   Updated: 2025/04/16 14:27:07 by vsarana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCALARCONVERTER_HPP
#define SCALARCONVERTER_HPP

enum literal_type
{
    PSEUDO,
    CHAR,
    INT,
    FLOAT,
    DOUBLE,
    INVALID
};

#include <iostream>
#include <string>
#include <limits>
#include <cstdlib>
#include <cctype>
#include <iomanip>
#include <sstream>


class ScalarConverter
{
    private:
        ScalarConverter();
        ScalarConverter(const ScalarConverter &other);
        ScalarConverter &operator=(const ScalarConverter &other);
        ~ScalarConverter();

    public:
        static void convert(const std::string &literal);  
};

#endif