/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Form.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsarana <vsarana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 15:58:49 by vsarana           #+#    #+#             */
/*   Updated: 2025/04/15 15:58:50 by vsarana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Form.hpp"
#include "Bureaucrat.hpp"

Form::Form() : name("default"), isSigned(false), gradeToSign(1), gradeToExecute(1)
{
    std::cout << "Form: Default constructor called" << std::endl;
    return ;
}

Form::Form(const std::string &name, const int gradeToSign, const int gradeToExecute) : name(name), isSigned(false), gradeToSign(gradeToSign), gradeToExecute(gradeToExecute)
{
    std::cout << "Form: Parametric constructor called" << std::endl;
    if (gradeToSign < 1 || gradeToExecute < 1)
        throw Form::GradeTooHighException();
    if (gradeToSign > 150 || gradeToExecute > 150)
        throw Form::GradeTooLowException();
    return ;
}

Form::Form(const Form &other) : name(other.name), isSigned(other.isSigned), gradeToSign(other.gradeToSign), gradeToExecute(other.gradeToExecute)
{
    std::cout << "Form: Copy constructor called" << std::endl;
    return ;
}

Form &Form::operator=(const Form &other)
{
    std::cout << "Form: Assignation operator called" << std::endl;
    if (this != &other)
    {
        isSigned = other.isSigned;
    }
    return (*this);
}

Form::~Form()
{
    std::cout << "Form: Destructor called" << std::endl;
    return ;
}

const std::string &Form::getName() const
{
    return (name);
}

bool Form::getIsSigned() const
{
    return (isSigned);
}

int Form::getGradeToSign() const
{
    return (gradeToSign);
}

int Form::getGradeToExecute() const
{
    return (gradeToExecute);
}

void Form::beSigned(const Bureaucrat &bureaucrat)
{
    if (bureaucrat.getGrade() > gradeToSign)
        throw Form::GradeTooLowException();
    isSigned = true;
    return ;
}

const char* Form::GradeTooHighException::what() const throw()
{
    return ("Form: Grade is too high");
}

const char* Form::GradeTooLowException::what() const throw()
{
    return ("Form: Grade is too low");
}

std::ostream &operator<<(std::ostream &out, const Form &obj)
{
    out << "Form " << obj.getName() << " is ";
    if (obj.getIsSigned())
        out << "signed";
    else
        out << "not signed";
    out << " and requires grade " << obj.getGradeToSign() << " to sign and grade " << obj.getGradeToExecute() << " to execute";
    return (out);
}
