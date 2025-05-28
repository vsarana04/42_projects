/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsarana <vsarana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 15:59:07 by vsarana           #+#    #+#             */
/*   Updated: 2025/04/15 15:59:21 by vsarana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../class/Bureaucrat.hpp"
#include "../class/Form.hpp"

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

void test3()
{
    try
    {
        Form form("Form1", 50, 25);
        Bureaucrat alice("Alice", 30);
        Bureaucrat bob("Bob", 100);

        std::cout << form << std::endl;

        alice.signForm(form); // success sign
        std::cout << form << std::endl;

        bob.signForm(form); // try to sign again
    }
    catch (const std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
    std::cout << "End of test3" << std::endl;
}

void test4()
{
    try
    {
        //incorrect grade
        Form invalidForm("InvalidForm", 0, 25); //throws exception
    }
    catch (const std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    try
    {
        Form form("Form2", 75, 100);
        Bureaucrat bob("Bob", 149);

        bob.signForm(form); //not enough grade to sign
    }
    catch (const std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
    std::cout << "End of test4" << std::endl;
}



int main()
{
    //test1();
    //test2();
    test3();
    //test4();
    return (0);

}