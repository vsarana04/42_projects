/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsarana <vsarana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 16:19:31 by vsarana           #+#    #+#             */
/*   Updated: 2024/11/30 16:19:32 by vsarana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"

Fixed::Fixed()
{
    this->fixed_p = 0;
    std::cout << "Default constructor called" << std::endl;
    return ;
}


Fixed::Fixed(const int value)
{
    std::cout << "Int constructor called" << std::endl;
    fixed_p = value << bits;
    return ;
}

Fixed::Fixed(const float value)
{
    std::cout << "Float constructor called" << std::endl;
    fixed_p = roundf(value * (1 << bits));
    return ;
}

Fixed::Fixed(const Fixed &other)
{
    std::cout << "Copy constructor called" << std::endl;
    *this = other;
    return ;
}

Fixed &Fixed::operator=(const Fixed &other)
{
    std::cout << "Copy assignment operator called" << std::endl;
    if (this != &other)
        this->fixed_p = other.fixed_p;
    return (*this);
}

Fixed::~Fixed()
{
    std::cout << "Destructor called" << std::endl;
    return ;
}

int Fixed::getRawBits() const
{
    return (this->fixed_p);
}

void Fixed::setRawBits(int const raw) 
{
    this->fixed_p = raw;
    return ;
}

float Fixed::toFloat() const
{
    float result = static_cast<float>(fixed_p);
    result /= (1 << bits);
    return (result);
}

int Fixed::toInt() const
{
    return (fixed_p >> bits);
}

std::ostream &operator<<(std::ostream &out, const Fixed &fixed)
{
    out << fixed.toFloat();
    return (out);
}
