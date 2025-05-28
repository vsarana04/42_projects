/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AForm.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsarana <vsarana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 16:01:14 by vsarana           #+#    #+#             */
/*   Updated: 2025/04/15 16:01:15 by vsarana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AForm.hpp"
#include "Bureaucrat.hpp"

AForm::AForm() : name("default"), isSigned(false), gradeToSign(1), gradeToExecute(1)
{
    std::cout << "AForm: Default constructor called" << std::endl;
    return ;
}

AForm::AForm(const std::string &name, const int gradeToSign, const int gradeToExecute) : name(name), isSigned(false), gradeToSign(gradeToSign), gradeToExecute(gradeToExecute)
{
    std::cout << "AForm: Parametric constructor called" << std::endl;
    if (gradeToSign < 1 || gradeToExecute < 1)
        throw AForm::GradeTooHighException();
    if (gradeToSign > 150 || gradeToExecute > 150)
        throw AForm::GradeTooLowException();
    return ;
}

AForm::AForm(const AForm &other) : name(other.name), isSigned(other.isSigned), gradeToSign(other.gradeToSign), gradeToExecute(other.gradeToExecute)
{
    std::cout << "AForm: Copy constructor called" << std::endl;
    return ;
}

AForm &AForm::operator=(const AForm &other)
{
    std::cout << "AForm: Assignation operator called" << std::endl;
    if (this != &other)
    {
        isSigned = other.isSigned;
    }
    return (*this);
}

AForm::~AForm()
{
    std::cout << "AForm: Destructor called" << std::endl;
    return ;
}

const std::string &AForm::getName() const
{
    return (name);
}

bool AForm::getIsSigned() const
{
    return (isSigned);
}

int AForm::getGradeToSign() const
{
    return (gradeToSign);
}

int AForm::getGradeToExecute() const
{
    return (gradeToExecute);
}

void AForm::beSigned(const Bureaucrat &bureaucrat)
{
    if (bureaucrat.getGrade() > gradeToSign)
        throw AForm::GradeTooLowException();
    isSigned = true;
    return ;
}

void AForm::execute(const Bureaucrat &exec) const
{
    if (!isSigned)
        throw AForm::FormNotSignedException();
    if (exec.getGrade() > gradeToExecute)
        throw AForm::GradeTooLowException();
    executeAction();
}

const char* AForm::GradeTooHighException::what() const throw()
{
    return ("AForm: Grade is too high");
}

const char* AForm::GradeTooLowException::what() const throw()
{
    return ("AForm: Grade is too low");
}

const char* AForm::FormNotSignedException::what() const throw()
{
    return ("AForm: AForm is not signed");
}

std::ostream &operator<<(std::ostream &out, const AForm &obj)
{
    out << "AForm " << obj.getName() << " is ";
    if (obj.getIsSigned())
        out << "signed";
    else
        out << "not signed";
    out << " and requires grade " << obj.getGradeToSign() << " to sign and grade " << obj.getGradeToExecute() << " to execute";
    return (out);
}
