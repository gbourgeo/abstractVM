/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Token.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 20:47:27 by gbourgeo          #+#    #+#             */
/*   Updated: 2021/01/23 15:45:56 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Token.hpp"

Token::Token(): _idx(0)
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
		this->_idx = rhs._idx;
	}
	return *this;
}

void	Token::addToken(Token::eTokenType typeToken, IOperand::eOperandType typeOperand, std::string const & valueOperand)
{
	this->_tokens.push_back(
		(struct s_token){ typeToken, this->_op.createOperand(typeOperand, valueOperand) });
}

Token::t_token	const * Token::getNextToken( void )
{
	if (this->_idx < this->_tokens.size())
	{
		return &this->_tokens.at(this->_idx++);
	}
	return nullptr;
}
