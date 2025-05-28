/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsarana <vsarana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 16:15:05 by vsarana           #+#    #+#             */
/*   Updated: 2024/12/03 18:54:06 by vsarana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../class/Animal.hpp"
#include "../class/Dog.hpp"
#include "../class/Cat.hpp"
#include "../class/WrongAnimal.hpp"
#include "../class/WrongCat.hpp"

/* void error_idea_test() 
{
    std::cout << "Error Idea Test" << std::endl;

    Dog dog1;
    
    dog1.getBrain()->setIdea("Valid Idea", 50);
    dog1.getBrain()->setIdea("Invalid Idea", -1);
    dog1.getBrain()->setIdea("Invalid Idea", 150);
    
    std::cout << "Dog1 Brain Idea (valid index 50): " << dog1.getBrain()->getIdea(50) << std::endl;
    std::cout << "Dog1 Brain Idea (invalid index -1): " << dog1.getBrain()->getIdea(-1) << std::endl;
    std::cout << "Dog1 Brain Idea (invalid index 150): " << dog1.getBrain()->getIdea(150) << std::endl;

    for (int i = -2; i <= 102; ++i)
        std::cout << "Checking Brain index " << i << ": " << dog1.getBrain()->getIdea(i) << std::endl;
} */

void idea_test()
{
    std::cout << "Idea Test" << std::endl;

    Dog dog1;
    for (int i = 0; i < 10; ++i)
        dog1.getBrain()->setIdea("First Idea ", i);

    Dog dog2(dog1);
    for (int i = 0; i < 5; ++i)
        dog2.getBrain()->setIdea("Modified Idea ", i);


    std::cout << "Dog1 Brain Ideas: " << std::endl;
    
    for (int i = 0; i < 10; ++i)
        std::cout << "  Idea " << i << ": " << dog1.getBrain()->getIdea(i) << std::endl;
        
    std::cout << "Dog2 Brain Ideas: " << std::endl;
    
    for (int i = 0; i < 10; ++i)
        std::cout << "  Idea " << i << ": " << dog2.getBrain()->getIdea(i) << std::endl;
}

void deep_copy_test() 
{
    std::cout << "Deep Copy Test" << std::endl;
    
    Dog dog1;
    dog1.getBrain()->setIdea("Chase the ball", 0);

    Dog dog2(dog1);
    dog2.getBrain()->setIdea("Eat food", 0);

    std::cout << "Dog1 Brain Idea 0: " << dog1.getBrain()->getIdea(0) << std::endl;
    std::cout << "Dog2 Brain Idea 0: " << dog2.getBrain()->getIdea(0) << std::endl;
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
    subject_test();
    //animal_array_test();
    //deep_copy_test();
    //idea_test();
    //error_idea_test();
    return (0);
}