/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsarana <vsarana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 14:21:48 by vsarana           #+#    #+#             */
/*   Updated: 2024/11/26 14:34:50 by vsarana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Replace.hpp"

int main(int ac, char **av)
{
    if (ac != 4)
    {
        std::cerr << "Error\nInvalid number of arguments" << std::endl;
        return (1);
    }

    Replace replace(av[1], av[2], av[3]);
    replace.replace();
    replace.display();
    return (0);
}