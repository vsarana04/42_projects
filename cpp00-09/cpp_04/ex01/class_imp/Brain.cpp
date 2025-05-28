/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Brain.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsarana <vsarana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 17:56:58 by vsarana           #+#    #+#             */
/*   Updated: 2024/12/03 17:56:59 by vsarana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../class/Brain.hpp"

Brain::Brain()
{
    std::cout << "Brain default constructor called" << std::endl;
    for (int i = 0; i < 100; i++)
        this->ideas[i] = "";
    return ;
}
Brain::~Brain()
{
    std::cout << "Brain destructor called" << std::endl;
    return ;
}

Brain::Brain(const Brain &other)
{
    std::cout << "Brain copy constructor called" << std::endl;
    *this = other;
    return ;
}

Brain &Brain::operator=(const Brain &other)
{
    std::cout << "Brain assignation operator called" << std::endl;
    if (this != &other)
    {
        for (int i = 0; i < 100; i++)
            this->ideas[i] = other.ideas[i];
    }
    return (*this);
}

void Brain::setIdea(std::string idea, int i)
{
    if (i < 0 || i >= 100)
    {
        std::cout << "Invalid index" << std::endl;
        return ;
    }
    this->ideas[i] = idea;
    return ;
}

std::string Brain::getIdea(int i) const
{
    if (i < 0 || i >= 100)
    {
        std::cout << "Invalid index" << std::endl;
        return ("");
    }
    return (this->ideas[i]);
}