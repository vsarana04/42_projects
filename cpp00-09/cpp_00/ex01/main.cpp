/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsarana <vsarana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 16:58:23 by vsarana           #+#    #+#             */
/*   Updated: 2024/11/22 16:58:24 by vsarana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PhoneBook.hpp"
#include "Contact.hpp"

std::string is_empty(const std::string& prompt) 
{
    std::string input;

    while (true)
    {
        std::cout << prompt;
        std::getline(std::cin, input);
        if (!input.empty()) 
            break ;
        std::cout << "Error\nFields cannot be empty. Please try again." << std::endl;
    }
    return (input);
}

int main() 
{
    PhoneBook phonebook;
    std::string command;
    int index;

    while (true) 
    {
        std::cout << "Enter command (ADD, SEARCH, EXIT): ";
        std::getline(std::cin, command);

        if (command == "ADD") 
        {
            Contact contact;
            std::string firstname, lastname, nickname, phonenumber, darkestsecret;

            firstname = is_empty("Enter first name: ");
            lastname = is_empty("Enter last name: ");
            nickname = is_empty("Enter nickname: ");
            phonenumber = is_empty("Enter phone number: ");
            darkestsecret = is_empty("Enter darkest secret: ");
            contact.set_contact(firstname, lastname, nickname, phonenumber, darkestsecret);
            phonebook.add_contact(contact);
        }
        else if (command == "SEARCH") 
        {
            if (!phonebook.check_contacts("No contacts available. Please add a contact.")) 
                continue ;
            phonebook.display_contacts();
            std::cout << "Enter index to view details: ";
            while (!(std::cin >> index))
            {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Error\nInvalid index! Please try again: ";
            }
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            phonebook.display_details(index);
        }
        else if (command == "EXIT") 
            break ;
        else
            std::cout << "Error\nInvalid command!" << std::endl;
    }
    return (0);
}
