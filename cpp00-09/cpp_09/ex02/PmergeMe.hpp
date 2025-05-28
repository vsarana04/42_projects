/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsarana <vsarana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 12:46:30 by vsarana           #+#    #+#             */
/*   Updated: 2025/05/05 12:46:31 by vsarana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <vector>
#include <list>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <string>
#include <sstream>
#include <stdexcept>
#include <sys/time.h>

class PmergeMe
{
    private:
        std::vector<int> _vector;
        std::list<int>   _list;

        bool isPositive(const std::string &str) const;
        void checkDuplicates(const std::vector<int> &data) const;
        void insertSortedVector(std::vector<int> &main, const std::vector<int> &toInsert);
        void insertSortedList(std::list<int> &main, const std::list<int> &toInsert);
        double getTimeInMicroseconds() const;

    public:
        PmergeMe();
        PmergeMe(const PmergeMe &other);
        PmergeMe &operator=(const PmergeMe &other);
        ~PmergeMe();

        void run(int argc, char **argv);
        void parseInput(int argc, char **argv);
        std::vector<int> mergeInsertSortVector(const std::vector<int> &input);
        std::list<int>   mergeInsertSortList(const std::list<int> &input);
    };

#endif