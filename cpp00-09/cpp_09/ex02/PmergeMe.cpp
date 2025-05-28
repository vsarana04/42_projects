/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsarana <vsarana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 12:46:27 by vsarana           #+#    #+#             */
/*   Updated: 2025/05/05 12:46:28 by vsarana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include "main.hpp"

PmergeMe::PmergeMe() {}

PmergeMe::PmergeMe(const PmergeMe &other) : _vector(other._vector), _list(other._list) {}

PmergeMe &PmergeMe::operator=(const PmergeMe &other)
{
    if (this != &other)
    {
        _vector = other._vector;
        _list = other._list;
    }
    return (*this);
}

PmergeMe::~PmergeMe() {}

bool PmergeMe::isPositive(const std::string &str) const
{
    if (str.empty())
        return (false);

    for (size_t i = 0; i < str.length(); ++i)
    {
        if (!std::isdigit(str[i]))
            return (false);
    }

    char *end = NULL;
    long value = std::strtol(str.c_str(), &end, 10);
    if (*end != '\0' || value <= 0 || value > 2147483647)
        return (false);
    return (true);
}

void PmergeMe::checkDuplicates(const std::vector<int> &data) const
{
    std::vector<int> tmp = data;
    std::sort(tmp.begin(), tmp.end());
    for (size_t i = 1; i < tmp.size(); ++i)
    {
        if (tmp[i] == tmp[i - 1])
            throw std::runtime_error("Error: duplicate values are not allowed");
    }
}

void PmergeMe::run(int ac, char **av)
{
    this->parseInput(ac, av);

    printBefore(_vector);

    double startVec = getTimeInMicroseconds();
    std::vector<int> sortedVector = mergeInsertSortVector(_vector);
    double endVec = getTimeInMicroseconds();
    double startList = getTimeInMicroseconds();
    std::list<int> sortedList = mergeInsertSortList(_list);
    double endList = getTimeInMicroseconds();
    printAfter(sortedVector);
    printTiming(endVec - startVec, endList - startList, _vector.size());
}


void PmergeMe::parseInput(int ac, char **av)
{
    if (ac < 2)
        throw std::invalid_argument("Error: No input provided");

    for (int i = 1; i < ac; ++i)
    {
        std::string arg = av[i];

        if (!isPositive(arg))
            throw std::invalid_argument("Error: Invalid input '" + arg + "'");

        int num = std::atoi(arg.c_str());
        _vector.push_back(num);
        _list.push_back(num);
    }
    checkDuplicates(_vector);
}

double PmergeMe::getTimeInMicroseconds() const
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000000.0 + tv.tv_usec);
}

std::vector<int> PmergeMe::mergeInsertSortVector(const std::vector<int> &input)
{
    size_t size = input.size();
    if (size <= 1)
        return (input);

    std::vector<int> bigs;
    std::vector<int> smalls;

    for (size_t i = 0; i + 1 < size; i += 2)
    {
        int first = input[i];
        int second = input[i + 1];

        if (first < second)
        {
            smalls.push_back(first);
            bigs.push_back(second);
        }
        else
        {
            smalls.push_back(second);
            bigs.push_back(first);
        }
    }

    if (size % 2 != 0)
        bigs.push_back(input[size - 1]);
    std::vector<int> sorted = mergeInsertSortVector(bigs);
    insertSortedVector(sorted, smalls);
    return (sorted);
}


void PmergeMe::insertSortedVector(std::vector<int> &main, const std::vector<int> &insert)
{
    for (size_t i = 0; i < insert.size(); ++i)
    {
        std::vector<int>::iterator pos = std::lower_bound(main.begin(), main.end(), insert[i]);
        main.insert(pos, insert[i]);
    }
}

std::list<int> PmergeMe::mergeInsertSortList(const std::list<int> &input)
{
    if (input.size() <= 1)
        return (input);

    std::list<int> bigs;
    std::list<int> smalls;

    std::list<int>::const_iterator it = input.begin();
    while (it != input.end())
    {
        int first = *it++;
        if (it != input.end())
        {
            int second = *it++;
            if (first < second)
            {
                smalls.push_back(first);
                bigs.push_back(second);
            }
            else
            {
                smalls.push_back(second);
                bigs.push_back(first);
            }
        }
        else
            bigs.push_back(first);
    }

    std::list<int> sorted = mergeInsertSortList(bigs);
    insertSortedList(sorted, smalls);
    return (sorted);
}

void PmergeMe::insertSortedList(std::list<int> &mainList, const std::list<int> &insert)
{
    for (std::list<int>::const_iterator it = insert.begin(); it != insert.end(); ++it)
    {
        std::list<int>::iterator pos = mainList.begin();
        while (pos != mainList.end() && *pos < *it)
            ++pos;
        mainList.insert(pos, *it);
    }
}