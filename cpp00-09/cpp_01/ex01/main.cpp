/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsarana <vsarana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 16:15:16 by vsarana           #+#    #+#             */
/*   Updated: 2024/11/25 16:15:20 by vsarana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

int main(void)
{
    Zombie* horde;
    horde = zombieHorde(5, "Zombie");
    for (int i = 0; i < 5; i++)
        horde[i].announce();
    delete[] horde;
    return (0);
}
