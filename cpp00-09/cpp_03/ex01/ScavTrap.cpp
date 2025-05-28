/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScavTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsarana <vsarana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 16:59:26 by vsarana           #+#    #+#             */
/*   Updated: 2024/12/02 17:55:30 by vsarana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScavTrap.hpp"

ScavTrap::ScavTrap() : ClapTrap()
{
    std::cout << "ScavTrap Default constructor called" << std::endl;
    this->hitPoints = 100;
    this->energyPoints = 50;
    this->attackDamage = 20;
    std::cout << "Name: " << this->name << std::endl;
    std::cout << "Hit Points: " << this->hitPoints << std::endl;
    std::cout << "Energy Points: " << this->energyPoints << std::endl;
    std::cout << "Attack Damage: " << this->attackDamage << std::endl << std::endl;
    return ;
}

ScavTrap::ScavTrap(std::string name) : ClapTrap(name)
{
    std::cout << "ScavTrap parameter constructor called" << std::endl;
    this->hitPoints = 100;
    this->energyPoints = 50;
    this->attackDamage = 20;
    std::cout << "Name: " << this->name << std::endl;
    std::cout << "Hit Points: " << this->hitPoints << std::endl;
    std::cout << "Energy Points: " << this->energyPoints << std::endl;
    std::cout << "Attack Damage: " << this->attackDamage << std::endl << std::endl;
    return ;
}

ScavTrap::~ScavTrap()
{
    std::cout << "ScavTrap destructor called" << std::endl;
    return ;
}

ScavTrap::ScavTrap(const ScavTrap &other) : ClapTrap(other)
{
    std::cout << "ScavTrap Copy constructor called" << std::endl;
    return ;
}

ScavTrap &ScavTrap::operator=(const ScavTrap &other)
{
    if (this != &other)
        ClapTrap::operator=(other);
    std::cout << "Assignation operator called" << std::endl;
    return (*this);
}

void ScavTrap::attack(std::string const &target)
{
    if (this->hitPoints == 0 && this->energyPoints == 0)
    {
        std::cout<< "ScavTrap: " << this->name << " is already dead and cannot attack" << std::endl;
        return ;
    }
    else 
    {
        this->energyPoints -= 1;
        std::cout << "ScavTrap: " << this->name << " attacks " << target << ", causing " << this->attackDamage << " points of damage!" << std::endl;
        std::cout << "Remaining Energy Points: " << this->energyPoints << std::endl;
        return ;
    }
    return ;
}

void ScavTrap::guardGate()
{
    if (this->hitPoints == 0 && this->energyPoints == 0)
    {
        std::cout << "ScavTrap: " << this->name << " is already dead and cannot guard the gate" << std::endl;
        return ;
    }
    else
        std::cout << "ScavTrap: " << this->name << " has entered in Gate keeper mode" << std::endl;
    return ;
}