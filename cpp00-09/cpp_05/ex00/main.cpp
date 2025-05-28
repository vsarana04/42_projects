/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsarana <vsarana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 15:57:10 by vsarana           #+#    #+#             */
/*   Updated: 2025/04/15 15:57:20 by vsarana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../class/Bureaucrat.hpp"

void test1()
{
    try
    {
        //Bureaucrat b("b", 0);
        //Bureaucrat b("b", 152);
        //Bureaucrat b("b", -2);
        Bureaucrat b("b", 3);
        std::cout << b.getName() << std::endl;
        std::cout << b.getGrade() << std::endl;
        std::cout << b << std::endl;

        b.incrementGrade();
        std::cout << b.getGrade() << std::endl;
        b.decrementGrade();
        std::cout << b.getGrade() << std::endl;
        b.decrementGrade();
        std::cout << b.getGrade() << std::endl;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    std::cout << "End of test1" << std::endl;
}

void    test2()
{
    try
    {
        Bureaucrat alice("Alice", 75);
        Bureaucrat bob("Bob", 149);
        std::cout << "Before assignment:" << std::endl;
        std::cout << "Alice: " << alice << std::endl;
        std::cout << "Bob: " << bob << std::endl;

        alice = bob;
        
        std::cout << "After assignment:" << std::endl;
        std::cout << "Alice: " << alice << std::endl;
    }
    catch (const std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
    std::cout << "End of test2" << std::endl;
}

int main()
{
    test1();
    //test2();
    return (0);
}