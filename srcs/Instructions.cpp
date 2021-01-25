/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Instructions.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 18:53:22 by gbourgeo          #+#    #+#             */
/*   Updated: 2021/01/24 13:27:31 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Instructions.hpp"

Instructions::t_inst	Instructions::_instructions[] = {
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
	{ "float",  IOperand::Float , &Instructions::floatOperandCheck },
	{ "double", IOperand::Double, &Instructions::doubleOperandCheck },
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
	this->_error = value + ": " + std::string(error) + ".";
}

Instructions::eInstructionType	Instructions::getInstruction(std::string const & token) const
{
	for (std::size_t i = 0; i < sizeof(this->_instructions) / sizeof(this->_instructions[0]); i++)
		if (token.compare(this->_instructions[i].name) == 0)
			return this->_instructions[i].type;
	throw Instructions::InstructionsException("Invalid instruction : name unknown", token);
}

std::size_t						Instructions::getInstructionNbArgs(std::string const & token) const
{
	for (std::size_t i = 0; i < sizeof(this->_instructions) / sizeof(this->_instructions[0]); i++)
		if (token.compare(this->_instructions[i].name) == 0)
			return this->_instructions[i].nbArgs;
	throw Instructions::InstructionsException("Invalid instruction : name unknown", token);
}

IOperand::eOperandType			Instructions::getOperand(std::string const & token) const
{
	std::size_t			parent_left;

	parent_left = token.find('(');
	if (parent_left == std::string::npos)
		throw Instructions::InstructionsException("Invalid operand format: Missing '('", token);
	for (std::size_t i = 0; i < sizeof(this->_values) / sizeof(this->_values[0]); i++)
		if (token.compare(0, parent_left, this->_values[i].name) == 0)
			return this->_values[i].type;
	throw Instructions::InstructionsException("Invalid operand : name unknown", token);
}

std::string						Instructions::getOperandValue(std::string const & token) const
{
	std::size_t		parent_left;
	std::size_t		parent_right;
	std::string		value;

	parent_left  = token.find('(');
	parent_right = token.find(')');
	if (parent_right == std::string::npos)
		throw Instructions::InstructionsException("Invalid operand format: Missing ')'", token);
	value = token.substr(parent_left + 1, parent_right - parent_left - 1);
	(this->*this->_values[Instructions::getOperand(token)].checkOperand)(value);
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


void			Instructions::intOperandCheck(std::string const & value) const
{
	std::size_t		i;

	if (value.length() == 0)
		throw Instructions::InstructionsException("Invalid operand value: Empty value", value);
	for (i = 0; i < value.length(); i++)
	{
		if ((value.at(i) == '-' && i != 0)
		|| !(value.at(i) >= '0' && value.at(i) <= '9'))
			throw Instructions::InstructionsException("Invalid operand value", value);
	}
}

void			Instructions::floatOperandCheck(std::string const & value) const
{
	std::size_t	i;
	int			found_point;

	found_point = 0;
	if (value.length() == 0)
		throw Instructions::InstructionsException("Invalid operand value: Empty value", value);
	for (i = 0; i < value.length(); i++)
	{
		if ((value.at(i) == '-' && i != 0)
			|| !(value.at(i) >= '0' && value.at(i) <= '9'))
		{
			found_point = (value.at(i) == '.');
			if (found_point == 0)
				throw Instructions::InstructionsException("Invalid operand value", value);
		}
	}
	if (found_point == 0)
			throw Instructions::InstructionsException("Invalid operand value: Missing point", value);
}

void			Instructions::doubleOperandCheck(std::string const & value) const
{
	std::size_t	i;
	char		found_point;

	found_point = 0;
	if (value.length() == 0)
		throw Instructions::InstructionsException("Invalid operand value: Empty value", value);
	for (i = 0; i < value.length(); i++)
	{
		if ((value.at(i) == '-' && i != 0)
			|| !(value.at(i) >= '0' && value.at(i) <= '9'))
		{
			found_point = (value.at(i) == '.');
			if (found_point == 0)
				throw Instructions::InstructionsException("Invalid operand value", value);
		}
	}
	if (found_point == 0)
		throw Instructions::InstructionsException("Invalid operand value: Missing point", value);
}

void			Instructions::noCheck(std::string const & value) const
{
	(void)value;
}
