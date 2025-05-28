/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsarana <vsarana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 15:25:04 by vsarana           #+#    #+#             */
/*   Updated: 2024/12/02 16:01:30 by vsarana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"

int main()
{
    ClapTrap clap("ClapTrap");
    ClapTrap clap2(clap);
    ClapTrap clap3;

    clap3 = clap2;

    clap.attack("Enemy1");
    clap.takeDamage(3);
    clap.beRepaired(5);
    clap.attack("Enemy2");
    clap.takeDamage(8);
    clap.beRepaired(3);
    clap.attack("Enemy3");
    clap.takeDamage(10);

    return (0);
}