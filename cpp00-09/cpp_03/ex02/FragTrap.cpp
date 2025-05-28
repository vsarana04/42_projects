/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FragTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsarana <vsarana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 18:40:33 by vsarana           #+#    #+#             */
/*   Updated: 2024/12/02 18:40:34 by vsarana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FragTrap.hpp"

FragTrap::FragTrap() : ClapTrap()
{
    std::cout << "FragTrap Default constructor called" << std::endl;
    this->hitPoints = 100;
    this->energyPoints = 100;
    this->attackDamage = 30;
    std::cout << "Name: " << this->name << std::endl;
    std::cout << "Hit Points: " << this->hitPoints << std::endl;
    std::cout << "Energy Points: " << this->energyPoints << std::endl;
    std::cout << "Attack Damage: " << this->attackDamage << std::endl << std::endl;
    return ;
}

FragTrap::FragTrap(std::string name) : ClapTrap(name)
{
    std::cout << "FragTrap parameter constructor called" << std::endl;
    this->hitPoints = 100;
    this->energyPoints = 100;
    this->attackDamage = 30;
    std::cout << "Name: " << this->name << std::endl;
    std::cout << "Hit Points: " << this->hitPoints << std::endl;
    std::cout << "Energy Points: " << this->energyPoints << std::endl;
    std::cout << "Attack Damage: " << this->attackDamage << std::endl << std::endl;
    return ;
}

FragTrap::~FragTrap()
{
    std::cout << "FragTrap destructor called" << std::endl;
    return ;
}

FragTrap::FragTrap(const FragTrap &copy) : ClapTrap(copy)
{
    std::cout << "FragTrap Copy constructor called" << std::endl;
    return ;
}

FragTrap &FragTrap::operator=(const FragTrap &other)
{
    if (this != &other)
        ClapTrap::operator=(other);
    std::cout << "Assignation operator called" << std::endl;
    return (*this);
}

void FragTrap::highFivesGuys(void)
{
    if (this->hitPoints == 0 && this->energyPoints == 0)
    {
        std::cout<< "FragTrap: " << this->name << " is already dead and cannot high five" << std::endl;
        return ;
    }
    else
    {
        this->energyPoints -= 5;
        std::cout << "FragTrap: " << this->name << " says high five guys!" << std::endl;
    }
    return ;
}