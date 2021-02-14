/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 11:53:23 by gbourgeo          #+#    #+#             */
/*   Updated: 2021/02/14 10:34:19 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Parser.hpp"

Parser::Parser(): _instructions(nullptr), _loop(true)
{
	throw Parser::ParserException(0, "No instructions given");
}

Parser::Parser(Instructions const & inst): _instructions(&inst), _loop(true)
{}

Parser::~Parser()
{
	std::for_each(this->_stack.begin(), this->_stack.end(),
		[](IOperand const * ope) {
			delete ope;
		});
	this->_stack.clear();
}

Parser::Parser(Parser const & src)
{
	*this = src;
}

Parser & Parser::operator=(Parser const & rhs)
{
	if (this != &rhs)
	{}
	return *this;
}

void			Parser::parse( Token & tokens )
{
	static void		(Parser::*execute[])( Token::t_token const * ) = {
		&Parser::_push,
		&Parser::_pop,
		&Parser::_dump,
		&Parser::_assert,
		&Parser::_add,
		&Parser::_sub,
		&Parser::_mul,
		&Parser::_div,
		&Parser::_mod,
		&Parser::_print,
		&Parser::_exit,
	};

	for (Token::t_token const *t = tokens.getNextToken(); t && this->_loop == true; t = tokens.getNextToken())
	{
		try
		{
			(this->*execute[t->instruction])(t);
		}
		catch (Operand<int8_t>::OperandException & e)
		{
			throw Parser::ParserException(t->lineNb, e.what());
		}
	}
	if (this->_loop == true)
	{
		std::size_t		lineNb;

		lineNb = (tokens.getLastToken() != nullptr) ? tokens.getLastToken()->lineNb : 0;
		throw Parser::ParserException(lineNb, "No exit instruction given");
	}
}

Parser::ParserException::ParserException(std::size_t lineNb, const char *error)
{
	this->_error = "Line " + std::to_string(lineNb) + " : Error : " + std::string(error);
}

void				Parser::_push(Token::t_token const * token)
{
	this->_stack.push_front(this->_op.createOperand(token->operand, token->operandValue));
}

void				Parser::_pop(Token::t_token const * token)
{
	if (this->_stack.empty())
		throw Parser::ParserException(token->lineNb, "Pop on an empty stack");
	delete this->_stack.front();
	this->_stack.pop_front();
}

void				Parser::_dump(Token::t_token const * token)
{
	(void)token;
	std::for_each(this->_stack.begin(), this->_stack.end(),
		[](IOperand const * ope) {
			std::cout << ope->toString() << std::endl;
		});
}

void				Parser::_assert(Token::t_token const * token)
{
	if (this->_stack.size() == 0)
		throw Parser::ParserException(token->lineNb, "Assertion on empty stack.");
	if (this->_stack.front()->getType() != token->operand)
		throw Parser::ParserException(token->lineNb, "Assertion on invalid token type.");
	if (this->_stack.front()->toString() != token->operandValue)
		throw Parser::ParserException(token->lineNb, "Assertion on invalid token value.");
}

void				Parser::_add(Token::t_token const * token)
{
	IOperand const	*first;
	IOperand const	*second;
	IOperand const	*result;

	if (this->_stack.size() < 2)
		throw Parser::ParserException(token->lineNb, "Addition operation on stack less than 2 operands.");
	first = this->_stack.front();
	this->_stack.pop_front();
	second = this->_stack.front();
	this->_stack.pop_front();
	result = *second + *first;
	this->_stack.push_front(result);
	delete first;
	delete second;
}

void				Parser::_sub(Token::t_token const * token)
{
	IOperand const	*first;
	IOperand const	*second;
	IOperand const	*result;

	if (this->_stack.size() < 2)
		throw Parser::ParserException(token->lineNb, "Substraction operation on stack less than 2 operands.");
	first = this->_stack.front();
	this->_stack.pop_front();
	second = this->_stack.front();
	this->_stack.pop_front();
	result = *second - *first;
	this->_stack.push_front(result);
	delete first;
	delete second;
}

void				Parser::_mul(Token::t_token const * token)
{
	IOperand const	*first;
	IOperand const	*second;
	IOperand const	*result;

	if (this->_stack.size() < 2)
		throw Parser::ParserException(token->lineNb, "Multiplication operation on stack less than 2 operands.");
	first = this->_stack.front();
	this->_stack.pop_front();
	second = this->_stack.front();
	this->_stack.pop_front();
	result = *second * *first;
	this->_stack.push_front(result);
	delete first;
	delete second;
}

void				Parser::_div(Token::t_token const * token)
{
	IOperand const	*first;
	IOperand const	*second;
	IOperand const	*result;

	if (this->_stack.size() < 2)
		throw Parser::ParserException(token->lineNb, "Division operation on stack less than 2 operands.");
	first = this->_stack.front();
	this->_stack.pop_front();
	second = this->_stack.front();
	this->_stack.pop_front();
	result = *second / *first;
	this->_stack.push_front(result);
	delete first;
	delete second;
}

void				Parser::_mod(Token::t_token const * token)
{
	IOperand const	*first;
	IOperand const	*second;
	IOperand const	*result;

	if (this->_stack.size() < 2)
		throw Parser::ParserException(token->lineNb, "Modulo operation on stack less than 2 operands.");
	first = this->_stack.front();
	this->_stack.pop_front();
	second = this->_stack.front();
	this->_stack.pop_front();
	result = *second % *first;
	this->_stack.push_front(result);
	delete first;
	delete second;
}

void				Parser::_print(Token::t_token const * token)
{
	int				value;
	std::string		err;

	err.clear();
	if (this->_stack.front() == nullptr)
	{
		err = "Print on an empty stack";
		throw Parser::ParserException(token->lineNb, err.c_str());
	}
	if (this->_stack.front()->getType() != IOperand::Int8)
	{
		err = "Printing value of a type " + std::string(this->_instructions->getOperand(this->_stack.front()->getType())) + "().";
		err += " Expected " + std::string(this->_instructions->getOperand(IOperand::Int8)) + "().";
		throw Parser::ParserException(token->lineNb, err.c_str());
	}
	value = std::stoi(this->_stack.front()->toString());
	std::cout << static_cast<char>(value) << std::endl;
}

void				Parser::_exit(Token::t_token const * token)
{
	(void)token;
	this->_loop = false;
}
