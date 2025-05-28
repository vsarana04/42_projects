/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsarana <vsarana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 16:01:31 by vsarana           #+#    #+#             */
/*   Updated: 2025/04/15 16:01:53 by vsarana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"

//test ShrubberyCreationForm
void test1()
{

    Bureaucrat alice("Alice", 1);
    ShrubberyCreationForm form("home");

    std::cout << form << std::endl;

    try
    {
        form.beSigned(alice);
        alice.executeForm(form);
    }
    catch (const std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
}

//test RobotomyRequestForm
void test2()
{
    Bureaucrat bob("Bob", 1);
    RobotomyRequestForm form("robot");

    std::cout << form << std::endl;

    try
    {
        form.beSigned(bob);
        for (int i = 0; i < 5; ++i)
        {
            bob.executeForm(form);
        } // 5 times to test the randomness
    }
    catch (const std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
}

//test PresidentialPardonForm
void test3()
{
    Bureaucrat charlie("Charlie", 1);
    PresidentialPardonForm form("target");

    std::cout << form << std::endl;

    try
    {
        form.beSigned(charlie);
        charlie.executeForm(form);
    }
    catch (const std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
}

//low grade test
void test()
{

    Bureaucrat alice("Alice", 150);
    ShrubberyCreationForm form("backyard");

    try
    {
        form.beSigned(alice);
        alice.executeForm(form);
    }
    catch (const std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
}

int main()
{
    //test1();
    //test2();
    test3();
    //test();
    return (0);
}