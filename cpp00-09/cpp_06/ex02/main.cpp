/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsarana <vsarana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 14:28:42 by vsarana           #+#    #+#             */
/*   Updated: 2025/04/16 14:28:43 by vsarana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../class/Base.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <exception>
#include <typeinfo>

Base* generate()
{
    std::srand(static_cast<unsigned int>(std::time(0)));
    int random = std::rand() % 3;

    switch (random)
    {
        case 0: return new A();
        case 1: return new B();
        case 2: return new C();
    }
    return (0);
}

void identify(Base* p)
{
    if (dynamic_cast<A*>(p))
        std::cout << "A" << std::endl;
    else if (dynamic_cast<B*>(p))
        std::cout << "B" << std::endl;
    else if (dynamic_cast<C*>(p))
        std::cout << "C" << std::endl;
    else
        std::cout << "Unknown type" << std::endl;
}

void identify(Base& p)
{
    try
    {
        (void)dynamic_cast<A&>(p);
        std::cout << "A" << std::endl;
        return;
    }
    catch (std::bad_cast&) {}

    try
    {
        (void)dynamic_cast<B&>(p);
        std::cout << "B" << std::endl;
        return;
    }
    catch (std::bad_cast&) {}

    try
    {
        (void)dynamic_cast<C&>(p);
        std::cout << "C" << std::endl;
        return;
    }
    catch (std::bad_cast&) {}

    std::cout << "Unknown type" << std::endl;
}

int main()
{

    for (int i = 0; i < 5; ++i)
    {
        Base* ptr = generate();

        std::cout << "[Test " << i + 1 << "]" << std::endl;
        std::cout << "identify(Base*): ";
        identify(ptr);

        std::cout << "identify(Base&): ";
        identify(*ptr);

        delete (ptr);
    }

    return (0);
}