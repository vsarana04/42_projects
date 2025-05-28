/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Span.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsarana <vsarana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 11:39:17 by vsarana           #+#    #+#             */
/*   Updated: 2025/04/30 11:39:18 by vsarana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../class/Span.hpp"

Span::Span(unsigned int n) : length(n) {}

Span::Span(const Span &other) : vec(other.vec), length(other.length) {}

Span &Span::operator=(const Span &other)
{
    if (this != &other)
    {
        length = other.length;
        vec = other.vec;
    }
    return (*this);
}

Span::~Span() {}

void Span::addNumber(int number)
{
    if (vec.size() >= length)
        throw SpanFullException();
    vec.push_back(number);
}

int Span::shortestSpan()
{
    if (vec.size() < 2)
        throw NoSpanException();
    std::vector<int> sortedVec = vec;
    std::sort(sortedVec.begin(), sortedVec.end());
    unsigned int shortestSpan = sortedVec[1] - sortedVec[0];
    for (size_t i = 1; i < sortedVec.size(); ++i)
    {
        unsigned int span = sortedVec[i] - sortedVec[i - 1];
        if (span < shortestSpan)
            shortestSpan = span;
    }
    return (shortestSpan);
}

int Span::longestSpan()
{
    if (vec.size() < 2)
        throw NoSpanException();
    int min = *std::min_element(vec.begin(), vec.end());
    int max = *std::max_element(vec.begin(), vec.end());
    return (max - min);
}

const char* Span::SpanFullException::what() const throw()
{
    return ("Span is full");
}
const char* Span::NoSpanException::what() const throw()
{
    return ("No span can be found");
}
