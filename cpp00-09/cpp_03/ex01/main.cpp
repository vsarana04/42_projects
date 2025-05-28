/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsarana <vsarana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 16:04:45 by vsarana           #+#    #+#             */
/*   Updated: 2024/12/02 17:51:15 by vsarana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"
#include "ScavTrap.hpp"


int main()
{
    ClapTrap clap("ClapTrap");
    
    clap.attack("Enemy1");
    clap.takeDamage(3);
    clap.beRepaired(5);
    std::cout << std::endl;
    
    std::cout << "-------------- " << std::endl;
    std::cout << "TEST ScavTrap" << std::endl;
    std::cout << "-------------- " << std::endl << std::endl;

    ScavTrap scav("ScavTrap");
    scav.attack("Enemy2");
    scav.takeDamage(8);
    scav.beRepaired(3);
    scav.guardGate(); 
    std::cout << std::endl;

/*     std::cout << "------------------ " << std::endl;
    std::cout << "TEST ScavTrap Copy" << std::endl;
    std::cout << "------------------ " << std::endl << std::endl;

    ScavTrap scav2(scav);
    scav2.attack("Enemy3");
    scav2.takeDamage(10);
    scav2.beRepaired(2);
    scav2.guardGate();
    std::cout << std::endl;

    std::cout << "------------------------- " << std::endl;
    std::cout << "TEST ScavTrap Assignation" << std::endl;
    std::cout << "------------------------- " << std::endl << std::endl;

    ScavTrap scav3;
    scav3 = scav2;
    scav3.attack("Enemy4");
    scav3.takeDamage(10);
    scav3.beRepaired(2);
    scav3.guardGate(); */


    return (0);
}