/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   megaphone.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsarana <vsarana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 14:05:56 by vsarana           #+#    #+#             */
/*   Updated: 2024/11/22 16:56:56 by vsarana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <cctype>

int main(int argc, char **argv)
{
    if (argc == 1)
        std::cout << "* LOUD AND UNBEARABLE FEEDBACK NOISE *" << std::endl;
    else
    {
        for (int i = 1; i < argc; i++)
        {
            for (int j = 0; argv[i][j] != '\0'; j++)
                std::cout << static_cast<char>(std::toupper(argv[i][j]));
            if (i < argc - 1)
                std::cout << ' ';
        }
        std::cout << std::endl;
    }
    return (0);
}
