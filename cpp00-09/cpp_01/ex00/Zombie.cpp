/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsarana <vsarana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 15:24:48 by vsarana           #+#    #+#             */
/*   Updated: 2024/11/25 15:24:49 by vsarana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp" 

Zombie::Zombie(std::string name)
{
    this->name = name;
    std::cout << this->name << " : " << "I'm alive" << std::endl;
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
