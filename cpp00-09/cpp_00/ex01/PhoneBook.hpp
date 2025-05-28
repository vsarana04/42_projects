/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhoneBook.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsarana <vsarana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 16:58:45 by vsarana           #+#    #+#             */
/*   Updated: 2024/11/22 16:58:46 by vsarana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHONEBOOK_HPP
# define PHONEBOOK_HPP

#include "Contact.hpp"

class PhoneBook 
{
    private:
        Contact contacts[8];
        int index;
        int total_contacts;


    public:
        PhoneBook();
        void add_contact(const Contact& contact);
        void display_headers() const;
        void display_contact(int i) const;
        void display_contacts() const;
        void display_details(int index) const;
        std::string trim_name(const std::string& name) const;
        bool check_contacts(const std::string& prompt);
};

#endif