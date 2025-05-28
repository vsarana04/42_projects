/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsarana <vsarana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 11:39:22 by vsarana           #+#    #+#             */
/*   Updated: 2025/04/30 11:39:23 by vsarana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "class/Span.hpp"

int test1()
{
    try
    {

        Span sp(5);
        sp.addNumber(6);
        sp.addNumber(3);
        sp.addNumber(17);
        sp.addNumber(9);
        sp.addNumber(11);

        try
        {
            sp.addNumber(42);
        }
        catch (std::exception& e)
        {
            std::cout << "Expected exception: " << e.what() << std::endl;
        }
        std::cout << "Shortest span: " << sp.shortestSpan() << std::endl;
        std::cout << "Longest span: " << sp.longestSpan() << std::endl;



        Span bigSpan(10000);
        std::vector<int> nums;
        for (int i = 0; i < 10000; ++i)
            nums.push_back(i * 2);

        bigSpan.addRange(nums.begin(), nums.end());

        std::cout << "Big span test" << std::endl;
        std::cout << "Shortest span: " << bigSpan.shortestSpan() << std::endl;
        std::cout << "Longest span: " << bigSpan.longestSpan() << std::endl;
    }
    catch (std::exception& e)
    {
        std::cerr << "Unexpected error: " << e.what() << std::endl;
    }

    return (0);
}

int main()
{
    /* Span sp = Span(5);
    sp.addNumber(6);
    sp.addNumber(3);
    sp.addNumber(17);
    sp.addNumber(9);
    sp.addNumber(11);
    std::cout << sp.shortestSpan() << std::endl;
    std::cout << sp.longestSpan() << std::endl;
 */
    test1();

    return (0);
}