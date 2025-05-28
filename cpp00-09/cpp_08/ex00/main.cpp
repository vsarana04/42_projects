/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsarana <vsarana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 11:38:47 by vsarana           #+#    #+#             */
/*   Updated: 2025/04/30 11:38:48 by vsarana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "easyfind.hpp"

void testvector()
{
    std::vector<int> vector;
    vector.push_back(10);
    vector.push_back(20);
    vector.push_back(30);

    std::cout << "Testing vectortor: ";
    for (std::vector<int>::iterator it = vector.begin(); it != vector.end(); ++it)
        std::cout << *it << " ";
    std::cout << std::endl;

    try
    {
        std::vector<int>::iterator found = easyfind(vector, 20);
        std::cout << "Found value in vector: " << *found << std::endl;
    }
    catch (std::exception& e)
    {
        std::cout << "Exception: " << e.what() << std::endl;
    }


}

int main()
{
    testvector();
    return (0);
}