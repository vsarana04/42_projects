/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanB.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsarana <vsarana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 15:40:33 by vsarana           #+#    #+#             */
/*   Updated: 2024/11/26 15:40:34 by vsarana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HumanB.hpp"

HumanB::HumanB(std::string name)
{
    this->name = name;
    this->weapon = NULL;
    std::cout << "HumanB created" << std::endl;
    return ;
}

HumanB::~HumanB()
{
    std::cout << "HumanB destroyed" << std::endl;
    return ;
}   

void HumanB::setWeapon(Weapon &weapon)
{
    this->weapon = &weapon;
    return ;
}

void HumanB::attack()
{
    if (this->weapon == NULL)
    {
        std::cout << this->name << " has no weapon" << std::endl;
        return ;
    }
    else
        std::cout << this->name << " attacks with their " << this->weapon->getType() << std::endl;
    return ;
}
