/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhoneBook.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsarana <vsarana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 16:58:38 by vsarana           #+#    #+#             */
/*   Updated: 2024/11/22 16:58:41 by vsarana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PhoneBook.hpp"
#include <iostream>
#include <iomanip>

PhoneBook::PhoneBook()
{
    index = 0;
    total_contacts = 0;
}

bool PhoneBook::check_contacts(const std::string& prompt) 
{
    if (total_contacts == 0) 
    {
        std::cout << prompt << std::endl;
        return (false);
    }
    return (true);
}

void PhoneBook::add_contact(const Contact& contact)
{
    contacts[index] = contact;
    index = (index + 1) % 8;
    if (total_contacts < 8)
        total_contacts++;
}

void PhoneBook::display_headers() const 
{
    std::cout << "" << std::endl;
    std::cout << std::setw(10) << "Index" << "|"
              << std::setw(10) << "First Name" << "|"
              << std::setw(10) << "Last Name" << "|"
              << std::setw(10) << "Nickname" << std::endl;
}

std::string PhoneBook::trim_name(const std::string& name) const
{
    if (name.length() > 10) 
        return (name.substr(0, 9) + ".");
    else
        return (name);
}

void PhoneBook::display_contact(int i) const 
{
    std::cout << std::setw(10) << i << "|"
              << std::setw(10) << trim_name(contacts[i].get_first_name()) << "|"
              << std::setw(10) << trim_name(contacts[i].get_last_name()) << "|"
              << std::setw(10) << trim_name(contacts[i].get_nickname()) << std::endl;
}

void PhoneBook::display_contacts() const 
{
    display_headers();
    for (int i = 0; i < total_contacts; i++)
        display_contact(i);
    std::cout << "" << std::endl;
}

void PhoneBook::display_details(int index) const 
{
    if (index < 0 || index >= total_contacts) 
    {
        std::cout << "Error\nInvalid index!" << std::endl;
        return ;
    }
    std::cout << "First Name: " << contacts[index].get_first_name() << std::endl;
    std::cout << "Last Name: " << contacts[index].get_last_name() << std::endl;
    std::cout << "Nickname: " << contacts[index].get_nickname() << std::endl;
    std::cout << "Phone Number: " << contacts[index].get_phone_number() << std::endl;
    std::cout << "Darkest Secret: " << contacts[index].get_darkest_secret() << std::endl;
}