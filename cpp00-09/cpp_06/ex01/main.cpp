/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsarana <vsarana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 14:28:17 by vsarana           #+#    #+#             */
/*   Updated: 2025/04/16 14:28:18 by vsarana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../class/Serializer.hpp"

int main()
{
    Data original;
    original.id = 7;
    original.name = "Bob";
    original.score = 99.5f;

    uintptr_t address = Serializer::serialize(&original);
    std::cout << "Serialized value: " << address << std::endl;

    Data* deserialized = Serializer::deserialize(address);

    std::cout << "\n[Pointer Comparison]" << std::endl;
    if (deserialized == &original)
        std::cout << "Deserialized pointer matches original pointer." << std::endl;
    else
        std::cout << "Deserialized pointer does NOT match original pointer." << std::endl;

    std::cout << "\n[Data Contents After Deserialization]" << std::endl;
    std::cout << "ID    : " << deserialized->id << std::endl;
    std::cout << "Name  : " << deserialized->name << std::endl;
    std::cout << "Score : " << deserialized->score << std::endl;

    return (0);
}
