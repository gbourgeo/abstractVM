/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Token.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 20:47:27 by gbourgeo          #+#    #+#             */
/*   Updated: 2021/01/17 21:30:59 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Token.hpp"

Token::Token()
{}

Token::~Token()
{
	auto freePointer = [](Token::t_token const & token) {
		if (token.ope != nullptr)
			delete token.ope;
	};
	std::for_each(this->_tokens.cbegin(), this->_tokens.cend(), freePointer);
	this->_tokens.clear();
}

Token::Token(Token const & src)
{
	*this = src;
}

Token & Token::operator=(Token const & rhs)
{
	if (this != &rhs)
	{
		this->_tokens.clear();
		this->_tokens = rhs._tokens;
	}
	return *this;
}

void	Token::addToken(eTokenType tokenType, std::string const & operandValue, eOperandType opType)
{
	this->_tokens.push_back( (struct s_token){ tokenType, this->_op.createOperand(opType, operandValue) } );
}

void	Token::addToken(eTokenType tokenType)
{
	this->_tokens.push_back( (struct s_token){ tokenType, nullptr } );
}

Token::t_token	const * Token::getNextToken( void )
{
	static std::size_t	i = 0;

	if (i < this->_tokens.size())
	{
		t_token	* tok = &this->_tokens.at(i);
		i++;
		return tok;
	}
	return nullptr;
}
