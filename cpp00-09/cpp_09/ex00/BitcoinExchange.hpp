/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsarana <vsarana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 12:38:30 by vsarana           #+#    #+#             */
/*   Updated: 2025/05/05 12:42:39 by vsarana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <ctime>
#include <cstdlib>

class BitcoinExchange
{
    private:
        std::map<std::string, float> _dataBase;

        float getRateForDate(const std::string& date) const;
        bool parseInput(const std::string &line, std::string &date, std::string &valueStr) const;
        void isValid(const std::string& date, const std::string& valueStr) const;
        bool isValidDate(const std::string& date) const;
        bool isValidValue(const std::string& valueStr) const;
        bool isLeapYear(int year) const;
        bool checkDays(int year, int month, int day) const;

    public:
        BitcoinExchange();
        BitcoinExchange(const BitcoinExchange &other);
        BitcoinExchange &operator=(const BitcoinExchange &other);
        ~BitcoinExchange();
        
        bool parseCSV(const std::string &line);
        void loadDataBase(const std::string &fileName);
        void processInput(const std::string &inputFileName);

};

#endif