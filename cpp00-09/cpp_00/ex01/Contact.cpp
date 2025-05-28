/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Contact.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsarana <vsarana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 16:58:05 by vsarana           #+#    #+#             */
/*   Updated: 2024/11/22 16:58:07 by vsarana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Contact.hpp"

Contact::Contact()
{
    first_name = "";
    last_name = "";
    nickname = "";
    phone_number = "";
    darkest_secret = "";
}

void Contact::set_contact(std::string fname, std::string lname, std::string nname, std::string pnumber, std::string dsecret) 
{
    first_name = fname;
    last_name = lname;
    nickname = nname;
    phone_number = pnumber;
    darkest_secret = dsecret;
}

std::string Contact::get_first_name() const 
{
    return (first_name);
}

std::string Contact::get_last_name() const 
{
    return (last_name);
}

std::string Contact::get_nickname() const 
{
    return (nickname);
}

std::string Contact::get_phone_number() const 
{
    return (phone_number);
}

std::string Contact::get_darkest_secret() const 
{
    return (darkest_secret);
}
