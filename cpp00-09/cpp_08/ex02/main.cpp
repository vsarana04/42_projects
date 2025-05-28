/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsarana <vsarana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 11:40:09 by vsarana           #+#    #+#             */
/*   Updated: 2025/04/30 11:40:10 by vsarana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "MutantStack.hpp"

int subjectTest()
{
    MutantStack<int> mstack;
    mstack.push(5);
    mstack.push(17);
    std::cout << mstack.top() << std::endl;
    mstack.pop();
    std::cout << mstack.size() << std::endl;
    mstack.push(3);
    mstack.push(5);
    mstack.push(737);

    mstack.push(0);
    MutantStack<int>::iterator it = mstack.begin();
    MutantStack<int>::iterator ite = mstack.end();
    ++it;
    --it;
    while (it != ite)
    {
        std::cout << *it << std::endl;
        ++it;
    }
    std::stack<int> s(mstack);

    return (0);
}

void test1()
{

    MutantStack<std::string> stack;

    stack.push("hello");
    stack.push("world");
    stack.push("42");
    stack.push("mutant");
    stack.push("stack");

    std::cout << "Top element: " << stack.top() << std::endl;

    std::cout << "All elements (top to bottom):" << std::endl;
    MutantStack<std::string>::iterator it = stack.begin();
    MutantStack<std::string>::iterator ite = stack.end();
    for (; it != ite; ++it)
        std::cout << *it << std::endl;

    std::cout << "Popping top element..." << std::endl;
    stack.pop();

    std::cout << "New top: " << stack.top() << std::endl;
    std::cout << "Size: " << stack.size() << std::endl;
}

int main()
{
    //subjectTest();
    test1();
    return (0);
}