/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Replace.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsarana <vsarana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 14:34:44 by vsarana           #+#    #+#             */
/*   Updated: 2024/11/26 14:34:45 by vsarana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REPLACE_HPP
#define REPLACE_HPP

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

class Replace
{
    private:
        std::string filename;
        std::string s1;
        std::string s2;
        std::string content;
    public:
        Replace(std::string filename, std::string s1, std::string s2);
        ~Replace();
        void replace();
        void display();
};

#endif