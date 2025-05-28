/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsarana <vsarana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 16:15:26 by vsarana           #+#    #+#             */
/*   Updated: 2024/11/26 15:39:10 by vsarana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

Zombie::Zombie(void)
{
    this->name = "Zombie";
    std::cout << this->name << " " << "created" << std::endl;
    return ;
}

Zombie::~Zombie(void)
{
    std::cout << this->name << " : " << "I'm dead" << std::endl;
    return ;
}

void	Zombie::announce(void) const
{
    std::cout << this->name << " : " << "BraiiiiiiinnnzzzZ..." << std::endl;
    return ;
}

void	Zombie::setName(std::string name)
{
    this->name = name;
    return ;
}
