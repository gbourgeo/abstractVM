/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OperandFactory.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/02 13:13:53 by gbourgeo          #+#    #+#             */
/*   Updated: 2021/01/23 15:55:45 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "OperandFactory.hpp"

OperandFactory::OperandFactory()
{}

OperandFactory::~OperandFactory()
{}

OperandFactory::OperandFactory(OperandFactory const & src)
{
	*this = src;
}

OperandFactory & OperandFactory::operator=(OperandFactory const & rhs)
{
	(void)rhs;
	return *this;
}

IOperand const * OperandFactory::createOperand( IOperand::eOperandType type, std::string const & value) const
{
	typedef IOperand const * (OperandFactory::*funcType)(std::string const &) const;
	static funcType func[] = {
		&OperandFactory::createInt8,
		&OperandFactory::createInt16,
		&OperandFactory::createInt32,
		&OperandFactory::createFloat,
		&OperandFactory::createDouble,
	};

	if (type >= sizeof(func) / sizeof(func[0]))
		return nullptr;
	return (this->*func[type])(value);
}

IOperand const * OperandFactory::createInt8( std::string const & value) const
{
	return new Operand(value, IOperand::Int8, 0);
}

IOperand const * OperandFactory::createInt16( std::string const & value) const
{
	return new Operand(value, IOperand::Int16, 0);
}

IOperand const * OperandFactory::createInt32( std::string const & value) const
{
	return new Operand(value, IOperand::Int32, 0);
}

IOperand const * OperandFactory::createFloat( std::string const & value) const
{
	return new Operand(value, IOperand::Float, 0);
}

IOperand const * OperandFactory::createDouble( std::string const & value) const
{
	return new Operand(value, IOperand::Double, 0);
}
