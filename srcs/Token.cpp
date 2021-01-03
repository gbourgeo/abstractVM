/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Token.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 20:47:27 by gbourgeo          #+#    #+#             */
/*   Updated: 2021/01/03 20:58:42 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Token.hpp"

Token::Token()
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
	}
	return *this;
}

void 	Token::addToken(eTokenType type, std::string & word)
{
	this->_tokens.push_back( (struct s_token){ type, word, "" } );
}

void	Token::addToken(eTokenType type, std::string & word, std::string & args)
{
	this->_tokens.push_back( (struct s_token){ type, word, args } );
}