/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsarana <vsarana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 16:04:45 by vsarana           #+#    #+#             */
/*   Updated: 2024/12/02 18:40:21 by vsarana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"
#include "ScavTrap.hpp"
#include "FragTrap.hpp"

int main()
{
    FragTrap frag("FragTrap");
    
    frag.attack("Enemy1");
    frag.takeDamage(30);
    frag.beRepaired(20);
    frag.highFivesGuys();
    std::cout << std::endl;

/*     FragTrap frag2(frag);
    frag2.attack("Enemy2");
    frag2.takeDamage(50);
    frag2.beRepaired(100);
    frag2.highFivesGuys();
    std::cout << std::endl;

    FragTrap frag3;

    frag3 = frag2;
    frag3.attack("Enemy3");
    frag3.takeDamage(100);
    frag3.beRepaired(50);
    frag3.highFivesGuys(); */

    return (0);
}