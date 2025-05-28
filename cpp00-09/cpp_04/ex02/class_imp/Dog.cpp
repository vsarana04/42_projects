/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsarana <vsarana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 15:31:23 by vsarana           #+#    #+#             */
/*   Updated: 2024/12/03 17:09:31 by vsarana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../class/Dog.hpp"
#include "../class/Brain.hpp"

Dog::Dog() : Animal()
{
    this->type = "Dog";
    this->brain = new Brain();
    std::cout << "Dog constructor called" << std::endl;
    return ;
}

Dog::~Dog()
{
    delete this->brain;
    std::cout << "Dog destructor called" << std::endl;
    return ;
}

Dog::Dog(const Dog &other) : Animal(other)
{
    this->brain = new Brain(*other.brain);
    std::cout << "Dog copy constructor called" << std::endl;
    
    return ;
}

Dog &Dog::operator=(const Dog &other)
{
    if (this == &other)
        return (*this);
    delete this->brain;
    this->brain = new Brain(*other.brain);
    this->type = other.type;
    std::cout << "Dog assignation operator called" << std::endl;
    return (*this);
}

void Dog::makeSound() const
{
    std::cout << "Bark" << std::endl;
    return ;
}

void Dog::setBrain(Brain* brain)
{
    this->brain = brain;
    return ;
}

Brain* Dog::getBrain() const
{
    return (this->brain);
}
