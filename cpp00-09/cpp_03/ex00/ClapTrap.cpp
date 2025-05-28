/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClapTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsarana <vsarana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 15:25:23 by vsarana           #+#    #+#             */
/*   Updated: 2024/12/02 15:59:50 by vsarana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"

ClapTrap::ClapTrap()
{
    std::cout << "Default constructor called" << std::endl;
    this->name = "";
    this->hitPoints = 10;
    this->energyPoints = 10;
    this->attackDamage = 0;
    std::cout << "Name: " << this->name << std::endl;
    std::cout << "Hit Points: " << this->hitPoints << std::endl;
    std::cout << "Energy Points: " << this->energyPoints << std::endl;
    std::cout << "Attack Damage: " << this->attackDamage << std::endl << std::endl;
    return ;
}


ClapTrap::ClapTrap(std::string name)
{
    std::cout << "ClapTrap parameter constructor called" << std::endl;
    this->name = name;
    this->hitPoints = 10;
    this->energyPoints = 10;
    this->attackDamage = 0;
    std::cout << "Name: " << this->name << std::endl;
    std::cout << "Hit Points: " << this->hitPoints << std::endl;
    std::cout << "Energy Points: " << this->energyPoints << std::endl;
    std::cout << "Attack Damage: " << this->attackDamage << std::endl << std::endl;
    return ;
}
ClapTrap::ClapTrap(const ClapTrap &other)
{
    std::cout << "Copy constructor called" << std::endl;
    this->name = other.name;
    this->hitPoints = other.hitPoints;
    this->energyPoints = other.energyPoints;
    this->attackDamage = other.attackDamage;
    std::cout << "Copied Name: " << this->name << std::endl;
    std::cout << "Copied Hit Points: " << this->hitPoints << std::endl;
    std::cout << "Copied Energy Points: " << this->energyPoints << std::endl;
    std::cout << "Copied Attack Damage: " << this->attackDamage << std::endl << std::endl;

    return ;
}

ClapTrap &ClapTrap::operator=(const ClapTrap &other)
{
    std::cout << "Assignation operator called" << std::endl;
    this->name = other.name;
    this->hitPoints = other.hitPoints;
    this->energyPoints = other.energyPoints;
    this->attackDamage = other.attackDamage;
    std::cout << "Copied Name: " << this->name << std::endl;
    std::cout << "Copied Hit Points: " << this->hitPoints << std::endl;
    std::cout << "Copied Energy Points: " << this->energyPoints << std::endl;
    std::cout << "Copied Attack Damage: " << this->attackDamage << std::endl << std::endl;
    return (*this);
}


ClapTrap::~ClapTrap()
{
    std::cout << "ClapTrap destructor called" << std::endl;
    return ;
}

void ClapTrap::attack(std::string const &target)
{
    if (this->hitPoints == 0 && this->energyPoints == 0)
    {
        std::cout << "Attack: " << this->name << " is already dead and cannot attack" << std::endl;
        return ;
    }
    else 
    {
        this->energyPoints -= 1;
        std::cout << "Attack: " << this->name << " attacks " << target << ", causing " << this->attackDamage << " points of damage!" << std::endl;
        std::cout << "Remaining Energy Points: " << this->energyPoints << std::endl;
        return ;
    }
    return ;
}

void ClapTrap::takeDamage(unsigned int amount)
{
    if (this->hitPoints == 0)
    {
        std::cout << "Damage: " << this->name << " is already dead" << std::endl;
        return ;
    }
    else if (amount >= this->hitPoints)
    {
        this->hitPoints = 0;
        std::cout << "Damage: " << this->name << " takes " << amount << " points of damage and dies" << std::endl;
        return ;
    }
    else
    {
        this->hitPoints -= amount;
        std::cout << "Damage: " << this->name << " takes " << amount << " points of damage!" << std::endl;
        std::cout << "Remaining Hit Points: " << this->hitPoints << std::endl;
        return ;
    }
    return ;
}

void ClapTrap::beRepaired(unsigned int amount)
{
    if (this->hitPoints == 0 && this->energyPoints == 0)
    {
        std::cout << "Repair: " << this->name << " is already dead and cannot be repaired. No hit points or energy!" << std::endl;
        return ;
    }

    this->energyPoints -= 1;

    if (amount + this->hitPoints >= 10)
    {

        this->hitPoints = 10;
        std::cout << "Repair: " << this->name << " is fully repaired" << std::endl;
        return ;
    }
    else
    {
        this->hitPoints += amount;
        std::cout << "Repair: " << this->name << " is repaired by " << amount << " points!" << std::endl;
        std::cout << "Remaining Hit Points: " << this->hitPoints << std::endl;
        return ;
    }

    std::cout << "Remaining Energy Points: " << this->energyPoints << std::endl;

    return ;
}