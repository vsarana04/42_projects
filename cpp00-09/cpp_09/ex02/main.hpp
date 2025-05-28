/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsarana <vsarana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 12:45:47 by vsarana           #+#    #+#             */
/*   Updated: 2025/05/05 12:45:48 by vsarana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_HPP
#define MAIN_HPP

#include <iostream>
#include <vector>
#include <list>

void printBefore(const std::vector<int>& data);
void printAfter(const std::vector<int>& data);
void printTiming(double vecTime, double listTime, size_t size);

#endif
