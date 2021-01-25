/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 11:53:23 by gbourgeo          #+#    #+#             */
/*   Updated: 2021/01/25 21:20:20 by gbourgeo         ###   ########.fr       */
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
		&Parser::push,
		&Parser::pop,
		&Parser::dump,
		&Parser::assert,
		&Parser::add,
		&Parser::sub,
		&Parser::mul,
		&Parser::div,
		&Parser::mod,
		&Parser::print,
		&Parser::exit,
	};

	std::cout << "Instruction	Operand	Value" << std::endl;
	for (Token::t_token const *t = tokens.getNextToken(); t; t = tokens.getNextToken())
	{
		std::cout << t->instruction << "	";// << this->_instructions[t->type].name;
		std::cout << t->operand << "	";
		std::cout << t->operandValue;
		std::cout << std::endl;
	}
	tokens.reset();
	std::cout << std::endl << "Execute :" << std::endl;
	for (Token::t_token const *t = tokens.getNextToken(); t && this->_loop == true; t = tokens.getNextToken())
	{
		(this->*execute[t->instruction])(t);
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

void				Parser::push(Token::t_token const * token)
{
	this->_stack.push_front(this->_op.createOperand(token->operand, token->operandValue));
}

void				Parser::pop(Token::t_token const * token)
{
	if (this->_stack.empty())
		throw Parser::ParserException(token->lineNb, "Pop on an empty stack");
	delete this->_stack.front();
	this->_stack.pop_front();
}

void				Parser::dump(Token::t_token const * token)
{
	(void)token;
	// std::cout << "Dumping stack:" << std::endl;
	std::for_each(this->_stack.begin(), this->_stack.end(),
		[](IOperand const * ope) {
			std::cout << ope->toString() << std::endl;
		});
}

void				Parser::assert(Token::t_token const * token)
{
	IOperand const	*ptr;
	std::string		err;

	err.clear();
	if (this->_stack.front()->getType() != token->operand
	|| this->_stack.front()->toString() != token->operandValue)
	{
		ptr = this->_op.createOperand(token->operand, token->operandValue);
		err = "Assert : " + this->_stack.front()->toString() + " != ";
		err += ptr->toString();
		delete ptr;
		throw Parser::ParserException(token->lineNb, err.c_str());
	}
}

void				Parser::add(Token::t_token const * token)
{
	(void)token;
}

void				Parser::sub(Token::t_token const * token)
{
	(void)token;
}

void				Parser::mul(Token::t_token const * token)
{
	(void)token;
}

void				Parser::div(Token::t_token const * token)
{
	(void)token;
}

void				Parser::mod(Token::t_token const * token)
{
	(void)token;
}

void				Parser::print(Token::t_token const * token)
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
		err = "Print " + this->_stack.front()->toString() + " != " + std::string(this->_instructions->getOperand(IOperand::Int8)) + "()";
		throw Parser::ParserException(token->lineNb, err.c_str());
	}
	value = std::stoi(this->_stack.front()->toString());
	std::cout << static_cast<char>(value) << std::endl;
}

void				Parser::exit(Token::t_token const * token)
{
	(void)token;
	this->_loop = false;
}
