/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsarana <vsarana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 12:45:58 by vsarana           #+#    #+#             */
/*   Updated: 2025/05/05 12:45:59 by vsarana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include "main.hpp"

void printBefore(const std::vector<int>& data)
{
    std::cout << "Before: ";
    for (size_t i = 0; i < data.size(); ++i)
        std::cout << data[i] << " ";
    std::cout << std::endl;
}

void printAfter(const std::vector<int>& data)
{
    std::cout << "After: ";
    for (size_t i = 0; i < data.size(); ++i)
        std::cout << data[i] << " ";
    std::cout << std::endl;
}

void printTiming(double vecTime, double listTime, size_t size)
{
    std::cout << "Time to process a range of " << size
              << " elements with std::vector: " << vecTime << " us" << std::endl;
    std::cout << "Time to process a range of " << size
              << " elements with std::list: " << listTime << " us" << std::endl;
}


int main(int argc, char **argv)
{
    try
    {
        PmergeMe sorter;
        sorter.run(argc, argv);
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        return (1);
    }
    return (0);
}
