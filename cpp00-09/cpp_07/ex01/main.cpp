/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsarana <vsarana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 14:53:26 by vsarana           #+#    #+#             */
/*   Updated: 2025/04/24 14:53:27 by vsarana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "iter.hpp"

template <typename T>
void printElement(T const &elem)
{
    std::cout << elem << std::endl;
}

int main()
{
    int intArr[5] = {1, 2, 3, 4, 5};
    std::string strArr[3] = {"x", "y", "z"};

    std::cout << "Print int array:" << std::endl;
    iter(intArr, 5, printElement);

    std::cout << "\nPrint string array:" << std::endl;
    iter(strArr, 3, printElement);

    return (0);
}