/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Operand.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 01:41:01 by gbourgeo          #+#    #+#             */
/*   Updated: 2021/01/02 14:20:07 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Operand.hpp"

Operand::Operand(): _value(0), _type(Int8), _precision(0)
{}

Operand::~Operand()
{}

Operand::Operand(Operand const & src)
{
	*this = src;
}

Operand & Operand::operator=(Operand const & rhs)
{
	if (this != &rhs)
	{
		this->_value = rhs._value;
		this->_type = rhs._type;
		this->_precision = rhs._precision;
	}
	return *this;
}

int Operand::getPrecision( void ) const
{
	return this->_precision;
}

eOperandType Operand::getType( void ) const
{
	return this->_type;
}

IOperand const * Operand::operator+( IOperand const & rhs ) const
{
	(void)rhs;
	return this;
}

IOperand const * Operand::operator-( IOperand const & rhs ) const
{
	(void)rhs;
	return this;
}

IOperand const * Operand::operator*( IOperand const & rhs ) const
{
	(void)rhs;
	return this;
}

IOperand const * Operand::operator/( IOperand const & rhs ) const
{
	(void)rhs;
	return this;
}

IOperand const * Operand::operator%( IOperand const & rhs ) const
{
	(void)rhs;
	return this;
}

std::string const & Operand::toString( void ) const
{
	const char	*type[] = {
		"Int8", "Int16", "Int32", "Float", "Double",
	};
	static std::string	ret;

	ret = "Type: " + std::string(type[this->_type])
		+ ", Value: " + this->_value
		+ ", Precision: " + std::to_string(this->_precision);
	return ret;
}

Operand::Operand(std::string const & value, eOperandType type):
	_value(value), _type(type), _precision(0)
{}

Operand::Operand(std::string const & value, eOperandType type, int precision):
	_value(value), _type(type), _precision(precision)
{}
