/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Token.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 20:47:27 by gbourgeo          #+#    #+#             */
/*   Updated: 2021/01/31 13:53:12 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Token.hpp"

Token::Token(): _idx(0)
{}

Token::~Token()
{
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

void					Token::addToken(Token::t_token token)
{
	this->_tokens.push_back(token);
}

Token::t_token const	*Token::getNextToken( void )
{
	if (this->_idx < this->_tokens.size())
	{
		return &this->_tokens.at(this->_idx++);
	}
	return nullptr;
}

Token::t_token const	*Token::getLastToken( void ) const
{
	return &this->_tokens.back();
}
