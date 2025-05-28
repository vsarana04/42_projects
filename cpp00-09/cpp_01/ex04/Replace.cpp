/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Replace.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsarana <vsarana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 14:34:34 by vsarana           #+#    #+#             */
/*   Updated: 2024/11/26 14:34:35 by vsarana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Replace.hpp"

Replace::Replace(std::string filename, std::string s1, std::string s2)
{
    this->filename = filename;
    this->s1 = s1;
    this->s2 = s2;
    this->content = "";

    std::cout << "Replace object created" << std::endl;
    std::cout << "filename: " << this->filename << std::endl;
    std::cout << "string 1: " << this->s1 << std::endl;
    std::cout << "string 2: " << this->s2 << std::endl;
    std::cout << "content: " << this->content << std::endl;
    return ;
}

Replace::~Replace()
{
    std::cout << "Replace object destroyed" << std::endl;
    return ;
}

void Replace::replace()
{
    std::ifstream file;
    file.open(this->filename.c_str());

    if (!file.is_open()) 
    {
        std::cerr << "Error\nCannot open file" << this->filename << std::endl;
        return ;
    }
    this->content.assign((std::istreambuf_iterator<char>(file)),
                         std::istreambuf_iterator<char>());
    file.close();

    std::string result;
    size_t pos;
    size_t prev_pos = 0;
    pos = 0;
    prev_pos = 0;

    while ((pos = this->content.find(this->s1, prev_pos)) != std::string::npos) 
    {
        result.append(this->content, prev_pos, pos - prev_pos);
        result.append(this->s2);
        prev_pos = pos + this->s1.length();
    }

    result.append(this->content, prev_pos, this->content.length() - prev_pos);

    std::ofstream output;
    output.open((this->filename + ".replace").c_str());
    if (!output.is_open()) 
    {
        std::cerr << "Error\nCannot create file" << this->filename << ".replace" << std::endl;
        return ;
    }
    output << result;
    output.close();
    std::cout << "Replacement complete. Output saved to" << this->filename << ".replace" << std::endl;
    return ;
}

void Replace::display()
{
    std::cout << this->content << std::endl;
    std::cout << "Display complete" << std::endl;
    return ;
}