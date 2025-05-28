/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cat.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsarana <vsarana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 15:31:18 by vsarana           #+#    #+#             */
/*   Updated: 2024/12/03 17:09:23 by vsarana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../class/Cat.hpp"
#include "../class/Brain.hpp"

Cat::Cat() : Animal()
{
    this->type = "Cat";
    this->brain = new Brain();
    std::cout << "Cat constructor called" << std::endl;
    return ;
}

Cat::~Cat()
{
    delete this->brain;
    std::cout << "Cat destructor called" << std::endl;
    return ;
}

Cat::Cat(const Cat &other) : Animal(other)
{
    this->brain = new Brain(*other.brain);
    std::cout << "Cat copy constructor called" << std::endl;
    return ;
}

Cat &Cat::operator=(const Cat &other)
{
    if (this == &other)
        return (*this);
    delete this->brain;
    this->brain = new Brain(*other.brain);
    this->type = other.type;
    std::cout << "Cat assignation operator called" << std::endl;
    return (*this);
}

void Cat::makeSound() const
{
    std::cout << "Meow" << std::endl;
    return ;
}

void Cat::setBrain(Brain* brain)
{
    this->brain = brain;
    return ;
}

Brain* Cat::getBrain() const
{
    return (this->brain);
}


