/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ShrubberyCreationForm.cpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsarana <vsarana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 16:01:27 by vsarana           #+#    #+#             */
/*   Updated: 2025/04/15 16:01:28 by vsarana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ShrubberyCreationForm.hpp"

ShrubberyCreationForm::ShrubberyCreationForm(const std::string &target) : AForm("ShrubberyCreationForm", 145, 137), target(target)
{
    std::cout << "ShrubberyCreationForm: Parametric constructor called" << std::endl;
    return ;
}

void ShrubberyCreationForm::executeAction() const
{
    std::string filename = target + "_shrubbery";
    std::ofstream file(filename.c_str());
    if (!file)
    {
        std::cerr << "Error: Could not open file" << std::endl;
        return ;
    }
    file <<
        "      /\\\n"
        "     /**\\\n"
        "    /****\\\n"
        "   /******\\\n"
        "  /********\\\n"
        "      ||\n"
        "      ||\n";
    file.close();
}

ShrubberyCreationForm::~ShrubberyCreationForm()
{
    std::cout << "ShrubberyCreationForm: Destructor called" << std::endl;
    return ;
}
