/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsarana <vsarana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 16:15:05 by vsarana           #+#    #+#             */
/*   Updated: 2024/12/03 18:39:43 by vsarana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../class/Animal.hpp"
#include "../class/Dog.hpp"
#include "../class/Cat.hpp"
#include "../class/WrongAnimal.hpp"
#include "../class/WrongCat.hpp"


void test_abstract_class()
{
   //Animal animal; // Error: cannot instantiate abstract class
    Dog dog;
    Cat cat;
    dog.makeSound();
    cat.makeSound();
}

void animal_array_test()
{
    std::cout << "Animal Array Test" << std::endl;
    
    const Animal* animals[10];

    for (int i = 0; i < 5; ++i)
    {
        animals[i] = new Dog();
        std::cout << "Animal " << i << " is a " << animals[i]->getType() << std::endl;
    }

    for (int i = 5; i < 10; ++i)
    {
        animals[i] = new Cat();
        std::cout << "Animal " << i << " is a " << animals[i]->getType() << std::endl;
    }

    std::cout << "Animals making sounds: " << std::endl;

    for (int i = 0; i < 10; ++i)
        animals[i]->makeSound();
    
    std::cout << "Deleting animals: " << std::endl;

    for (int i = 0; i < 10; ++i)
    {
        delete animals[i];
        std::cout << "Deleted animal " << i << std::endl;
    }
}


void subject_test()
{
    const Animal* j = new Dog();
    const Animal* i = new Cat();
    delete (j);//should not create a leak
    delete (i);
}

int main()
{
    //subject_test();
    test_abstract_class();
    //animal_array_test();
    //deep_copy_test();
    //idea_test();
    //error_idea_test();
    return (0);
}