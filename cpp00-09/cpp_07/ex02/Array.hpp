/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Array.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsarana <vsarana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 14:53:36 by vsarana           #+#    #+#             */
/*   Updated: 2025/04/24 14:53:37 by vsarana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARRAY_HPP
#define ARRAY_HPP

#include <stdexcept>
#include <iostream>
#include <string>

template <typename T>
class Array
{
    private:
        T* _array;
        unsigned int _size;

    public:

        Array() : _array(NULL), _size(0) {}
        Array(unsigned int n) : _array(new T[n]), _size(n)
        {
            for (unsigned int i = 0; i < n; ++i)
                _array[i] = T();
        }
        Array(const Array& other) : _array(NULL), _size(0)
        {
            *this = other;
        }

        Array& operator=(const Array& other)
        {
            if (this != &other)
            {
                delete[] _array;
                _size = other._size;
                _array = new T[_size];
                for (unsigned int i = 0; i < _size; ++i)
                    _array[i] = other._array[i];
            }
            return (*this);
        }

        ~Array()
        {
            delete[] _array;
        }

        T& operator[](unsigned int i)
        {
            if (i >= _size)
                throw std::out_of_range("Index out of range");
            return (_array[i]);
        }

        unsigned int size() const
        {
            return (_size);
        }
};

#endif