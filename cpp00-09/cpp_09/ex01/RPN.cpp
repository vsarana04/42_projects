/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsarana <vsarana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 12:44:20 by vsarana           #+#    #+#             */
/*   Updated: 2025/05/05 12:44:21 by vsarana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

RPN::RPN()
{
    std::cout << "Default constructor called" << std::endl;
}

RPN::RPN(const RPN &other)
{
    std::cout << "Copy constructor called" << std::endl;
    *this = other;
}

RPN &RPN::operator=(const RPN &other)
{
    if (this != &other)
        this->stack = other.stack;
    return (*this);
}

RPN::~RPN()
{
    std::cout << "Destructor called" << std::endl;
}

bool RPN::isOperator(char c) const
{
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

bool RPN::isDigit(char c) const
{
    return (c >= '0' && c <= '9');
}

bool RPN::executeOperation(char op)
{
    if (stack.size() < 2)
    {
        std::cerr << "Error: Not enough operands" << std::endl;
        return (false);
    }

    int b = stack.top();
    stack.pop();
    int a = stack.top();
    stack.pop();

    int result = 0;

    if (op == '+')
        result = a + b;
    else if (op == '-')
        result = a - b;
    else if (op == '*')
        result = a * b;
    else if (op == '/')
    {
        if (b == 0)
        {
            std::cerr << "Error: Division by zero" << std::endl;
            return (false);
        }
        result = a / b;
    }
    else
    {
        std::cerr << "Error: Unknown operator" << std::endl;
        return (false);
    }

    stack.push(result);
    return (true);
}

void RPN::calculate(const std::string &input)
{
    std::istringstream iss(input);
    std::string token;

    while (iss >> token)
    {
        if (token.length() == 1 && isDigit(token[0]))
        {
            stack.push(token[0] - '0');
        }
        else if (token.length() == 1 && isOperator(token[0]))
        {
            if (!executeOperation(token[0]))
                return;
        }
        else
        {
            std::cerr << "Error: Invalid input \"" << token << "\"" << std::endl;
            return;
        }
    }

    if (stack.size() != 1)
    {
        std::cerr << "Error: Invalid expression" << std::endl;
        return;
    }

    std::cout << "Result: " << stack.top() << std::endl;
}