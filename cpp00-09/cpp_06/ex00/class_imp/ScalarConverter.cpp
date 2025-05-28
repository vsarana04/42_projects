/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsarana <vsarana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 14:27:11 by vsarana           #+#    #+#             */
/*   Updated: 2025/04/16 14:27:12 by vsarana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScalarConverter.hpp"

ScalarConverter::ScalarConverter() {}

ScalarConverter::ScalarConverter(const ScalarConverter &other) { (void)other; } 

ScalarConverter &ScalarConverter::operator=(const ScalarConverter &other)
{
    (void)other;
    return (*this);
}

ScalarConverter::~ScalarConverter() {}

static literal_type detectType(const std::string& str)
{
    if (str == "nan" || str == "+inf" || str == "-inf" ||
        str == "nanf" || str == "+inff" || str == "-inff")
        return (PSEUDO);

    if (str.length() == 1 && !std::isdigit(str[0]))
        return (CHAR);

    if (str.find('.') != std::string::npos)
    {
        if (str[str.length() - 1] == 'f')
            return (FLOAT);
        else
            return (DOUBLE);
    }
    return (INT);
}

template<typename T>
std::string formatValue(T value, const std::string& suffix)
{
    std::ostringstream oss;
    oss << value;
    std::string result = oss.str();

    if (result.find('.') == std::string::npos)
        result += ".0";

    result += suffix;
    return (result);
}

static void convertFromChar(char c)
{
    std::cout << "char: '" << c << "'" << std::endl;
    std::cout << "int: " << static_cast<int>(c) << std::endl;
    std::cout << "float: " << formatValue(static_cast<float>(c), "f") << std::endl;
    std::cout << "double: " << formatValue(static_cast<double>(c), "") << std::endl;
}

static void convertFromInt(int n)
{
    if (n >= 32 && n <= 126)
        std::cout << "char: '" << static_cast<char>(n) << "'" << std::endl;
    else if (n >= 0 && n <= 255)
        std::cout << "char: Non displayable" << std::endl;
    else
        std::cout << "char: impossible" << std::endl;

    std::cout << "int: " << n << std::endl;
    std::cout << "float: " << formatValue(static_cast<float>(n), "f") << std::endl;
    std::cout << "double: " << formatValue(static_cast<double>(n), "") << std::endl;
}

static void convertFromFloat(float f)
{
    if (f >= 32 && f <= 126)
        std::cout << "char: '" << static_cast<char>(f) << "'" << std::endl;
    else if (f >= 0 && f <= 255)
        std::cout << "char: Non displayable" << std::endl;
    else
        std::cout << "char: impossible" << std::endl;

    if (f >= static_cast<float>(std::numeric_limits<int>::min()) &&
        f <= static_cast<float>(std::numeric_limits<int>::max()))
        std::cout << "int: " << static_cast<int>(f) << std::endl;
    else
        std::cout << "int: impossible" << std::endl;

    std::cout << "float: " << formatValue(f, "f") << std::endl;
    std::cout << "double: " << formatValue(static_cast<double>(f), "") << std::endl;
}

static void convertFromDouble(double d)
{
    if (d >= 32 && d <= 126)
        std::cout << "char: '" << static_cast<char>(d) << "'" << std::endl;
    else if (d >= 0 && d <= 255)
        std::cout << "char: Non displayable" << std::endl;
    else
        std::cout << "char: impossible" << std::endl;

    if (d >= static_cast<double>(std::numeric_limits<int>::min()) &&
        d <= static_cast<double>(std::numeric_limits<int>::max()))
        std::cout << "int: " << static_cast<int>(d) << std::endl;
    else
        std::cout << "int: impossible" << std::endl;

    if (d >= -std::numeric_limits<float>::max() &&
        d <= std::numeric_limits<float>::max())
        std::cout << "float: " << formatValue(static_cast<float>(d), "f") << std::endl;
    else
        std::cout << "float: impossible" << std::endl;

    std::cout << "double: " << formatValue(d, "") << std::endl;
}

static void convertFromPseudo(const std::string& str)
{
    std::string f;
    std::string d;

    if (str[str.length() - 1] == 'f')
    {
        f = str;
        d = str.substr(0, str.length() - 1);
    }
    else
    {
        f = str + "f";
        d = str;
    }

    std::cout << "char: impossible" << std::endl;
    std::cout << "int: impossible" << std::endl;
    std::cout << "float: " << f << std::endl;
    std::cout << "double: " << d << std::endl;
}

static void printImpossible()
{
    std::cout << "char: impossible" << std::endl;
    std::cout << "int: impossible" << std::endl;
    std::cout << "float: impossible" << std::endl;
    std::cout << "double: impossible" << std::endl;
}

void ScalarConverter::convert(const std::string& literal)
{
    literal_type type = detectType(literal);

    switch (type)
    {
        case CHAR:
            convertFromChar(literal[0]);
            break;
        case INT:
            convertFromInt(std::atoi(literal.c_str()));
            break;
        case FLOAT:
            convertFromFloat(static_cast<float>(std::atof(literal.c_str())));
            break;
        case DOUBLE:
            convertFromDouble(std::atof(literal.c_str()));
            break;
        case PSEUDO:
            convertFromPseudo(literal);
            break;
        default:
            printImpossible();
    }
}
