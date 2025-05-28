/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Span.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsarana <vsarana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 11:39:12 by vsarana           #+#    #+#             */
/*   Updated: 2025/04/30 11:39:13 by vsarana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPAN_HPP
#define SPAN_HPP

#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <stdexcept>

class Span
{
    private:
        std::vector<int> vec;
        unsigned int length;
    
    public:

        Span(unsigned int n);
        Span(const Span &other);
        Span &operator=(const Span &other);
        ~Span();

        void addNumber(int number);
        int shortestSpan();
        int longestSpan();

        template <typename T>
        void addRange(T begin, T end)
        {
            if (std::distance(begin, end) > static_cast<int>(length))
                throw SpanFullException();
            vec.insert(vec.end(), begin, end);
        }
        
        class SpanFullException : public std::exception
        {
            public:
                const char* what() const throw();
        };
        
        class NoSpanException : public std::exception
        {
            public:
                const char* what() const throw();
        };
};

#endif