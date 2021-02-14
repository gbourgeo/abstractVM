/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Instructions.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 18:53:22 by gbourgeo          #+#    #+#             */
/*   Updated: 2021/02/14 12:20:27 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Instructions.hpp"

Instructions::t_inst	Instructions::_instructions[] = {
	/* Name     Type                  Nb_args */
	{ "push",   Instructions::Push,   1 },
	{ "pop",    Instructions::Pop,    0 },
	{ "dump",   Instructions::Dump,   0 },
	{ "assert", Instructions::Assert, 1 },
	{ "add",    Instructions::Add,    0 },
	{ "sub",    Instructions::Sub,    0 },
	{ "mul",    Instructions::Mul,    0 },
	{ "div",    Instructions::Div,    0 },
	{ "mod",    Instructions::Mod,    0 },
	{ "print",  Instructions::Print,  0 },
	{ "exit",   Instructions::Exit,   0 },
};

Instructions::t_ope		Instructions::_values[] = {
	{ "int8",   IOperand::Int8  , &Instructions::intOperandCheck },
	{ "int16",  IOperand::Int16 , &Instructions::intOperandCheck },
	{ "int32",  IOperand::Int32 , &Instructions::intOperandCheck },
	{ "float",  IOperand::Float , &Instructions::pointOperandCheck },
	{ "double", IOperand::Double, &Instructions::pointOperandCheck },
	{ "",       IOperand::None,   &Instructions::noCheck },
};

Instructions::Instructions()
{}

Instructions::~Instructions()
{}

Instructions::Instructions(Instructions const & src)
{
	*this = src;
}

Instructions & Instructions::operator=(Instructions const & rhs)
{
	if (this != &rhs)
	{

	}
	return *this;
}

Instructions::InstructionsException::InstructionsException(const char * error, std::string const & value)
{
	this->_error = "Error : " + std::string(error) + " : " + value + ".";
}

Instructions::eInstructionType	Instructions::getInstruction(std::string const & token) const
{
	for (std::size_t i = 0; i < sizeof(this->_instructions) / sizeof(this->_instructions[0]); i++)
		if (token.compare(this->_instructions[i].name) == 0)
			return this->_instructions[i].type;
	throw Instructions::InstructionsException("Instruction name unknown", token);
}

std::size_t						Instructions::getInstructionNbArgs(std::string const & token, std::size_t nbArgs) const
{
	for (std::size_t i = 0; i < sizeof(this->_instructions) / sizeof(this->_instructions[0]); i++)
		if (token.compare(this->_instructions[i].name) == 0)
		{
			if (nbArgs < this->_instructions[i].nbArgs + 1)
				throw Instructions::InstructionsException("Missing argument for instruction", token);
			if (nbArgs > this->_instructions[i].nbArgs + 1)
				throw Instructions::InstructionsException("Too many values for instruction", token);
			return this->_instructions[i].nbArgs;
		}
	throw Instructions::InstructionsException("Instruction name unknown", token);
}

IOperand::eOperandType			Instructions::getOperand(std::string const & token) const
{
	std::size_t			parent_left;

	parent_left = token.find('(');
	if (parent_left == std::string::npos)
		throw Instructions::InstructionsException("Invalid operand format : Missing '('", token);
	for (std::size_t i = 0; i < sizeof(this->_values) / sizeof(this->_values[0]); i++)
		if (token.compare(0, parent_left, this->_values[i].name) == 0)
			return this->_values[i].type;
	throw Instructions::InstructionsException("Operand name unknown", token);
}

std::string						Instructions::getOperandValue(IOperand::eOperandType type, std::string const & token) const
{
	std::size_t		parent_left;
	std::size_t		parent_right;
	std::string		value;

	parent_left  = token.find('(');
	parent_right = token.find(')');
	if (parent_right == std::string::npos)
		throw Instructions::InstructionsException("Invalid operand format : Missing ')'", token);
	value = token.substr(parent_left + 1, parent_right - parent_left - 1);
	(this->*this->_values[Instructions::getOperand(token)].checkOperand)(type, value);
	return value;
}

const char *			Instructions::getInstruction(eInstructionType type) const
{
	return this->_instructions[type].name;
}

const char *			Instructions::getOperand(IOperand::eOperandType type) const
{
	return this->_values[type].name;
}

void			Instructions::intOperandCheck(IOperand::eOperandType type, std::string const & value) const
{
	std::size_t	i;
	long		lvalue;

	if (value.length() == 0)
		throw Instructions::InstructionsException("Operand value empty", value);
	for (i = (value.at(0) == '-'); i < value.length(); i++)
	{
		if (!(value.at(i) >= '0' && value.at(i) <= '9'))
			throw Instructions::InstructionsException("Invalid operand value", value);
	}
	try
	{
		lvalue = std::stol(value);
	}
	catch (...)
	{
			throw Instructions::InstructionsException("Invalid operand value", value);
	}
	if (type == IOperand::Int8)
	{
		if (lvalue < std::numeric_limits<int8_t>::min())
			throw Instructions::InstructionsException("Underflow on operand value", value);
		if (lvalue > std::numeric_limits<int8_t>::max())
			throw Instructions::InstructionsException("Overflow on operand value", value);
	}
	else if (type == IOperand::Int16)
	{
		if (lvalue < std::numeric_limits<int16_t>::min())
			throw Instructions::InstructionsException("Underflow on operand value", value);
		if (lvalue > std::numeric_limits<int16_t>::max())
			throw Instructions::InstructionsException("Overflow on operand value", value);
	}
	else if (type == IOperand::Int32)
	{
		if (lvalue < std::numeric_limits<int32_t>::min())
			throw Instructions::InstructionsException("Underflow on operand value", value);
		if (lvalue > std::numeric_limits<int32_t>::max())
			throw Instructions::InstructionsException("Overflow on operand value", value);
	}
}

void			Instructions::pointOperandCheck(IOperand::eOperandType type, std::string const & value) const
{
	std::size_t	i;
	std::string	fstring;
	int			found_point;

	(void)type;
	found_point = 0;
	if (value.length() == 0)
		throw Instructions::InstructionsException("Operand value empty", value);
	/* Check value is only digit and have a single '.' in value,
	 * skip the negative character at the begining if present
	 */
	for (i = (value.at(0) == '-'); i < value.length(); i++)
	{
		if (std::isdigit(value.at(i)))
			continue ;
		if (found_point != 0)
			throw Instructions::InstructionsException("Invalid operand value", value);
		found_point = (value.at(i) == '.');
		if (found_point == 0)
			throw Instructions::InstructionsException("Invalid operand value", value);
	}
	/* Validation on decimal value */
	if (found_point == 0)
		throw Instructions::InstructionsException("Invalid operand value : Missing point", value);
	/* Validation on decimal value */
	int point_len = value.length() - value.find('.') - 1;
	if (point_len > 6)
		throw Instructions::InstructionsException("Invalid operand value : Floating point too long", value);
	/* Validation on Over/underflow value */
	Instructions::intOperandCheck(IOperand::Int32, value.substr(0, value.find('.')));
}

void			Instructions::noCheck(IOperand::eOperandType type, std::string const & value) const
{
	(void)type;
	(void)value;
}
