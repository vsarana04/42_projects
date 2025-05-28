/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsarana <vsarana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 12:38:45 by vsarana           #+#    #+#             */
/*   Updated: 2025/05/05 12:38:46 by vsarana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange()
{
    std::cout << "Default constructor called" << std::endl;
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &other)
{
    std::cout << "Copy constructor called" << std::endl;
    *this = other;
}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &other)
{
    std::cout << "Assignation operator called" << std::endl;
    if (this != &other)
        this->_dataBase = other._dataBase;
    
    return (*this);
}

BitcoinExchange::~BitcoinExchange()
{
    std::cout << "Destructor called" << std::endl;
}

bool BitcoinExchange::parseCSV(const std::string &line)
{
    std::istringstream ss(line);
    std::string date, valueStr;

    if (!std::getline(ss, date, ',') || !std::getline(ss, valueStr))
        return (false);

    if (!isValidDate(date))
    {
        std::cerr << "Warning: invalid date → " << date << std::endl;
        return (true);
    }

    float value = std::atof(valueStr.c_str());
    _dataBase[date] = value;

    return (true);
}

bool BitcoinExchange::parseInput(const std::string &line, std::string &date, std::string &valueStr) const
{
    std::istringstream ss(line);
    if (!std::getline(ss, date, '|') || !std::getline(ss, valueStr))
        return (false);

    size_t start = date.find_first_not_of(" \t");
    size_t end = date.find_last_not_of(" \t");
    if (start != std::string::npos && end != std::string::npos)
        date = date.substr(start, end - start + 1);
    else
        date = "";

    start = valueStr.find_first_not_of(" \t");
    end = valueStr.find_last_not_of(" \t");
    if (start != std::string::npos && end != std::string::npos)
        valueStr = valueStr.substr(start, end - start + 1);
    else
        valueStr = "";

    return (true);
}

void BitcoinExchange::loadDataBase(const std::string &fileName)
{
    std::ifstream file(fileName.c_str());

    if (!file.is_open())
    {
        std::cerr << "Error: couldn't open file " << fileName << std::endl;
        return;
    }

    std::string line;
    std::getline(file, line);

    while (std::getline(file, line))
    {
        if (!parseCSV(line))
            std::cerr << "Warning: bad format → " << line << std::endl;
    }
    file.close();
}

void BitcoinExchange::processInput(const std::string &inputFileName)
{
    std::ifstream inputFile(inputFileName.c_str());

    if (!inputFile.is_open())
    {
        std::cerr << "Error: couldn't open input file " << inputFileName << std::endl;
        return;
    }

    std::string line;

    while (std::getline(inputFile, line))
    {
        if (line == "date | value")
            continue;
        if (line.empty())
            continue;

        std::string date, valueStr;
        if (!parseInput(line, date, valueStr))
        {
            std::cerr << "Error: bad input => " << line << std::endl;
            continue;
        }
        isValid (date, valueStr);
    }
    inputFile.close();
}

float BitcoinExchange::getRateForDate(const std::string &date) const
{
    if (_dataBase.find(date) != _dataBase.end())
        return (_dataBase.at(date));

    std::map<std::string, float>::const_iterator it = _dataBase.lower_bound(date);

    if (it == _dataBase.begin())
    {
        std::cerr << "Error: no earlier date available for " << date << std::endl;
        return (0.0f);
    }

    --it;
    return (it->second);
}

void BitcoinExchange::isValid(const std::string &date, const std::string &valueStr) const
{
    if (!isValidDate(date))
    {
        std::cerr << "Error: invalid date => " << date << std::endl;
        return;
    }

    if (!isValidValue(valueStr))
    {
        std::cerr << "Error: invalid value => " << valueStr << std::endl;
        return;
    }

    float value = std::atof(valueStr.c_str());
    float rate = getRateForDate(date);
    std::cout << date << " => " << value << " = " << (value * rate) << std::endl;
}

bool BitcoinExchange::checkDays(int year, int month, int day) const
{
    if (month < 1 || month > 12 || day < 1)
        return (false);

    int maxDay;

    if (month == 2)
    {
        if (isLeapYear(year))
            maxDay = 29;
        else
            maxDay = 28;
    }
    else if (month == 4 || month == 6 || month == 9 || month == 11)
        maxDay = 30;
    else
        maxDay = 31;

    if (day > maxDay)
        return (false);

    return (true);
}

bool BitcoinExchange::isValidDate(const std::string &date) const
{
    if (date.length() != 10 || date[4] != '-' || date[7] != '-')
        return (false);

    for (size_t i = 0; i < date.length(); ++i)
    {
        if ((i == 4 || i == 7))
            continue;
        if (!isdigit(date[i]))
            return (false);
    }
    int year = atoi(date.substr(0, 4).c_str());
    int month = atoi(date.substr(5, 2).c_str());
    int day = atoi(date.substr(8, 2).c_str());

    return (checkDays(year, month, day));
}

bool BitcoinExchange::isLeapYear(int year) const
{
    return ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0);
}

bool BitcoinExchange::isValidValue(const std::string &valueStr) const
{
    bool dotFound = false;
    size_t i = 0;

    if (valueStr.empty())
        return (false);

    if (valueStr[i] == '-')
        return (false);

    for (; i < valueStr.length(); ++i)
    {
        if (valueStr[i] == '.')
        {
            if (dotFound)
                return (false);
            dotFound = true;
        }
        else if (!isdigit(valueStr[i]))
            return false;
    }

    float value = std::atof(valueStr.c_str());
    return (value >= 0.0f && value <= 1000.0f);
}
