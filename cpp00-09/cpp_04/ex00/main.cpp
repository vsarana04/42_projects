/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsarana <vsarana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 16:15:05 by vsarana           #+#    #+#             */
/*   Updated: 2024/12/03 18:51:07 by vsarana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../class/Animal.hpp"
#include "../class/Dog.hpp"
#include "../class/Cat.hpp"
#include "../class/WrongAnimal.hpp"
#include "../class/WrongCat.hpp"

void reference_test()
{
    std::cout << "Reference test" << std::endl;
    Dog dog;
    Cat cat;
    Animal &animal = dog;
    Animal &animal2 = cat;

    animal.makeSound();
    animal2.makeSound();
}

void copy_test()
{
    std::cout << "Copy test" << std::endl;
    Dog dog;
    Dog dog2(dog);

    dog.makeSound();
    dog2.makeSound();

}

void wrong_animal_test()
{
    const WrongAnimal* meta = new WrongAnimal();
    const WrongAnimal* i = new WrongCat();

    std::cout << i->getType() << " " << std::endl;
    i->makeSound(); //will output the wrong cat sound!
    meta->makeSound();

    delete (i);
    delete (meta);
}

void subject_test()
{
    const Animal* meta = new Animal();
    const Animal* j = new Dog();
    const Animal* i = new Cat();

    std::cout << j->getType() << " " << std::endl;
    std::cout << i->getType() << " " << std::endl;
    i->makeSound(); //will output the cat sound!
    j->makeSound();
    meta->makeSound();

    delete (j);
    delete (i);
    delete (meta);
}

int main()
{
    subject_test();
    //wrong_animal_test();
    //copy_test();
    //reference_test();
    return (0);
}