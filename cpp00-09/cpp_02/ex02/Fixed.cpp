/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsarana <vsarana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 16:55:55 by vsarana           #+#    #+#             */
/*   Updated: 2024/11/30 16:55:56 by vsarana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"

Fixed::Fixed()
{
    fixed_p = 0;
    std::cout << "Default constructor called" << std::endl;
    return ;
}

Fixed::Fixed(const int value)
{
    fixed_p = value << bits;
    std::cout << "Int constructor called" << std::endl;
    return ;
}

Fixed::Fixed(const float value)
{
    fixed_p = roundf(value * (1 << bits));
    std::cout << "Float constructor called" << std::endl;
    return ;
}

Fixed::Fixed(const Fixed &other)
{
    *this = other;
    std::cout << "Copy constructor called" << std::endl;
    return ;
}

Fixed &Fixed::operator=(const Fixed &other)
{
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
    return (fixed_p);
}


void Fixed::setRawBits(int const raw)
{
    fixed_p = raw;
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

bool Fixed::operator>(const Fixed &other) const
{
    return (fixed_p > other.fixed_p);
}

bool Fixed::operator<(const Fixed &other) const 
{
    return (fixed_p < other.fixed_p);
}

bool Fixed::operator>=(const Fixed &other) const 
{
    return (fixed_p >= other.fixed_p);
}

bool Fixed::operator<=(const Fixed &other) const
{
    return (fixed_p <= other.fixed_p);
}

bool Fixed::operator==(const Fixed &other) const
{
    return (fixed_p == other.fixed_p);
}

bool Fixed::operator!=(const Fixed &other) const
{
    return (fixed_p != other.fixed_p);
}

Fixed Fixed::operator+(const Fixed &other) const
{
    float result = this->toFloat() + other.toFloat();
    return (Fixed(result));
}

Fixed Fixed::operator-(const Fixed &other) const
{
    float result = this->toFloat() - other.toFloat();
    return (Fixed(result));
}

Fixed Fixed::operator*(const Fixed &other) const
{
    float result = this->toFloat() * other.toFloat();
    return (Fixed(result));
}

Fixed Fixed::operator/(const Fixed &other) const
{
    float result = this->toFloat() / other.toFloat();
    return (Fixed(result));
}

Fixed &Fixed::operator++()
{
    fixed_p++;
    return (*this);
}

Fixed Fixed::operator++(int)
{
    Fixed tmp = *this;
    fixed_p++;
    return (tmp);
}

Fixed &Fixed::operator--()
{
    fixed_p--;
    return (*this);
}

Fixed Fixed::operator--(int)
{
    Fixed tmp = *this;
    fixed_p--;
    return (tmp);
}

Fixed &Fixed::min(Fixed &a, Fixed &b)
{
    if (a < b)
        return (a);
    else
        return (b);
}

const Fixed &Fixed::min(const Fixed &a, const Fixed &b)
{
    if (a < b)
        return (a);
    else
        return (b);
}

Fixed &Fixed::max(Fixed &a, Fixed &b)
{
    if (a > b)
        return (a);
    else
        return (b);
}

const Fixed &Fixed::max(const Fixed &a, const Fixed &b)
{
    if (a > b)
        return (a);
    else
        return (b);
}

std::ostream &operator<<(std::ostream &out, const Fixed &fixed)
{
    out << fixed.toFloat();
    return (out);
}