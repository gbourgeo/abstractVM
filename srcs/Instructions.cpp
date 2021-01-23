/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Instructions.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 18:53:22 by gbourgeo          #+#    #+#             */
/*   Updated: 2021/01/23 15:56:21 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Instructions.hpp"

Instructions::t_inst	Instructions::_instructions[] = {
	{ "push",   Token::Push,   1 },
	{ "pop",    Token::Pop,    0 },
	{ "dump",   Token::Dump,   0 },
	{ "assert", Token::Assert, 1 },
	{ "add",    Token::Add,    0 },
	{ "sub",    Token::Sub,    0 },
	{ "mul",    Token::Mul,    0 },
	{ "div",    Token::Div,    0 },
	{ "mod",    Token::Mod,    0 },
	{ "print",  Token::Print,  0 },
	{ "exit",   Token::Exit,   0 },
};

Instructions::t_ope		Instructions::_values[] = {
	{ "int8",   IOperand::Int8  , &Instructions::intOperandCheck },
	{ "int16",  IOperand::Int16 , &Instructions::intOperandCheck },
	{ "int32",  IOperand::Int32 , &Instructions::intOperandCheck },
	{ "float",  IOperand::Float , &Instructions::floatOperandCheck },
	{ "double", IOperand::Double, &Instructions::doubleOperandCheck },
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

Instructions::t_result const	Instructions::getInstruction(std::vector<std::string> const & token) const
{
	t_result		res;
	std::size_t		parent_left;
	std::size_t		parent_right;

	res.typeToken = Token::Undefined;
	res.typeOperand = IOperand::Undefined;
	res.valueOperand.clear();
	for (std::size_t i = 0; i < sizeof(this->_instructions) / sizeof(this->_instructions[0]); i++)
		if (token.at(0).compare(this->_instructions[i].name) == 0)
		{
			res.typeToken = this->_instructions[i].type;
			if (token.size() < this->_instructions[i].nbArgs + 1)
				throw Instructions::InstructionsException("Invalid instruction: Missing value", token.at(0));
			if (token.size() > this->_instructions[i].nbArgs + 1)
				throw Instructions::InstructionsException("Invalid instruction: Too many values", token.at(0));
			if (this->_instructions[i].nbArgs == 0)
				return res;
			parent_left  = token.at(1).find('(');
			parent_right = token.at(1).find(')');
			if (parent_left == std::string::npos || parent_right == std::string::npos)
				throw Instructions::InstructionsException("Invalid operand format: Missing '(' or ')'", token.at(1));
			for (std::size_t j = 0; j < sizeof(this->_values) / sizeof(this->_values[0]); j++)
				if (token.at(1).compare(0, parent_left, this->_values[j].name) == 0)
				{
					res.typeOperand = this->_values[j].type;
					res.valueOperand = token.at(1).substr(parent_left + 1, parent_right - parent_left - 1);
					(this->*this->_values[j].checkOperand)(res.valueOperand);
					return res;
				}
			throw Instructions::InstructionsException("Invalid operand : Unknown name", token.at(1));
		}
	throw Instructions::InstructionsException("Invalid instruction : Unknown name", token.at(0));
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

Instructions::InstructionsException::InstructionsException(const char * error, std::string const & value)
{
	this->_error = value + ": " + std::string(error) + ".";
}
